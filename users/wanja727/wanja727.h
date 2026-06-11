/* Copyright 2025 @ wanja727
 *
 * Shared user logic for all Keychron keyboards (K7 Max / K11 Max / K15 Max / V8 Max).
 *
 * Layer model (see each board's keymap + readme.md):
 *   BASE  -> normal typing (number row: tap = number, hold = F1~F12)
 *   FN2   -> the original Keychron media/RGB/BT layer (renamed from FN1)
 *   NAV   -> CapsLock modifier: arrows / editing / browser / window / multi-monitor / 한영
 *   MOUSE -> FN1 modifier: mouse move / buttons / wheel / browser / task switch
 *
 * Custom keycodes start at NEW_SAFE_RANGE (defined in keychron_common.h) because Keychron
 * already uses the QK_KB_0.. range for its own keycodes (BT_HST1, P2P4G, ...).
 */

#pragma once

#include QMK_KEYBOARD_H
#include "keychron_common.h"

// ---------------------------------------------------------------------------
// 한/영 전환 키. 1순위는 KC_LNG1. Windows 환경에서 동작하지 않으면 아래를
// KC_RALT 로 바꿔서 다시 빌드하면 된다. (자세한 내용은 readme.md 참고)
// ---------------------------------------------------------------------------
#define HANGEUL_KEYCODE KC_LNG1
// #define HANGEUL_KEYCODE KC_RALT

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
    // CapsLock replacement (tap-hold):
    //   tap        = MOUSE 레이어 ON (layer_on, 토글 아님)
    //   hold/조합  = NAV layer
    //   Win + this = 기존 Caps Lock
    MO_NAV,
    // (사용 안 함) 한/영 키코드 슬롯. 직접 누르면 HANGEUL_KEYCODE 를 보낸다(현재 키맵엔 미배치).
    HANGEUL,
    // (사용 안 함) 슬롯 유지. (VIA 키코드 값 안정성)
    ALT_TAB,
    // MOUSE 레이어의 좌Shift (custom tap-hold):
    //   tap        = MOUSE 레이어 OFF (layer_off, Shift 입력 없음)
    //   hold/조합  = 일반 Shift (KC_LSFT)
    MS_OFF_SFT,
};

// Shared hooks. Each board's keymap forwards process_record_user / matrix_scan_user here.
// nav_layer / mouse_layer are passed in because the layer indices differ per board.
bool wanja_process_record(uint16_t keycode, keyrecord_t *record, uint8_t nav_layer, uint8_t mouse_layer);
void wanja_matrix_scan(void);
