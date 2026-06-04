/* Copyright 2025 @ wanja727
 *
 * Shared user logic for all Keychron keyboards. See wanja727.h / readme.md.
 */

#include "wanja727.h"

#define HOLD_THRESHOLD 200  // ms; number row: press longer than this -> F1~F12

// ---- Number row tap/hold table (index 0..11) ----
// clang-format off
static const uint16_t tap_kc[12]  = { KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL };
static const uint16_t hold_kc[12] = { KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12 };
// clang-format on

static bool     numf_held[12] = {false};
static bool     numf_sent[12] = {false};
static uint16_t numf_time[12] = {0};

// ---- NAV (CapsLock tap-hold) state ----
//   tap   = 한/영,  hold/조합 = NAV layer,  Win+Caps = Caps Lock
static bool     caps_held        = false; // tap-hold 세션 진행 중
static bool     caps_nav_on      = false; // Caps 로 인해 NAV 가 켜져 있음
static bool     caps_interrupted = false; // 누른 동안 다른 키가 눌림 -> hold(NAV) 확정
static uint16_t caps_time        = 0;

// ---- Alt+Tab task switcher state ----
// Alt 는 ALT_TAB 을 처음 누른 시점의 레이어(NAV/MOUSE)가 활성인 동안 유지된다.
static bool    alt_tab_active = false;
static uint8_t alt_tab_layer  = 0;

// ---- Mouse "slow on Shift" state ----
// FN1(MOUSE) 레이어를 누르고 있는 동안 Shift 는 기존 동작 대신 "느린 속도 전용" 키로만 쓴다.
static bool shift_down  = false;
static bool acl_applied = false; // is MS_ACL0 currently registered?

static void update_slow(uint8_t mouse_layer) {
    bool want = shift_down && layer_state_is(mouse_layer);
    if (want && !acl_applied) {
        register_code(MS_ACL0);
        acl_applied = true;
    } else if (!want && acl_applied) {
        unregister_code(MS_ACL0);
        acl_applied = false;
    }
}

bool wanja_process_record(uint16_t keycode, keyrecord_t *record, uint8_t nav_layer, uint8_t mouse_layer) {
    // Caps tap-hold: 누르고 있는 동안 다른 키가 눌리면 hold(NAV)로 확정 (tap=한/영 취소)
    if (caps_held && record->event.pressed && keycode != MO_NAV) {
        caps_interrupted = true;
    }

    // --- Number row: tap = number, hold = F1~F12 ---
    if (keycode >= NUM_F1 && keycode <= NUM_F12) {
        uint8_t idx = (uint8_t)(keycode - NUM_F1);
        if (record->event.pressed) {
            numf_held[idx] = true;
            numf_time[idx] = record->event.time;
            numf_sent[idx] = false;
        } else {
            numf_held[idx] = false;
            if (!numf_sent[idx]) {
                tap_code16(tap_kc[idx]);
            }
        }
        return false;
    }

    // --- CapsLock tap-hold: tap = 한/영, hold/조합 = NAV, Win+Caps = Caps Lock ---
    if (keycode == MO_NAV) {
        if (record->event.pressed) {
            if (get_mods() & MOD_MASK_GUI) {
                tap_code(KC_CAPS); // Win held -> 기존 Caps Lock
            } else {
                caps_held        = true;
                caps_interrupted = false;
                caps_time        = record->event.time;
                layer_on(nav_layer);
                caps_nav_on = true;
            }
        } else {
            if (caps_nav_on) {
                layer_off(nav_layer);
                caps_nav_on = false;
            }
            if (caps_held) {
                caps_held = false;
                // 짧게 눌렀고(다른 키 조합 없음) -> tap = 한/영
                if (!caps_interrupted && timer_elapsed(caps_time) < TAPPING_TERM) {
                    tap_code16(HANGEUL_KEYCODE);
                }
            }
        }
        return false;
    }

    // --- 한/영 전환 ---
    if (keycode == HANGEUL) {
        if (record->event.pressed) {
            tap_code16(HANGEUL_KEYCODE);
        }
        return false;
    }

    // --- Alt+Tab task switcher (Alt stays held while the trigger layer is active) ---
    if (keycode == ALT_TAB) {
        if (record->event.pressed) {
            if (!alt_tab_active) {
                alt_tab_active = true;
                alt_tab_layer  = get_highest_layer(layer_state); // NAV or MOUSE
                register_code(KC_LALT);
            }
            register_code(KC_TAB); // 누르고 있으면 반복, 탭하면 한 칸씩 전환 (Shift 동시押 = 역방향)
        } else {
            unregister_code(KC_TAB);
        }
        return false;
    }

    // --- FN1(MOUSE) 홀드 중 Shift = 느린 속도 전용 ---
    if (keycode == KC_LSFT || keycode == KC_RSFT) {
        shift_down = record->event.pressed;
        update_slow(mouse_layer);
        if (layer_state_is(mouse_layer)) {
            return false; // MOUSE 레이어에서는 Shift 를 OS 로 보내지 않고 속도 조절로만 사용
        }
        return true;
    }

    return true;
}

// 오른쪽 Space = LT(MOUSE, KC_SPC) 의 tap/hold 판정 시간.
// 타이핑 중 Space 입력이 늦거나 MOUSE 로 오진입하면 이 값을 조절한다.
//  - 값을 키우면: hold 판정이 늦어져 tap(Space) 이 잘 나옴 (오진입 ↓, 의도한 hold 는 더 길게 눌러야 함)
//  - 값을 줄이면: MOUSE 진입이 빨라짐 (반응 ↑, 타이핑 중 오진입 ↑)
#define RSPACE_TAPPING_TERM 200

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    // 보드별 MOUSE 레이어 인덱스와 무관하게, KC_SPC 를 tap 으로 갖는 모든 LT 에 적용.
    if (IS_QK_LAYER_TAP(keycode) && QK_LAYER_TAP_GET_TAP_KEYCODE(keycode) == KC_SPC) {
        return RSPACE_TAPPING_TERM;
    }
    return TAPPING_TERM;
}

void wanja_matrix_scan(void) {
    // Number row: fire F-key once the hold threshold passes.
    for (uint8_t i = 0; i < 12; i++) {
        if (numf_held[i] && !numf_sent[i] && timer_elapsed(numf_time[i]) > HOLD_THRESHOLD) {
            tap_code16(hold_kc[i]);
            numf_sent[i] = true;
        }
    }
    // Alt+Tab: 진입했던 레이어(Caps/FN1)를 떼면 Alt 를 풀어 선택을 확정한다.
    if (alt_tab_active && !layer_state_is(alt_tab_layer)) {
        unregister_code(KC_LALT);
        alt_tab_active = false;
    }
}
