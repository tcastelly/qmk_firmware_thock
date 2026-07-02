/* Compile the canonical (shared) tcy.c on the thock's frozen base:
 * QMK headers first (define qk_tap_dance_*_t, KC_*), then the adapter
 * (typedefs/aliases), then the unmodified canonical source. */
#include QMK_KEYBOARD_H
#include "tcy_compat.h"
#include "tcy.h"
#include "tcy.c"
