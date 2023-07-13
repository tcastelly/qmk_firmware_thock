
#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFFFE
#define PRODUCT_ID      0x0009
#define DEVICE_VER      0x0001
#define MANUFACTURER    a bit keys
#define PRODUCT         mc2s lp
#define DESCRIPTION     hid keyboard

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 7

#define MATRIX_ROW_PINS       { B0, B1, B2 }
#define MATRIX_COL_PINS       { D6, D5, D4, C7, C6, B6, B5 }
#define MATRIX_ROW_PINS_RIGHT { B0, B1, B2 }
#define MATRIX_COL_PINS_RIGHT { B5, B6, C6, C7, D4, D5, D6 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Split Keyboard specific options */
#define SPLIT_HAND_PIN E6  /*fix pin. HIGH is left, LOW is right */
#define SOFT_SERIAL_PIN D3 /* serial communication pin */

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

