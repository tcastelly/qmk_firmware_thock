#include QMK_KEYBOARD_H
#include "keymap_jp.h"

enum layers{
    BASE, 
    _RAISE0, 
    _RAISE1, 
    _RAISE2, 
    _RAISE3, 
};

#define RAISE0 MO(_RAISE0)
#define RAISE1 MO(_RAISE1)
#define RAISE2 MO(_RAISE2)
#define RAISE3 MO(_RAISE3)

/* modify this keymap to customize. */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
    /* Left */                                                            /* Right */
    KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_BSPC, 
    KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT, 
    KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, 
                                           RAISE2,  RAISE1, KC_SPC,       KC_ENT, RAISE0,  KC_RALT 
  ),
  [_RAISE0] = LAYOUT(
    /* Left */                                                            /* Right */
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                            KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, 
    KC_CLCK, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______, 
                                        KC_LGUI, RAISE3,  KC_ESC,         _______, _______, _______ 
  ), 
  [_RAISE1] = LAYOUT(
    /* Left */                                                            /* Right */
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                             KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    KC_DEL, 
    KC_LCTL, _______, _______, _______, _______, _______,                          KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_PGUP, KC_HOME, 
    _______, _______, _______, _______, _______, _______,                          KC_INS,  KC_PAUS, KC_PSCR, KC_SLCK,  KC_PGDN, KC_END, 
                                        _______, _______, _______,        _______, RAISE3,  _______ 
  ), 
  [_RAISE2] = LAYOUT(
    /* Left */                                                            /* Right */
    KC_ESC,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                          KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, 
    _______, _______, _______, _______, _______, _______,                          KC_MINS, KC_EQL,  KC_LCBR, KC_RCBR, KC_PIPE, KC_GRV, 
    _______, _______, _______, _______, _______, _______,                          KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, KC_TILD, 
                                        _______, _______, _______,        _______, RAISE3,  JP_KANA 
  ), 
  [_RAISE3] = LAYOUT(
    /* Left */                                                            /* Right */
    _______, RESET,   _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______, 
                                        _______, _______, _______,        _______, _______, _______ 
  ), 
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}

