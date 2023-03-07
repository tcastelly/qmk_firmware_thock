#include QMK_KEYBOARD_H
#include "quantum.h"

enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _ARROWS,
  _ACCENTS,
  _NUM_PADS
};

enum keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ACCENTS,
  ACCENT_TREMA,
  ACCENT_E_GRAVE,
  ACCENT_A_GRAVE,
  ACCENT_U_GRAVE,
  ACCENT_I_TREMA,
  NUM_PADS
};

// "tap-hold"
typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

// custom tap dance
enum {
    TD_ESC,
    TD_TAB,
    TD_O,
    TD_P,
    TD_L,
    TD_SCLN
};

bool is_hold_tapdance_disabled = false;

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
 * | Ctrl | Num  |Accent| Alt  |  GUI |Lower |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_grid(
    TD(TD_TAB),    KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    TD(TD_O),    TD(TD_P),   KC_BSPC,
    TD(TD_ESC),    KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    TD(TD_L),    TD(TD_SCLN),KC_QUOT,
    KC_LSFT,       KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,      KC_SLSH,    KC_ENT ,
    KC_LCTL,       NUM_PADS, ACCENTS, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  RAISE,   KC_LEFT, KC_DOWN,     KC_UP,      KC_RGHT
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
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
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
 * |      |     |      |      |      |      |      |      |      |      |      | Reset |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |AGnorm|AGswap|      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_grid(
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, RESET,
    _______, _______, _______, _______, _______, AG_NORM, AG_SWAP, _______, _______, _______,  _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
),

/* Arrows
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
[_ARROWS] = LAYOUT_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
  _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
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

/* Accents
 * ,-----------------------------------------------------------------------------------.
 * |   `  |      |      |  è   |  €   |      |   ^  |      |  ï   |  œ   |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  à   |      |      |      |      |      |      |      |      |      |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ACCENTS] = LAYOUT_grid(
  KC_GRV,  _______,        _______, ACCENT_E_GRAVE, KC_5,    _______, KC_6,    _______, ACCENT_I_TREMA, KC_X,    _______, _______,
  _______, ACCENT_A_GRAVE, _______, _______,        _______, _______, _______, _______, _______,        _______, _______, ACCENT_TREMA,
  _______, _______,        _______, _______,        _______, _______, _______, _______, _______,        _______, _______, _______,
  _______, _______,        _______, _______,        _______, _______, _______, _______, _______,        _______, _______, _______
)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  qk_tap_dance_action_t *action;

  switch (keycode) {
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

     case ACCENTS:
       if (record->event.pressed) {
           is_hold_tapdance_disabled = true;
           register_code(KC_RALT);
           layer_on(_ACCENTS);
       } else {
           unregister_code(KC_RALT);
           layer_off(_ACCENTS);
           is_hold_tapdance_disabled = false;
       }
       break;

     case ACCENT_E_GRAVE:
       if (record->event.pressed) {
           register_code(KC_GRV);
       } else {
           unregister_code(KC_GRV);
           unregister_code(KC_RALT);
           register_code(KC_E);
           unregister_code(KC_E);

           layer_off(_ACCENTS);
           layer_on(_QWERTY);
       }
       break;

     case ACCENT_A_GRAVE:
       if (record->event.pressed) {
           register_code(KC_GRV);
       } else {
           unregister_code(KC_GRV);
           unregister_code(KC_RALT);
           register_code(KC_A);
           unregister_code(KC_A);

           layer_off(_ACCENTS);
           layer_on(_QWERTY);
       }
       break;

     case ACCENT_U_GRAVE:
       if (record->event.pressed) {
           register_code(KC_GRV);
       } else {
           unregister_code(KC_GRV);
           unregister_code(KC_RALT);
           register_code(KC_U);
           unregister_code(KC_U);

           layer_off(_ACCENTS);
           layer_on(_QWERTY);
       }
       break;

     case ACCENT_I_TREMA:
       if (record->event.pressed) {
           register_code(KC_LSFT);
           register_code(KC_QUOT);
           unregister_code(KC_QUOT);
       } else {
           unregister_code(KC_LSFT);
           unregister_code(KC_RALT);
           register_code(KC_I);
           unregister_code(KC_I);

           layer_off(_ACCENTS);
           layer_on(_QWERTY);
       }
       break;

     case ACCENT_TREMA:
       if (record->event.pressed) {
           register_code(KC_LSFT);
           register_code(KC_QUOT);
       } else {
           unregister_code(KC_QUOT);
           unregister_code(KC_LSFT);

           layer_off(_ACCENTS);
           layer_on(_QWERTY);
       }
       break;

     // list all tap dance keycodes with tap-hold configurations
     // default tap for `hold tap dance`
     case TD(TD_O):
     case TD(TD_ESC):
     case TD(TD_TAB):
     case TD(TD_P):
     case TD(TD_L):
     case TD(TD_SCLN):
       action = &tap_dance_actions[TD_INDEX(keycode)];
       if (!record->event.pressed && action->state.count && !action->state.finished) {
           tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
           tap_code16(tap_hold->tap);
       }

       if (keycode == TD(TD_ESC) && !record->event.pressed) {
           layer_off(_ARROWS);
           is_hold_tapdance_disabled = false;
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

void tap_dance_tap_hold_reset(qk_tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

void tap_dance_tap_hold_finished_layout(qk_tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    is_hold_tapdance_disabled = true;

    if (state->pressed) {
        layer_on(tap_hold->hold);

        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            tap_hold->held = tap_hold->hold;
        } else {
            // don t register tap
            // in case of arrow navigation, it prevent to send KC_ESC
            // register_code16(tap_hold->tap);

            tap_hold->held = 0;
            is_hold_tapdance_disabled = false;
        }
    }
}

void tap_dance_tap_hold_reset_layout(qk_tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    is_hold_tapdance_disabled = false;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

#define ACTION_TAP_DANCE_TAP_HOLD_LAYOUT(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished_layout, tap_dance_tap_hold_reset_layout}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_ESC] = ACTION_TAP_DANCE_TAP_HOLD_LAYOUT(KC_ESC, _ARROWS),
    [TD_TAB] = ACTION_TAP_DANCE_TAP_HOLD(KC_TAB, KC_TILD),
    [TD_O] = ACTION_TAP_DANCE_TAP_HOLD(KC_O, KC_LPRN),
    [TD_P] = ACTION_TAP_DANCE_TAP_HOLD(KC_P, KC_RPRN),
    [TD_L] = ACTION_TAP_DANCE_TAP_HOLD(KC_L, KC_LCBR),
    [TD_SCLN] = ACTION_TAP_DANCE_TAP_HOLD(KC_SCLN, KC_RCBR)
};

// Set a long-ish tapping term for tap-dance keys
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_TAP_DANCE_MAX:
            return 275;
            break;
        case TD(TD_ESC):
            return 120;
            break;
        default:
            return TAPPING_TERM;
            break;
    }
}
