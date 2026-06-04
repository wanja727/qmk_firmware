/* Copyright 2024 ~ 2026 @ Keychron (https://www.keychron.com)
 * Customized by wanja727 -- unified across K7/K11/K15/V8 Max. See users/wanja727/readme.md.
 */

#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "wanja727.h"

enum layers {
    MAC_BASE,
    WIN_BASE,
    MAC_FN2,
    WIN_FN2,
    NAV,
    MOUSE,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_69(
        KC_ESC,   NUM_F1,   NUM_F2,   NUM_F3,   NUM_F4,   NUM_F5,   NUM_F6,   NUM_F7,   NUM_F8,   NUM_F9,   NUM_F10,  NUM_F11,  NUM_F12,            KC_BSPC,            KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_DEL,
        MO_NAV,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,
        KC_LCTL,  KC_LOPTN,           KC_LCMMD,           KC_SPC,   MO(MOUSE),MO(MAC_FN2),        KC_SPC,             KC_RCMMD,                     KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_BASE] = LAYOUT_ansi_69(
        KC_ESC,   NUM_F1,   NUM_F2,   NUM_F3,   NUM_F4,   NUM_F5,   NUM_F6,   NUM_F7,   NUM_F8,   NUM_F9,   NUM_F10,  NUM_F11,  NUM_F12,            KC_BSPC,            KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_DEL,
        MO_NAV,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,
        KC_LCTL,  KC_LWIN,            KC_LALT,            KC_SPC,   MO(MOUSE),MO(WIN_FN2),        KC_SPC,             KC_RALT,                      KC_LEFT,  KC_DOWN,  KC_RGHT),

    // FN2 = 기존 Keychron 미디어/RGB/BT 레이어 (원본 유지)
    [MAC_FN2] = LAYOUT_ansi_69(
        KC_GRV,   KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, UG_VALD,  UG_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,            _______,            UG_TOGG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        UG_TOGG,  UG_NEXT,  UG_VALU,  UG_HUED,  UG_SATU,  UG_SPDU,            _______,  _______,  _______,  _______,  _______,  _______,            _______,            KC_END,
        _______,            UG_PREV,  UG_VALD,  UG_HUEU,  UG_SATD,  UG_SPDD,  UG_SPDD,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,            _______,            _______,  _______,  _______,            _______,            _______,                      _______,  _______,  _______),

    [WIN_FN2] = LAYOUT_ansi_69(
        KC_GRV,   KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  UG_VALD,  UG_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,            _______,            UG_TOGG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        UG_TOGG,  UG_NEXT,  UG_VALU,  UG_HUED,  UG_SATU,  UG_SPDU,            _______,  _______,  _______,  _______,  _______,  _______,            _______,            KC_END,
        _______,            UG_PREV,  UG_VALD,  UG_HUEU,  UG_SATD,  UG_SPDD,  UG_SPDD,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,            _______,            _______,  _______,  _______,            _______,            _______,                      _______,  _______,  _______),

    // NAV = CapsLock(hold)
    [NAV] = LAYOUT_ansi_69(
        _______,  _______,          _______,        _______,    _______,     _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        ALT_TAB,  LCTL(LSFT(KC_TAB)),LCTL(KC_TAB),  LCTL(KC_W), LALT(KC_F4), _______,            _______,  KC_HOME,  KC_UP,    KC_END,   _______,  _______,  _______,  _______,            _______,
        _______,  LGUI(LSFT(KC_LEFT)),LGUI(LSFT(KC_RGHT)),_______,_______,   _______,            _______,  KC_LEFT,  KC_DOWN,  KC_RGHT,  _______,  _______,            _______,            _______,
        _______,  _______,        _______,    _______,    _______,  _______,  _______,  KC_BSPC,  KC_DEL,   _______,  _______,  _______,  _______,            _______,
        _______,  _______,            _______,            HANGEUL,  _______,  _______,            _______,            _______,                      _______,  _______,  _______),

    // MOUSE = FN1(주 Fn) hold
    [MOUSE] = LAYOUT_ansi_69(
        _______,  _______,          _______,        _______,    _______,     _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        ALT_TAB,  LCTL(LSFT(KC_TAB)),LCTL(KC_TAB),  LCTL(KC_W), LALT(KC_F4), _______,            _______,  MS_WHLL,  MS_UP,    MS_WHLR,  _______,  _______,  _______,  _______,            _______,
        _______,  MS_BTN4,          MS_BTN5,        MS_BTN1,    MS_BTN2,     _______,            MS_WHLD,  MS_LEFT,  MS_DOWN,  MS_RGHT,  MS_WHLU,  _______,            _______,            _______,
        _______,            _______,        _______,    _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,            _______,            _______,  _______,  _______,            _______,            _______,                      _______,  _______,  _______),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MAC_FN2]  = {ENCODER_CCW_CW(UG_VALD, UG_VALU)},
    [WIN_FN2]  = {ENCODER_CCW_CW(UG_VALD, UG_VALU)},
    [NAV]      = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MOUSE]    = {ENCODER_CCW_CW(MS_WHLD, MS_WHLU)},
};
#endif // ENCODER_MAP_ENABLE
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    return wanja_process_record(keycode, record, NAV, MOUSE);
}

void matrix_scan_user(void) {
    wanja_matrix_scan();
}
