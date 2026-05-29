/* Copyright 2025 @ wanja727
 *
 * Shared user logic for all Keychron keyboards (K7 Max / K11 Max / K15 Max / V8 Max).
 *
 * Custom keycodes start at NEW_SAFE_RANGE (defined in keychron_common.h) because
 * Keychron already uses the QK_KB_0.. range for its own keycodes (BT_HST1, P2P4G, ...).
 */

#pragma once

#include QMK_KEYBOARD_H
#include "keychron_common.h"

enum wanja_keycodes {
    // Number row: tap = number/symbol, hold(>HOLD_THRESHOLD) = F1~F12 (fires immediately)
    NUM_F1 = NEW_SAFE_RANGE,
    NUM_F2,
    NUM_F3,
    NUM_F4,
    NUM_F5,
    NUM_F6,
    NUM_F7,
    NUM_F8,
    NUM_F9,
    NUM_F10,
    NUM_F11,
    NUM_F12,
    // NAV layer tab/q: tap = browser tab switch, hold = move window across monitors
    WIN_TAB_PREV, // tap: Ctrl+Shift+Tab (prev tab)  | hold: Win+Shift+Left  (window to left monitor)
    WIN_TAB_NEXT, // tap: Ctrl+Tab       (next tab)  | hold: Win+Shift+Right (window to right monitor)
    // CapsLock replacement: hold = NAV layer | (Win + this) = real Caps Lock
    MO_NAV,
};

// Shared hooks. Each board's keymap forwards process_record_user / matrix_scan_user here.
// nav_layer is passed in because the NAV layer index differs per board.
bool wanja_process_record(uint16_t keycode, keyrecord_t *record, uint8_t nav_layer);
void wanja_matrix_scan(void);
