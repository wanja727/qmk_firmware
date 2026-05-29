/* Copyright 2024 ~ 2025 @ Keychron (https://www.keychron.com)
 * Customized by wanja727 -- unified across K7/K11/K15/V8 Max. See users/wanja727 for shared logic.
 */

#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "wanja727.h"

enum layers {
    MAC_BASE,
    WIN_BASE,
    MAC_FN1,
    WIN_FN1,
    _FN2,
    NAV,
    WHEEL,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_69(
        KC_ESC,  NUM_F1,   NUM_F2,   NUM_F3,  NUM_F4,  NUM_F5,  NUM_F6,      NUM_F7,   NUM_F8,   NUM_F9,  NUM_F10,  NUM_F11,  NUM_F12,            KC_BSPC,             KC_MUTE,
        KC_TAB,  KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,                 KC_Y,     KC_U,     KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,             KC_DEL,
        MO_NAV,  KC_A,     KC_S,     KC_D,    KC_F,    KC_G,                 KC_H,     KC_J,     KC_K,    KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,              KC_HOME,
        KC_LSFT,           KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,        KC_B,     KC_N,     KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,
        KC_LCTL, KC_LOPTN,           KC_LCMMD,         KC_SPC,  MO(MAC_FN1), MO(_FN2),           KC_SPC,            KC_RCMMD,                     KC_LEFT,  KC_DOWN,   KC_RGHT),

    [WIN_BASE] = LAYOUT_ansi_69(
        KC_ESC,  NUM_F1,   NUM_F2,   NUM_F3,  NUM_F4,  NUM_F5,  NUM_F6,      NUM_F7,   NUM_F8,   NUM_F9,  NUM_F10,  NUM_F11,  NUM_F12,            KC_BSPC,             KC_MUTE,
        KC_TAB,  KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,                 KC_Y,     KC_U,     KC_I,    KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,             KC_DEL,
        MO_NAV,  KC_A,     KC_S,     KC_D,    KC_F,    KC_G,                 KC_H,     KC_J,     KC_K,    KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,              KC_HOME,
        KC_LSFT,           KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,        KC_B,     KC_N,     KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,
        KC_LCTL, KC_LWIN,            KC_LALT,          KC_SPC,  MO(WIN_FN1), MO(_FN2),           KC_SPC,            KC_RALT,                      KC_LEFT,  KC_DOWN,   KC_RGHT),

     [MAC_FN1] = LAYOUT_ansi_69(
        KC_GRV,  KC_BRID,  KC_BRIU,  KC_MCTRL,KC_LNPAD,UG_VALD, UG_VALU,     KC_MPRV,  KC_MPLY,  KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,            _______,             UG_TOGG,
        _______, BT_HST1,  BT_HST2,  BT_HST3, P2P4G,   _______,              MS_BTN1,MS_UP, MS_BTN2,_______,_______, _______,  _______,  _______,             _______,
        UG_TOGG, UG_NEXT,  UG_VALU,  UG_HUED, UG_SATU, UG_SPDU,              MS_LEFT,  MS_DOWN,  MS_RGHT, _______,  _______,  _______,            _______,             KC_END,
        _______,           UG_PREV, UG_VALD, UG_HUEU, UG_SATD, UG_SPDD,     UG_SPDD,  NK_TOGG,  _______, _______,  _______,  _______,  _______,            _______,
        _______, _______,            _______,          MO(WHEEL),_______,    _______,            _______,           _______,                      _______,  _______,   _______),

     [WIN_FN1] = LAYOUT_ansi_69(
        KC_GRV,  KC_BRID,  KC_BRIU,  KC_TASK, KC_FILE, UG_VALD, UG_VALU,     KC_MPRV,  KC_MPLY,  KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,            _______,             UG_TOGG,
        _______, BT_HST1,  BT_HST2,  BT_HST3, P2P4G,   _______,              MS_BTN1,MS_UP, MS_BTN2,_______,_______, _______,  _______,  _______,             _______,
        UG_TOGG, UG_NEXT,  UG_VALU,  UG_HUED, UG_SATU, UG_SPDU,              MS_LEFT,  MS_DOWN,  MS_RGHT, _______,  _______,  _______,            _______,             KC_END,
        _______,           UG_PREV, UG_VALD, UG_HUEU, UG_SATD, UG_SPDD,     UG_SPDD,  NK_TOGG,  _______, _______,  _______,  _______,  _______,            _______,
        _______, _______,            _______,          MO(WHEEL),_______,    _______,            _______,           _______,                      _______,  _______,   _______),

    [_FN2] = LAYOUT_ansi_69(
        KC_TILD, KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,       KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,   KC_F12,             _______,             _______,
        _______, _______,  _______,  _______, _______, _______,              _______,  _______,  _______, _______,  _______,  _______,  _______,  _______,             _______,
        _______, _______,  _______,  _______, _______, _______,              _______,  _______,  _______, _______,  _______,  _______,            _______,             _______,
        _______,           _______,  _______, _______, _______, BAT_LVL,     BAT_LVL,  _______,  _______, _______,  _______,  _______,  _______,            _______,
        _______, _______,            _______,          _______, _______,     _______,            _______,           _______,                      _______,  _______,   _______),

    [NAV] = LAYOUT_ansi_69(
        _______, _______,  _______,  _______, _______, _______, _______,     _______,  _______,  _______, _______,  _______,  _______,            _______,             _______,
        WIN_TAB_PREV,WIN_TAB_NEXT,_______,LCTL(KC_W),LALT(KC_F4),_______,    KC_PGUP,  KC_HOME,  KC_UP,   KC_END,   _______,  _______,  _______,  _______,             _______,
        _______, MS_BTN4,MS_BTN5,_______,_______,_______,             KC_PGDN,  KC_LEFT,  KC_DOWN, KC_RIGHT, _______,  _______,            _______,             _______,
        _______,           _______,  _______, _______, _______, _______,     _______,  KC_BSPC,  KC_DEL,  _______,  _______,  _______,  _______,            _______,
        _______, _______,            _______,          _______, _______,     _______,            _______,           _______,                      _______,  _______,   _______),

    [WHEEL] = LAYOUT_ansi_69(
        _______, _______,  _______,  _______, _______, _______, _______,     _______,  _______,  _______, _______,  _______,  _______,            _______,             _______,
        _______, _______,  _______,  _______, _______, _______,              _______,  _______,  MS_WHLU, _______,  _______,  _______,  _______,  _______,             _______,
        _______, _______,  _______,  _______, _______, _______,              MS_WHLL,  MS_WHLD,  MS_WHLR, _______,  _______,  _______,            _______,             _______,
        _______,           _______,  _______, _______, _______, _______,     _______,  _______,  _______, _______,  _______,  _______,  _______,            _______,
        _______, _______,            _______,          _______, _______,     _______,            _______,           _______,                      _______,  _______,   _______),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MAC_FN1]  = {ENCODER_CCW_CW(UG_VALD, UG_VALU)},
    [WIN_FN1]  = {ENCODER_CCW_CW(UG_VALD, UG_VALU)},
    [_FN2]     = {ENCODER_CCW_CW(UG_VALD, UG_VALU)},
    [NAV]      = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WHEEL]    = {ENCODER_CCW_CW(MS_WHLD, MS_WHLU)},
};
#endif // ENCODER_MAP_ENABLE
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    return wanja_process_record(keycode, record, NAV);
}

void matrix_scan_user(void) {
    wanja_matrix_scan();
}
