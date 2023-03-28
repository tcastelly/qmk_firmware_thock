#include QMK_KEYBOARD_H
#include "quantum.h"

enum layers {
  _QWERTY,
  _QWERTY_OSX,
  _COLEMAK,
  _LOWER,
  _RAISE,
  _ADJUST,
  _ESC,
  _ESC_OSX,
  _ACCENTS_RALT,
  _NUM_PADS
};

enum keycodes {
  QWERTY  = SAFE_RANGE,
  QWERTY_OSX,
  COLEMAK,
  LOWER,
  RAISE,
  ACCENT_TREMA,
  ACCENT_E_GRAVE,
  ACCENT_A_GRAVE,
  ACCENT_U_GRAVE,
  ACCENT_I_TREMA,
  ACCENT_GRAVE,
  ACCENT_CIRCUM,
  NUM_PADS,

  ACCENTS_RALT,

  // to be used with RALT already pressed
  ACCENT_I_CIRC_RALT,
  ACCENT_O_CIRC_RALT,
  ACCENT_U_AIGU_RALT,
  ACCENT_C_RALT,
  ACCENT_A_GRAVE_RALT,

  // Jetbrains macro
  JET_FIND,
  JET_RNM,
};

// "tap-hold"
typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

// custom tap dance
enum {
    TD_TAB,
    TD_O,
    TD_P,
    TD_L,
    TD_SCLN,
    TD_ENT,
    TD_BSPC,
    TD_BSPC_OSX,
    TD_DEL,
    TD_DEL_OSX,
    TD_ESC,
    TD_ESC_OSX,
    TD_LEFT_OSX,
    TD_LEFT,
    TD_RIGHT_OSX,
    TD_RIGHT,
};

bool is_hold_tapdance_disabled = false;

uint16_t last_hold_t;

#define TD_INDEX(code) ((code)&0xFF)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |      |     | Alt  |  GUI |Lower |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
// same as QWERTY but use KC_RALT instead of KC_GUI
// to use accents
[_QWERTY] = LAYOUT_grid(
    TD(TD_TAB),    KC_Q,     KC_W,          KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    TD(TD_O),    TD(TD_P),   TD(TD_BSPC),
    TD(TD_ESC),    KC_A,     KC_S,          KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    TD(TD_L),    TD(TD_SCLN),KC_QUOT,
    KC_LSFT,       KC_Z,     KC_X,          KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,      KC_SLSH,    TD(TD_ENT),
    KC_LCTL,       NUM_PADS, ACCENTS_RALT,  KC_LCTL, KC_LALT, LOWER,   KC_SPC,  RAISE,   KC_LEFT, KC_DOWN,     KC_UP,      KC_RGHT
),

[_QWERTY_OSX] = LAYOUT_grid(
    TD(TD_TAB),    KC_Q,     KC_W,         KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    TD(TD_O),    TD(TD_P),   TD(TD_BSPC_OSX),
    TD(TD_ESC_OSX),KC_A,     KC_S,         KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    TD(TD_L),    TD(TD_SCLN),KC_QUOT,
    KC_LSFT,       KC_Z,     KC_X,         KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,      KC_SLSH,    TD(TD_ENT),
    KC_LCTL,       NUM_PADS, ACCENTS_RALT, KC_LCTL, KC_LGUI, LOWER,   KC_SPC,  RAISE,   KC_LEFT, KC_DOWN,     KC_UP,      KC_RGHT
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Dvorak| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
    KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    QWERTY,  KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |CapLk |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_grid(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_DEL,
    KC_CAPS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
    _______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next |ScrBr-|ScrBr+| Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_grid(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_BRID, KC_BRIU, KC_MPLY
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |Qwerty|QwrtyL|Colemk|      |      |      |      |      |      |      |Reset |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |AGnorm|AGswap|      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_grid(
    _______, QWERTY_OSX,  QWERTY,  COLEMAK, _______, _______, _______, _______, _______,  _______, _______, RESET,
    _______, _______,     _______, _______, _______, AG_NORM, AG_SWAP, _______, _______,  _______, _______, _______,
    _______, _______,     _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
    _______, _______,     _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
),

/* ESC
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |Del   |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      | Left | Down |  Up  |Right |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ESC] = LAYOUT_grid(
  ACCENT_GRAVE, ACCENT_GRAVE,   _______, ACCENT_E_GRAVE, JET_RNM,  _______, ACCENT_CIRCUM, ACCENT_U_GRAVE, ACCENT_I_TREMA, _______,      _______, TD(TD_DEL),
  _______,      ACCENT_A_GRAVE, _______, _______,        JET_FIND, _______, TD(TD_LEFT),   KC_DOWN,        KC_UP,          TD(TD_RIGHT), _______, ACCENT_TREMA,
  _______,      _______,        _______, _______,        _______,  _______, _______,       _______,        _______,        _______,      _______, _______,
  _______,      _______,        _______, _______,        _______,  _______, _______,       _______,        _______,        _______,      _______, _______
),

[_ESC_OSX] = LAYOUT_grid(
  ACCENT_GRAVE, ACCENT_GRAVE,   _______, ACCENT_E_GRAVE, JET_RNM,  _______, ACCENT_CIRCUM, ACCENT_U_GRAVE, ACCENT_I_TREMA, _______,      _______, TD(TD_DEL_OSX),
  _______,      ACCENT_A_GRAVE, _______, _______,        JET_FIND, _______, TD(TD_LEFT),   KC_DOWN,        KC_UP,          TD(TD_RIGHT), _______, ACCENT_TREMA,
  _______,      _______,        _______, _______,        _______,  _______, _______,       _______,        _______,        _______,      _______, _______,
  _______,      _______,        _______, _______,        _______,  _______, _______,       _______,        _______,        _______,      _______, _______
),


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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  qk_tap_dance_action_t *action;

  switch (keycode) {
    case QWERTY:
        if (record->event.pressed) {
            layer_move(_QWERTY);
        }
        return false;
        break;

    case QWERTY_OSX:
        if (record->event.pressed) {
            layer_move(_QWERTY_OSX);
        }
        return false;
        break;

    case COLEMAK:
        if (record->event.pressed) {
            layer_move(_COLEMAK);
        }
        return false;
        break;

    case LOWER:
      if (record->event.pressed) {
        is_hold_tapdance_disabled = true;
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        is_hold_tapdance_disabled = false;
      }
      return false;
      break;

    case RAISE:
      if (record->event.pressed) {
        is_hold_tapdance_disabled = true;
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        is_hold_tapdance_disabled = false;
      }
      return false;
      break;

    case KC_LSFT:
    case KC_LALT:
    case KC_RALT:
    case KC_LGUI:
      if (record->event.pressed) {
          is_hold_tapdance_disabled = true;
      } else {
          is_hold_tapdance_disabled = false;
      }
      return true;
      break;

    case NUM_PADS:
      if (record->event.pressed) {
        is_hold_tapdance_disabled = true;
        layer_on(_NUM_PADS);
      } else {
        layer_off(_NUM_PADS);
        is_hold_tapdance_disabled = false;
      }
      break;

     case ACCENTS_RALT:
       if (record->event.pressed) {
           is_hold_tapdance_disabled = true;
           register_code(KC_RALT);
           layer_on(_ACCENTS_RALT);
       } else {
           unregister_code(KC_RALT);
           layer_off(_ACCENTS_RALT);
           is_hold_tapdance_disabled = false;
       }
       break;

     case ACCENT_E_GRAVE:
       if (record->event.pressed) {
           register_code(KC_RALT);
           register_code(KC_GRV);
       } else {
           unregister_code(KC_GRV);
           unregister_code(KC_RALT);
           register_code(KC_E);
           unregister_code(KC_E);
       }
       break;

     case ACCENT_A_GRAVE:
       if (record->event.pressed) {
           register_code(KC_RALT);
           register_code(KC_GRV);
       } else {
           unregister_code(KC_GRV);
           unregister_code(KC_RALT);
           register_code(KC_A);
           unregister_code(KC_A);
       }
       break;

     case ACCENT_U_GRAVE:
       if (record->event.pressed) {
           register_code(KC_RALT);
           register_code(KC_GRV);
       } else {
           unregister_code(KC_GRV);
           unregister_code(KC_RALT);
           register_code(KC_U);
           unregister_code(KC_U);
       }
       break;

    case ACCENT_CIRCUM:
      if (record->event.pressed) {
          register_code(KC_RALT);
          register_code(KC_6);
      } else {
          unregister_code(KC_6);
          unregister_code(KC_RALT);
      }
      break;

    case ACCENT_GRAVE:
      if (record->event.pressed) {
          register_code(KC_RALT);
          register_code(KC_GRV);
      } else {
          unregister_code(KC_GRV);
          unregister_code(KC_RALT);
      }
      break;

     case ACCENT_I_TREMA:
       if (record->event.pressed) {
           register_code(KC_RALT);
           register_code(KC_LSFT);
           register_code(KC_QUOT);
           unregister_code(KC_QUOT);
       } else {
           unregister_code(KC_LSFT);
           unregister_code(KC_RALT);
           register_code(KC_I);
           unregister_code(KC_I);
       }
       break;

     case ACCENT_TREMA:
       if (record->event.pressed) {
           register_code(KC_RALT);
           register_code(KC_LSFT);
           register_code(KC_QUOT);
       } else {
           unregister_code(KC_QUOT);
           unregister_code(KC_LSFT);
           unregister_code(KC_RALT);
       }
       break;

      // to be used with RALT already pressed
     case ACCENT_A_GRAVE_RALT:
       if (record->event.pressed) {
           register_code(KC_GRV);
       } else {
           unregister_code(KC_GRV);
           unregister_code(KC_RALT);
           register_code(KC_A);
           unregister_code(KC_A);

           // will be unregister by release `ACCENTS_RALT`
           register_code(KC_RALT);
       }
       break;

     case ACCENT_I_CIRC_RALT:
       if (record->event.pressed) {
           register_code(KC_6);
       } else {
           unregister_code(KC_6);
           unregister_code(KC_RALT);
           register_code(KC_I);
           unregister_code(KC_I);

           // will be unregister by release `ACCENTS_RALT`
           register_code(KC_RALT);
       }
       break;

     case ACCENT_O_CIRC_RALT:
       if (record->event.pressed) {
           register_code(KC_6);
       } else {
           unregister_code(KC_6);
           unregister_code(KC_RALT);
           register_code(KC_O);
           unregister_code(KC_O);

           // will be unregister by release `ACCENTS_RALT`
           register_code(KC_RALT);
       }
       break;

     case ACCENT_U_AIGU_RALT:
       if (record->event.pressed) {
           register_code(KC_GRV);
       } else {
           unregister_code(KC_GRV);
           unregister_code(KC_RALT);
           register_code(KC_U);
           unregister_code(KC_U);

           // will be unregister by release `ACCENTS_RALT`
           register_code(KC_RALT);
       }
       break;

     case ACCENT_C_RALT:
       if (record->event.pressed) {
           register_code(KC_COMM);
       } else {
           unregister_code(KC_COMM);
           unregister_code(KC_RALT);

           // will be unregister by release `ACCENTS_RALT`
           register_code(KC_RALT);
       }
       break;

     case JET_RNM:
       if (record->event.pressed) {
           register_code(KC_LSFT);
           register_code(KC_F6);

           unregister_code(KC_LSFT);
           unregister_code(KC_F6);
       }
       return false;
       break;

     case JET_FIND:
       if (record->event.pressed) {
           register_code(KC_LALT);
           register_code(KC_F1);

           unregister_code(KC_F1);
           unregister_code(KC_LALT);
           tap_code(KC_1);
       }
       return false;
       break;

     // list all tap dance keycodes with tap-hold configurations
     case TD(TD_O):
     case TD(TD_ESC):
     case TD(TD_ESC_OSX):
     case TD(TD_TAB):
     case TD(TD_P):
     case TD(TD_L):
     case TD(TD_SCLN):
     case TD(TD_ENT):
     case TD(TD_BSPC):
     case TD(TD_BSPC_OSX):
     case TD(TD_DEL):
     case TD(TD_DEL_OSX):
     case TD(TD_LEFT):
     case TD(TD_LEFT_OSX):
     case TD(TD_RIGHT):
     case TD(TD_RIGHT_OSX):
       if ((keycode == TD(TD_ESC) || keycode == TD(TD_ESC_OSX)) && !record->event.pressed) {
           layer_off(_ESC);
           layer_off(_ESC_OSX);
           is_hold_tapdance_disabled = false;
       }

       if (timer_elapsed(last_hold_t) < 50) {
           return false;
       }

       action = &tap_dance_actions[TD_INDEX(keycode)];
       if (!record->event.pressed && action->state.count && !action->state.finished) {
           tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
           tap_code16(tap_hold->tap);
       }
       break;
  }
  return true;
}

void tap_dance_tap_hold_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
            && !is_hold_tapdance_disabled
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

// allow call multiple tap dance simultaneously
// e.g: TD_DEL/TD_DEL_LIN
void tap_dance_tap_hold_finished_unprotected(qk_tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(qk_tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

void tap_dance_tap_hold_finished_layout(qk_tap_dance_state_t *state, void *user_data) {
    last_hold_t = timer_read();

    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    is_hold_tapdance_disabled = true;

    if (state->pressed) {
        layer_on(tap_hold->hold);
    }
}

void tap_dance_tap_hold_reset_layout(qk_tap_dance_state_t *state, void *user_data) {
    is_hold_tapdance_disabled = false;
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

// allow call multiple tap dance simultaneously
// e.g: TD_DEL/TD_DEL_LIN
#define ACTION_TAP_DANCE_TAP_HOLD_UNPROTECTED(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished_unprotected, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

#define ACTION_TAP_DANCE_TAP_HOLD_LAYOUT(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished_layout, tap_dance_tap_hold_reset_layout}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC] = ACTION_TAP_DANCE_TAP_HOLD_LAYOUT(KC_ESC, _ESC),
    [TD_ESC_OSX] = ACTION_TAP_DANCE_TAP_HOLD_LAYOUT(KC_ESC, _ESC_OSX),
    [TD_TAB] = ACTION_TAP_DANCE_TAP_HOLD(KC_TAB, KC_TILD),
    [TD_O] = ACTION_TAP_DANCE_TAP_HOLD(KC_O, KC_LPRN),
    [TD_P] = ACTION_TAP_DANCE_TAP_HOLD(KC_P, KC_RPRN),
    [TD_L] = ACTION_TAP_DANCE_TAP_HOLD(KC_L, KC_LCBR),
    [TD_SCLN] = ACTION_TAP_DANCE_TAP_HOLD(KC_SCLN, KC_RCBR),
    [TD_ENT] = ACTION_TAP_DANCE_TAP_HOLD(KC_ENT, KC_LSFT),

    // same tap-dance
    // enable it for osx and linux
    [TD_BSPC_OSX] = ACTION_TAP_DANCE_TAP_HOLD(KC_BSPC, LALT(KC_BSPC)),
    [TD_BSPC] = ACTION_TAP_DANCE_TAP_HOLD(KC_BSPC, LCTL(KC_BSPC)),

    [TD_DEL_OSX] = ACTION_TAP_DANCE_TAP_HOLD_UNPROTECTED(KC_DEL, LALT(KC_DEL)),
    [TD_DEL] = ACTION_TAP_DANCE_TAP_HOLD_UNPROTECTED(KC_DEL, LCTL(KC_DEL)),

    [TD_LEFT_OSX] = ACTION_TAP_DANCE_TAP_HOLD_UNPROTECTED(KC_LEFT, LALT(KC_LEFT)),
    [TD_LEFT] = ACTION_TAP_DANCE_TAP_HOLD_UNPROTECTED(KC_LEFT, LCTL(KC_LEFT)),

    [TD_RIGHT_OSX] = ACTION_TAP_DANCE_TAP_HOLD_UNPROTECTED(KC_RIGHT, LALT(KC_RIGHT)),
    [TD_RIGHT] = ACTION_TAP_DANCE_TAP_HOLD_UNPROTECTED(KC_RIGHT, LCTL(KC_RIGHT)),
};

