#pragma once

#include "quantum.h"

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

#define LAYOUT(\
    L00, L01, L02, L03, L04, L05,               R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15,               R10, R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25,               R20, R21, R22, R23, R24, R25, \
                        L26, L16, L06,     R06, R16, R26\
) {\
    {L06, L00, L01, L02, L03, L04, L05},\
    {L16, L10, L11, L12, L13, L14, L15},\
    {L26, L20, L21, L22, L23, L24, L25},\
    {R00, R01, R02, R03, R04, R05, R06},\
    {R10, R11, R12, R13, R14, R15, R16},\
    {R20, R21, R22, R23, R24, R25, R26},\
}

