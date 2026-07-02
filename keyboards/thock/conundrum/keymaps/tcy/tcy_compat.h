#pragma once
/*
 * tcy_compat.h — bridges the canonical users/tcy code (current QMK API) onto
 * the thock's frozen pre-2022 base.  Must be included AFTER QMK_KEYBOARD_H
 * (so qk_tap_dance_*_t and KC_* already exist) and BEFORE tapdance.h/tcy.c.
 * The wrappers and keymap.c do exactly that.
 *
 * The tap-dance struct is identical field-for-field on this base (count,
 * weak_mods, interrupted, pressed, finished, ...) — only the type *name*
 * changed upstream (qk_ prefix dropped).  So a typedef is all it takes.
 */

// layer state was a raw uint32_t on this base; current code uses layer_state_t
typedef uint32_t layer_state_t;

// tap-dance type rename (qk_* -> *)
typedef qk_tap_dance_state_t  tap_dance_state_t;
typedef qk_tap_dance_action_t tap_dance_action_t;

// keycode renames (this base predates the qk_-cleanup keycode renames)
#define MS_BTN1 KC_MS_BTN1
#define MS_BTN2 KC_MS_BTN2
#ifndef QK_BOOT
#  define QK_BOOT RESET
#endif

// layer-state helper added after this base
#ifndef IS_LAYER_ON_STATE
#  define IS_LAYER_ON_STATE(state, layer) ((bool)((state) & ((layer_state_t)1 << (layer))))
#endif

// tap-dance helpers added after this base
#ifndef TD_INDEX
#  define TD_INDEX(code) ((code) & 0xFF)
#endif
// modern tap_dance_get_state(i); old base exposes the state inside the action table
#define tap_dance_get_state(idx) (&tap_dance_actions[(idx)].state)

// get_highest_layer() was named biton32() on this base
#ifndef get_highest_layer
#  define get_highest_layer(state) biton32(state)
#endif
