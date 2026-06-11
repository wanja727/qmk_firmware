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
//   tap   = MOUSE ON,  hold/조합 = NAV layer,  Win+Caps = Caps Lock
static bool     caps_held        = false; // tap-hold 세션 진행 중
static bool     caps_nav_on      = false; // Caps 로 인해 NAV 가 켜져 있음
static bool     caps_interrupted = false; // 누른 동안 다른 키가 눌림 -> hold(NAV) 확정
static uint16_t caps_time        = 0;

// ---- MOUSE 좌Shift(MS_OFF_SFT) tap-hold state ----
//   tap = MOUSE OFF,  hold/조합 = 일반 Shift(KC_LSFT)
static bool     msoffsft_held        = false;
static bool     msoffsft_shift_on    = false; // KC_LSFT 를 register 한 상태
static bool     msoffsft_interrupted = false;
static uint16_t msoffsft_time        = 0;

// ---- Alt+Tab task switcher state (미사용, 슬롯 유지) ----
static bool    alt_tab_active = false;
static uint8_t alt_tab_layer  = 0;

// MOUSE 레이어에서 누르면 "해당 키 입력 + 자동 BASE 복귀(layer_off)" 대상인 '문자 입력' 키인가?
//  - 알파벳/숫자/기호/Space + 우측 Alt(한/영키, 타이핑 의사) 가 대상.
//  - 마우스/NAV/modifier/media/layer/encoder 키는 대상 아님(여기서 false).
//  - 숫자열(NUM_F*)·Space(LT)는 keycode 형태가 달라 별도 분기에서 처리한다.
static bool is_text_input_key(uint16_t keycode) {
    if (keycode >= KC_A && keycode <= KC_0) return true; // A~Z, 1~0
    switch (keycode) {
        case KC_MINS: case KC_EQL:  case KC_LBRC: case KC_RBRC:
        case KC_BSLS: case KC_SCLN: case KC_QUOT: case KC_GRV:
        case KC_COMM: case KC_DOT:  case KC_SLSH: case KC_SPC:
        case KC_RALT: // 우측 Alt = 한/영(OS) — 누르는 행위 자체가 타이핑 의사
            return true;
    }
    return false;
}

// MOUSE auto-off 를 적용할 상태인가?
//  - MOUSE 활성 & NAV 비활성이어야 하고,
//  - Ctrl/Alt/GUI 가 눌려 있으면(=단축키 조합, 예: Ctrl+C/Ctrl+V) auto-off 하지 않는다.
//    (Shift 는 제외: Shift+글자 = 대문자라 여전히 '문자 입력'으로 보고 auto-off 유지)
static bool mouse_auto_off_armed(uint8_t nav_layer, uint8_t mouse_layer) {
    if (!layer_state_is(mouse_layer) || layer_state_is(nav_layer)) return false;
    if (get_mods() & (MOD_MASK_CTRL | MOD_MASK_ALT | MOD_MASK_GUI)) return false;
    return true;
}

bool wanja_process_record(uint16_t keycode, keyrecord_t *record, uint8_t nav_layer, uint8_t mouse_layer) {
    // Caps tap-hold: 누르고 있는 동안 다른 키가 눌리면 hold(NAV)로 확정 (tap=MOUSE ON 취소)
    if (caps_held && record->event.pressed && keycode != MO_NAV) {
        caps_interrupted = true;
    }
    // MOUSE 좌Shift tap-hold: 다른 키가 같이 눌리면 hold(Shift)로 확정하고 즉시 Shift 를 눌러
    // Shift+키 조합이 정상 동작하게 한다 (tap=MOUSE OFF 취소).
    if (msoffsft_held && record->event.pressed && keycode != MS_OFF_SFT) {
        msoffsft_interrupted = true;
        if (!msoffsft_shift_on) {
            register_code(KC_LSFT);
            msoffsft_shift_on = true;
        }
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
                tap_code16(tap_kc[idx]); // tap = 숫자/기호 (문자 입력)
                // 문자 입력 -> MOUSE 자동 OFF (NAV 사용 중·단축키 조합 중에는 제외)
                if (mouse_auto_off_armed(nav_layer, mouse_layer)) {
                    layer_off(mouse_layer);
                }
            }
        }
        return false;
    }

    // --- CapsLock: tap = MOUSE ON / hold(또는 조합) = NAV / Win+Caps = Caps Lock ---
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
                // 짧게 눌렀고(다른 키 조합 없음) -> tap = MOUSE 레이어 ON (토글 아님)
                if (!caps_interrupted && timer_elapsed(caps_time) < TAPPING_TERM) {
                    layer_on(mouse_layer);
                }
            }
        }
        return false;
    }

    // --- MOUSE 좌Shift: tap = MOUSE OFF / hold(또는 조합) = 일반 Shift ---
    if (keycode == MS_OFF_SFT) {
        if (record->event.pressed) {
            msoffsft_held        = true;
            msoffsft_interrupted = false;
            msoffsft_shift_on    = false;
            msoffsft_time        = record->event.time;
            // press 시점엔 Shift 를 누르지 않는다(탭이면 Shift 입력이 남지 않도록).
        } else {
            if (msoffsft_held) {
                msoffsft_held = false;
                // 짧게 눌렀고(조합 없음) -> tap = MOUSE OFF (Shift 입력 없음)
                if (!msoffsft_interrupted && timer_elapsed(msoffsft_time) < TAPPING_TERM) {
                    layer_off(mouse_layer);
                }
            }
            if (msoffsft_shift_on) {
                unregister_code(KC_LSFT);
                msoffsft_shift_on = false;
            }
        }
        return false;
    }

    // --- (미사용) 한/영 키코드 직접 입력 슬롯 ---
    if (keycode == HANGEUL) {
        if (record->event.pressed) {
            tap_code16(HANGEUL_KEYCODE);
        }
        return false;
    }

    // --- (미사용) Alt+Tab task switcher 슬롯 ---
    if (keycode == ALT_TAB) {
        if (record->event.pressed) {
            if (!alt_tab_active) {
                alt_tab_active = true;
                alt_tab_layer  = get_highest_layer(layer_state);
                register_code(KC_LALT);
            }
            register_code(KC_TAB);
        } else {
            unregister_code(KC_TAB);
        }
        return false;
    }

    // --- Space = LT(NAV, KC_SPC): MOUSE 에서 tap 하면 Space 입력 + MOUSE OFF ---
    //   hold = NAV 진입(LT 기본 동작). hold 중(NAV 활성)에는 auto-off 안 함.
    if (keycode == (uint16_t)(QK_LAYER_TAP | (((uint16_t)nav_layer & 0xF) << 8) | KC_SPC)) {
        if (!record->event.pressed && record->tap.count > 0) {
            // tap 으로 확정 (실제 Space 는 LT 코어가 입력). 문자 입력이므로 MOUSE OFF.
            if (mouse_auto_off_armed(nav_layer, mouse_layer)) {
                layer_off(mouse_layer);
            }
        }
        return true; // LT 기본 처리(tap=Space, hold=NAV)에 맡긴다
    }

    // --- 문자 입력 키 auto-off ---
    //   MOUSE 활성 & NAV 비활성 & (단축키 modifier 미사용) 이고 문자 입력 키면,
    //   해당 키는 그대로 입력되고(return true) MOUSE 레이어는 OFF 되어 BASE 로 복귀.
    if (record->event.pressed
        && is_text_input_key(keycode)
        && mouse_auto_off_armed(nav_layer, mouse_layer)) {
        layer_off(mouse_layer);
    }

    return true;
}

void wanja_matrix_scan(void) {
    // Number row: fire F-key once the hold threshold passes.
    for (uint8_t i = 0; i < 12; i++) {
        if (numf_held[i] && !numf_sent[i] && timer_elapsed(numf_time[i]) > HOLD_THRESHOLD) {
            tap_code16(hold_kc[i]);
            numf_sent[i] = true;
        }
    }
    // Alt+Tab(미사용): 진입했던 레이어를 떼면 Alt 를 풀어 선택을 확정한다.
    if (alt_tab_active && !layer_state_is(alt_tab_layer)) {
        unregister_code(KC_LALT);
        alt_tab_active = false;
    }
}
