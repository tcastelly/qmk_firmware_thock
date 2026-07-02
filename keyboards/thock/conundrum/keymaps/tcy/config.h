#pragma once

/* Mousekey timing: the frozen base's defaults are the ancient X11-style ones
 * (MOUSEKEY_DELAY 300 — a 300ms pause after the first 1px move, INTERVAL 50
 * = 20fps). Use modern QMK's defaults instead so the _ESC layer mouse keys
 * feel like the EC boards. */
#define MOUSEKEY_DELAY 10
#define MOUSEKEY_INTERVAL 20
#define MOUSEKEY_MOVE_DELTA 8
#define MOUSEKEY_MAX_SPEED 10
#define MOUSEKEY_TIME_TO_MAX 30
#define MOUSEKEY_WHEEL_DELAY 10
#define MOUSEKEY_WHEEL_INTERVAL 80
#define MOUSEKEY_WHEEL_MAX_SPEED 8
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40
