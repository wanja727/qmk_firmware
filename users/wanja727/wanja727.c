/* Copyright 2025 @ wanja727
 *
 * Shared user logic for all Keychron keyboards. See wanja727.h / readme.md.
 */

#include "wanja727.h"

#ifdef DIGITIZER_ENABLE
#    include "digitizer.h"
#endif

#define HOLD_THRESHOLD 200  // ms; number row: press longer than this -> F1~F12
#define ALT_TAB_TIMEOUT 600 // ms; release Alt this long after the last ALT_TAB tap

// ---- Number row tap/hold table (index 0..11) ----
// clang-format off
static const uint16_t tap_kc[12]  = { KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL };
static const uint16_t hold_kc[12] = { KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12 };
// clang-format on

static bool     numf_held[12] = {false};
static bool     numf_sent[12] = {false};
static uint16_t numf_time[12] = {0};

// ---- NAV (CapsLock) state ----
static bool nav_active = false;

// ---- Alt+Tab task switcher state ----
static bool     alt_tab_active = false;
static uint16_t alt_tab_timer  = 0;

// ---- Mouse "slow on Shift" state ----
static uint8_t mouse_count = 0;     // number of mouse move/wheel keys currently held
static bool    shift_down  = false;
static bool    acl_applied = false; // is MS_ACL0 currently registered?

static void update_slow(void) {
    bool want = shift_down && (mouse_count > 0);
    if (want && !acl_applied) {
        register_code(MS_ACL0);
        acl_applied = true;
    } else if (!want && acl_applied) {
        unregister_code(MS_ACL0);
        acl_applied = false;
    }
}

#ifdef DIGITIZER_ENABLE
// 절대좌표로 커서를 옮긴다. Windows 는 digitizer 를 펜/터치처럼 다루므로
// in_range 를 잠깐 켰다가 끄는 hover 동작으로 포인터를 이동시킨다.
static void cursor_jump(float x, float y) {
    digitizer_in_range_on();
    digitizer_set_position(x, y);
    digitizer_in_range_off();
}
#endif

bool wanja_process_record(uint16_t keycode, keyrecord_t *record, uint8_t nav_layer) {
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

    // --- CapsLock: hold = NAV layer, Win+Caps = real Caps Lock ---
    if (keycode == MO_NAV) {
        if (record->event.pressed) {
            if (get_mods() & MOD_MASK_GUI) {
                tap_code(KC_CAPS); // Win held -> behave as the original Caps Lock
            } else {
                layer_on(nav_layer);
                nav_active = true;
            }
        } else {
            if (nav_active) {
                layer_off(nav_layer);
                nav_active = false;
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

    // --- Alt+Tab task switcher (Alt stays held across taps; Shift -> Alt+Shift+Tab) ---
    if (keycode == ALT_TAB) {
        if (record->event.pressed) {
            if (!alt_tab_active) {
                alt_tab_active = true;
                register_code(KC_LALT);
            }
            alt_tab_timer = timer_read();
            register_code(KC_TAB);
        } else {
            unregister_code(KC_TAB);
            alt_tab_timer = timer_read();
        }
        return false;
    }

#ifdef DIGITIZER_ENABLE
    // --- 절대좌표 커서 이동 (왼쪽/오른쪽 화면 중앙) ---
    if (keycode == CUR_LSCR || keycode == CUR_RSCR) {
        if (record->event.pressed) {
            if (keycode == CUR_LSCR) {
                cursor_jump(CURSOR_LEFT_X, CURSOR_LEFT_Y);
            } else {
                cursor_jump(CURSOR_RIGHT_X, CURSOR_RIGHT_Y);
            }
        }
        return false;
    }
#endif

    // --- Mouse: track movement/wheel keys, make Shift = slow ---
    switch (keycode) {
        case MS_UP:
        case MS_DOWN:
        case MS_LEFT:
        case MS_RGHT:
        case MS_WHLU:
        case MS_WHLD:
        case MS_WHLL:
        case MS_WHLR:
            if (record->event.pressed) {
                mouse_count++;
            } else if (mouse_count) {
                mouse_count--;
            }
            update_slow();
            return true;
        case KC_LSFT:
        case KC_RSFT:
            shift_down = record->event.pressed;
            update_slow();
            // While mousing, consume Shift so it only slows the cursor.
            if (record->event.pressed && mouse_count > 0) {
                return false;
            }
            return true;
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
    // Alt+Tab: release Alt after the timeout once no ALT_TAB key is held.
    if (alt_tab_active && timer_elapsed(alt_tab_timer) > ALT_TAB_TIMEOUT) {
        unregister_code(KC_LALT);
        alt_tab_active = false;
    }
}
