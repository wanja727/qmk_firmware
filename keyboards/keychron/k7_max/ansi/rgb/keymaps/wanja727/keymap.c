/* Copyright 2024 ~ 2026 @ Keychron (https://www.keychron.com)
 * Customized by wanja727 -- unified across K7/K11/K15/V8 Max. See users/wanja727/readme.md.
 *
 * 레이어:
 *   BASE        기본 타이핑 (숫자열: tap=숫자, hold=F1~F12)
 *   FN1(media)  기존 Keychron 미디어/RGB/BT 레이어 (Fn 키로 진입)
 *   NAV         CapsLock tap=한/영, hold=방향/편집/브라우저/창/모니터
 *   MOUSE       Space hold 로 진입. 마우스 이동/버튼/휠/브라우저 (Caps hold=정밀 이동)
 */

#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "wanja727.h"

enum layers {
    MAC_BASE,
    WIN_BASE,
    MAC_FN1,
    WIN_FN1,
    NAV,
    MOUSE,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[MAC_BASE] = LAYOUT_ansi_68(
     KC_ESC,   NUM_F1,   NUM_F2,   NUM_F3,   NUM_F4,   NUM_F5,   NUM_F6,   NUM_F7,   NUM_F8,   NUM_F9,   NUM_F10,  NUM_F11,  NUM_F12,  KC_BSPC,           KC_DEL,
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,           KC_HOME,
     MO_NAV,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,            KC_PGUP,
     KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,                      KC_RSFT,  KC_UP,   KC_PGDN,
     KC_LCTL,  KC_LOPTN, KC_LCMMD,                            KC_SPC,                        KC_RCMMD, MO(MAC_FN1),MO(MAC_FN1),KC_LEFT,KC_DOWN, KC_RGHT),

[WIN_BASE] = LAYOUT_ansi_68(
     KC_ESC,   NUM_F1,   NUM_F2,   NUM_F3,   NUM_F4,   NUM_F5,   NUM_F6,   NUM_F7,   NUM_F8,   NUM_F9,   NUM_F10,  NUM_F11,  NUM_F12,  KC_BSPC,           KC_DEL,
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,           KC_HOME,
     MO_NAV,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,            KC_PGUP,
     KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,                      KC_RSFT,  KC_UP,   KC_PGDN,
     KC_LCTL,  KC_LGUI,  KC_LALT,                             KC_SPC,                        KC_RALT,  MO(WIN_FN1),MO(WIN_FN1),KC_LEFT,KC_DOWN, KC_RGHT),

// FN1 = 기존 Keychron 미디어/RGB/BT 레이어 (원본 유지)
[MAC_FN1] = LAYOUT_ansi_68(
     KC_GRV,   KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, UG_VALD,  UG_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,            _______,
     _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            KC_END,
     UG_TOGG,  UG_NEXT,  UG_VALU,  UG_HUEU,  UG_SATU,  UG_SPDU,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
     _______,  UG_PREV,  UG_VALD,  UG_HUED,  UG_SATD,  UG_SPDD,  NK_TOGG,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,
     _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______),

[WIN_FN1] = LAYOUT_ansi_68(
     KC_GRV,   KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  UG_VALD,  UG_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,            _______,
     _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            KC_END,
     UG_TOGG,  UG_NEXT,  UG_VALU,  UG_HUEU,  UG_SATU,  UG_SPDU,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
     _______,  UG_PREV,  UG_VALD,  UG_HUED,  UG_SATD,  UG_SPDD,  NK_TOGG,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,
     _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______),

// NAV = CapsLock(hold)
[NAV] = LAYOUT_ansi_68(
     _______,  _______,           _______,       _______,    _______,      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
     LCTL(LSFT(KC_TAB)),LCTL(KC_TAB),LCTL(KC_W),LALT(KC_F4),_______,        _______,  _______,  KC_HOME,  KC_UP,    KC_END,   _______,  _______,  _______,  _______,            _______,
     _______,  TG(MOUSE),         _______,            _______,  _______,    _______,  _______,  KC_LEFT,  KC_DOWN,  KC_RGHT,  _______,  _______,            _______,            _______,
     _______,  _______,           _______,       _______,    _______,      _______,  KC_BSPC,  KC_DEL,   LGUI(LSFT(KC_LEFT)),LGUI(LSFT(KC_RGHT)),_______,                _______,  _______,  _______,
     _______,  _______,           _______,                                  _______,                                _______,  _______,  _______,  _______,  _______,  _______),

// MOUSE = Caps+A 토글 진입 / Esc 해제 (Caps hold = 빠른 이동)
[MOUSE] = LAYOUT_ansi_68(
     TG(MOUSE),_______,           _______,       _______,    _______,      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
     LCTL(LSFT(KC_TAB)),LCTL(KC_TAB),LCTL(KC_W),LALT(KC_F4),_______,  _______,  _______,  MS_WHLL,  MS_UP,    MS_WHLR,  _______,  _______,  _______,  _______,            _______,
     _______,  MS_BTN4,           MS_BTN1,       MS_BTN2,    MS_BTN5,       _______,  MS_WHLD,  MS_LEFT,  MS_DOWN,  MS_RGHT,  MS_WHLU,  _______,            _______,            _______,
     _______,  _______,           _______,       _______,    _______,      _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,
     _______,  _______,           _______,                                  _______,                                _______,  _______,  _______,  _______,  _______,  _______),
};
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
