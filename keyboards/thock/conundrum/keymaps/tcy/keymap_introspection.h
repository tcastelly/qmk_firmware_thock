#pragma once
/* Stand-in for modern QMK's generated keymap_introspection.h, which the
 * canonical shared_tcy/tcy.c includes (its keymap_key_to_keycode override
 * calls keycode_at_keymap_location). The frozen base has neither; the
 * implementation lives in keymap.c, where keymaps[] and its size are
 * visible. Found via -I on the keymap dir (see rules.mk). */
#include <stdint.h>

uint16_t keycode_at_keymap_location(uint8_t layer_num, uint8_t row, uint8_t column);
