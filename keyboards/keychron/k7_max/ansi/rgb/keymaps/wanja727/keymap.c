/* Copyright 2024 ~ 2026 @ Keychron (https://www.keychron.com)
 * Customized by wanja727 -- unified across K7/K11/K15/V8 Max. See users/wanja727/readme.md.
 */

#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "wanja727.h"

enum layers {
    MAC_BASE,
    WIN_BASE,
    MAC_FN1,
    WIN_FN1,
    MOUSE,
    NAV,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[MAC_BASE] = LAYOUT_ansi_68(
     KC_ESC,   NUM_F1,   NUM_F2,   NUM_F3,   NUM_F4,   NUM_F5,   NUM_F6,   NUM_F7,   NUM_F8,   NUM_F9,   NUM_F10,  NUM_F11,  NUM_F12,  KC_BSPC,           KC_DEL,
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,           KC_HOME,
     MO_NAV,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,            KC_PGUP,
     KC_LSFT,  KC_Z,     KC_X,    KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,                      KC_RSFT,  KC_UP,   KC_PGDN,
     KC_LCTL,  KC_LOPTN, KC_LCMMD,                               LT(NAV, KC_SPC),                                 KC_RCMMD, MO(MAC_FN1),MO(MAC_FN1),KC_LEFT,KC_DOWN, KC_RGHT),

[WIN_BASE] = LAYOUT_ansi_68(
     KC_ESC,   NUM_F1,   NUM_F2,   NUM_F3,   NUM_F4,   NUM_F5,   NUM_F6,   NUM_F7,   NUM_F8,   NUM_F9,   NUM_F10,  NUM_F11,  NUM_F12,  KC_BSPC,           KC_DEL,
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,           KC_HOME,
     MO_NAV,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,            KC_PGUP,
     KC_LSFT,  KC_Z,     KC_X,    KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,                      KC_RSFT,  KC_UP,   KC_PGDN,
     KC_LCTL,  KC_LGUI,  KC_LALT,                                LT(NAV, KC_SPC),                                 KC_RALT,  MO(WIN_FN1),MO(WIN_FN1),KC_LEFT,KC_DOWN, KC_RGHT),

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

// NAV = CapsLock hold (Caps tap = MOUSE ON).
//  W/E/R/T = 이전탭/다음탭/탭닫기/창닫기, S/G = 마우스 뒤로/앞으로, D/F = 창 좌/우 모니터 이동
//  휠: H=업 ;=다운 Y=좌 P=우
[NAV] = LAYOUT_ansi_68(
     _______,  _______,           _______,            _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
     _______,  LCTL(LSFT(KC_TAB)),LCTL(KC_TAB),LCTL(KC_W),LALT(KC_F4),LCTL(KC_T),MS_WHLL,  KC_HOME,  KC_UP,    KC_END,   MS_WHLR,  _______,  _______,  _______,            _______,
     _______,  MS_BTN4,           MS_BTN5,            LGUI(LSFT(KC_LEFT)),LGUI(LSFT(KC_RGHT)),_______,MS_WHLU,KC_LEFT,KC_DOWN,KC_RGHT,  MS_WHLD,  _______,            _______,            _______,
     _______,  _______,           _______,            _______,            _______,  _______,  KC_BSPC,  KC_DEL,   _______,  _______,  _______,                      _______,  _______,  _______,
     _______,  _______,           _______,                                 _______,                               _______,  _______,  _______,  _______,  _______,  _______),

// MOUSE = Caps tap 으로 ON. Shift tap=MOUSE OFF / Shift hold=일반 Shift. Space tap=Space+MOUSE OFF / hold=NAV.
//  문자 입력 키는 입력 후 자동 BASE 복귀. 나머지(뒤로/앞으로/브라우저/모니터)는 Caps 조합으로 NAV 에서 사용. 휠: H=업 ;=다운 Y=좌 P=우
[MOUSE] = LAYOUT_ansi_68(
     _______,  _______,           _______,            _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
     _______,  _______,           _______,            _______,            _______,  _______,  MS_WHLL,  _______,  MS_UP,    _______,  MS_WHLR,  _______,  _______,  _______,            _______,
     _______,  _______,           _______,            MS_BTN1,            MS_BTN2,  _______,  MS_WHLU,  MS_LEFT,  MS_DOWN,  MS_RGHT,  MS_WHLD,  _______,            _______,            _______,
     MS_OFF_SFT,_______,          _______,            _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,
     _______,  _______,           _______,                                 _______,                               _______,  _______,  _______,  _______,  _______,  _______),
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
