/* Thock conundrum (4x12 ortho) — shares the canonical users/tcy brain.
 *
 * This board is a frozen island on a pre-2022 QMK base (SAMD51 / ARM_ATSAM,
 * which upstream removed). It still consumes the *single* canonical
 * tapdance.c + tcy.c (mounted at shared_tcy/) via the tcy_compat.h adapter.
 * No OLED / RGB / audio / pointing here, so those parts of tcy.c #ifdef out.
 *
 * Logic (tap_dance_actions, process_record_user, accents, JET, OSX via the
 * runtime is_osx flag) lives in shared_tcy/tcy.c. This file is just layouts.
 */
#include QMK_KEYBOARD_H
#include "tcy_compat.h"   // bridge qk_* -> * before tapdance.h prototypes
#include "tapdance.h"

#define KC_WH_D     KC_MS_WH_DOWN
#define KC_WH_U     KC_MS_WH_UP

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_grid(
      TD(TD_TAB), KC_Q,     KC_W,          KC_E,        KC_R,        KC_T,    KC_Y,    KC_U,    KC_I,        TD(TD_O),   TD(TD_P),    TD(TD_BSPC),
      TD(TD_ESC), TD(TD_A), KC_S,          KC_D,        KC_F,        KC_G,    KC_H,    KC_J,    KC_K,        TD(TD_L),   TD(TD_SCLN), KC_QUOT,
      KC_LSFT,    KC_Z,     KC_X,          KC_C,        KC_V,        KC_B,    KC_N,    KC_M,    KC_COMM,     KC_DOT,     KC_SLSH,     TD(TD_ENT),
      KC_LCTL,    NUM_PADS, ACCENTS_RALT,  KC_LCTL,     TD(TD_LALT), LOWER,   KC_SPC,  RAISE,   TD(TD_RALT), KC_DOWN,    KC_UP,       KC_RGHT
  ),

   // remove tapdance and move spacebar
  [_QWERTY_GAMING] = LAYOUT_grid(
      KC_TAB,    KC_Q,     KC_W,          KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,        KC_P,       KC_BSPC,
      KC_ESC,    KC_A,     KC_S,          KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,        KC_SCLN,    KC_QUOT,
      KC_LSFT,   KC_Z,     KC_X,          KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,      KC_SLSH,    KC_ENT,
      KC_LCTL,   NUM_PADS, KC_LGUI,       KC_LCTL, KC_SPC,  RAISE,   KC_SPC,  LOWER,   KC_LEFT, KC_DOWN,     KC_UP,      KC_RGHT
  ),

  [_LOWER] = LAYOUT_grid(
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC,    KC_AMPR,    KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
      KC_CAPS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,      KC_MINS,    KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
      _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     S(KC_NUHS), KC_HOME, KC_END,  _______, _______,
      _______, _______, _______, _______, _______, _______, _______,   _______,    _______, _______, _______, _______
  ),

  [_RAISE] = LAYOUT_grid(
      KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
      KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
      _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_PGUP, KC_PGDN, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [_ADJUST] = LAYOUT_grid(
      _______, QWERTY,  QWERTY_OSX, QWERTY_GAMING, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [_ESC] = LAYOUT_grid(
      ACCENT_GRAVE, ACCENT_GRAVE, _______, ACCENT_E_GRAVE, JET_RNM, _______, ACCENT_CIRCUM, KC_WH_D, KC_WH_U, JET_OPTI, JET_FORMAT, TD(TD_DEL),
      _______, ACCENT_A_GRAVE, _______, _______, JET_FIND, _______, TD(TD_LEFT), KC_DOWN, KC_UP, TD(TD_RIGHT), _______, ACCENT_TREMA,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  // Placeholder layers required by TCY_FULL_TD: the canonical tap-dances call
  // layer_on(_NUM_PADS) (LALT double-tap) and layer_on(_ACCENTS_RALT) (RALT).
  // Transparent for now (RALT held just yields AltGr+key); flesh out later.
  /* NumPads
   * ,-----------------------------------------------------------------------------------.
   * |      |      |      |      |      |      |      |      |  7   |  8   |  9   | Bksp |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |  4   |  5   |  6   |  -   |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |  1   |  2   |  3   |  +   |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |             |      |  0   |  .   |      |Enter |
   * `-----------------------------------------------------------------------------------'
   */
  [_NUM_PADS] = LAYOUT_grid(
    _______, _______, _______, _______, _______,    _______,    _______,    _______,    KC_7,     KC_8,        KC_9,    KC_BSPC,
    _______, _______, _______, _______, _______,    _______,    _______,    _______,    KC_4,     KC_5,        KC_6,    KC_MINS,
    _______, _______, _______, _______, _______,    _______,    _______,    _______,    KC_1,     KC_2,        KC_3,    KC_PLUS,
    _______, _______, _______, _______, _______,    _______,    _______,    _______,    KC_0,     KC_DOT,      KC_DOT,  KC_ENT
  ),

  [_ACCENTS_RALT] = LAYOUT_grid(
    _______, _______,             _______, _______,       _______, _______, _______, ACCENT_U_AIGU_RALT, ACCENT_I_CIRC_RALT, ACCENT_O_CIRC_RALT, _______, _______,
    _______, ACCENT_A_GRAVE_RALT, _______, _______,       _______, _______, _______, _______,            _______,            _______,            _______, _______,
    _______, _______,             _______, ACCENT_C_RALT, _______, _______, _______, _______,            _______,            _______,            _______, _______,
    _______, _______,             _______, _______,       _______, _______, _______, _______,            _______,            _______,            _______, _______
  )
};
// clang-format on

/* Bounds-checked keymap lookup for the frozen base.
 *
 * The canonical tcy.c uses "signal" layers (_OSX_SIGNAL / _OLED_OFF_SIGNAL) as
 * persistent flags: QWERTY_OSX does layer_on(_OSX_SIGNAL) and is_osx is read
 * back from the layer state. These flag layers are deliberately given NO layout.
 *
 * Modern QMK's keymap_key_to_keycode bounds-checks the layer index and returns
 * KC_TRANSPARENT past the last defined layer, so the flag bit is harmless. But
 * this pre-2022 base (quantum/keymap_common.c) reads keymaps[layer] with no
 * bounds check, and its layer scan walks all 32 bits — so an active _OSX_SIGNAL
 * makes every key read past the end of keymaps[] and return garbage. That is
 * what broke QWERTY_OSX. Replicate the modern guard here (weak override). */
uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key) {
    if (layer >= (sizeof(keymaps) / sizeof(keymaps[0]))) {
        return KC_TRANSPARENT;
    }
    return pgm_read_word(&keymaps[layer][key.row][key.col]);
}
