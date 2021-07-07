#pragma once

#include "dactyl_manuform.h"
#include "quantum.h"

#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
  #include <avr/io.h>
  #include <avr/interrupt.h>
#endif
#endif

#define LAYOUT_5x6(\
  L00, L01, L02, L03, L04, L05,                          R01, R02, R03, R04, R05, R06, \
  L10, L11, L12, L13, L14, L15,                          R11, R12, R13, R14, R15, R16, \
  L20, L21, L22, L23, L24, L25,                          R21, R22, R23, R24, R25, R26, \
  L30, L31, L32, L33, L34, L35,                          R31, R32, R33, R34, R35, R36, \
            L42, L43,                                              R43, R44,           \
                      L44, L45,                          R41, R42,                     \
                                L54, L55,      R51, R52,                               \
                                L52, L53,      R53, R54,                               \
    L06, L16, L26, L36, L46,                                R00, R10, R20, R30, R40    \
  ) \
  { \
    { L00,   L01,   L02, L03, L04, L05, L06 },     \
    { L10,   L11,   L12, L13, L14, L15, L16 },     \
    { L20,   L21,   L22, L23, L24, L25, L26 },     \
    { L30,   L31,   L32, L33, L34, L35, L36 },     \
    { KC_NO, KC_NO, L42, L43, L44, L45, L46 },     \
    { KC_NO, KC_NO, L52, L53, L54, L55, KC_NO },   \
                                                   \
    { R00,   R01, R02, R03, R04,   R05,   R06 },   \
    { R10,   R11, R12, R13, R14,   R15,   R16 },   \
    { R20,   R21, R22, R23, R24,   R25,   R26 },   \
    { R30,   R31, R32, R33, R34,   R35,   R36 },   \
    { R40,   R41, R42, R43, R44,   KC_NO, KC_NO }, \
    { KC_NO, R51, R52, R53, R54,   KC_NO, KC_NO }  \
}
