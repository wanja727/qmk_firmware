/* Copyright 2025 @ wanja727
 *
 * Shared user logic for all Keychron keyboards.
 *  - Number row: tap = number, hold = F1~F12 (fires at threshold, no need to keep holding)
 *  - NAV tab/q: tap = browser tab switch, hold = move active window to other monitor
 *  - CapsLock: hold = NAV layer, Win+Caps = real Caps Lock
 *  - Mouse keys: Shift while moving = slow (MS_ACL0); constant speed set in config.h
 */

#include "wanja727.h"

#define HOLD_THRESHOLD 200 // ms; press longer than this -> hold action

// Tap/hold table.  Index 0..11 = number row, 12 = WIN_TAB_PREV, 13 = WIN_TAB_NEXT.
#define TH_COUNT 14

// clang-format off
static const uint16_t tap_kc[TH_COUNT] = {
    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL,
    LCTL(LSFT(KC_TAB)), // WIN_TAB_PREV tap: previous browser tab
    LCTL(KC_TAB),       // WIN_TAB_NEXT tap: next browser tab
};
static const uint16_t hold_kc[TH_COUNT] = {
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
    LGUI(LSFT(KC_LEFT)),  // WIN_TAB_PREV hold: move window to left monitor
    LGUI(LSFT(KC_RIGHT)), // WIN_TAB_NEXT hold: move window to right monitor
};
// clang-format on

static bool     th_held[TH_COUNT] = {false};
static bool     th_sent[TH_COUNT] = {false};
static uint16_t th_time[TH_COUNT] = {0};

// NAV layer (CapsLock) state
static bool nav_active = false;

// Mouse "slow on Shift" state
static uint8_t mouse_count  = 0;     // number of mouse-move/wheel keys currently held
static bool    shift_down   = false;
static bool    acl_applied  = false; // is MS_ACL0 currently registered?

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

bool wanja_process_record(uint16_t keycode, keyrecord_t *record, uint8_t nav_layer) {
    // --- Tap/hold keys (number row + NAV tab/q) ---
    if ((keycode >= NUM_F1 && keycode <= NUM_F12) || keycode == WIN_TAB_PREV || keycode == WIN_TAB_NEXT) {
        uint8_t idx = (keycode <= NUM_F12) ? (uint8_t)(keycode - NUM_F1) : (keycode == WIN_TAB_PREV ? 12 : 13);
        if (record->event.pressed) {
            th_held[idx] = true;
            th_time[idx] = record->event.time;
            th_sent[idx] = false;
        } else {
            th_held[idx] = false;
            if (!th_sent[idx]) {
                tap_code16(tap_kc[idx]); // short press -> tap action
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

    // --- Mouse: track movement keys, make Shift = slow ---
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
            // While mousing, consume Shift so it only slows the cursor (no Shift sent to OS).
            if (record->event.pressed && mouse_count > 0) {
                return false;
            }
            return true;
    }

    return true;
}

void wanja_matrix_scan(void) {
    for (uint8_t i = 0; i < TH_COUNT; i++) {
        if (th_held[i] && !th_sent[i] && timer_elapsed(th_time[i]) > HOLD_THRESHOLD) {
            tap_code16(hold_kc[i]); // held past threshold -> hold action, fire once
            th_sent[i] = true;
        }
    }
}
