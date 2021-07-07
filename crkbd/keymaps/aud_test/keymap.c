#include QMK_KEYBOARD_H
#include "pimoroni_trackball.h"
#include "pointing_device.h"
#include "i2c_master.h"

enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  BALL_HUI,//cycles hue
  BALL_WHT,//cycles white
  BALL_DEC,//decreased color
  BALL_SCR,//scrolls
  BALL_NCL,//left click
  BALL_RCL,//right click
  BALL_MCL,//middle click
};
void keyboard_post_init_user(void) { i2c_init(); }


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
        KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T,     KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G,     KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,    KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                       KC_LCTL, KC_ENT, MO(1),    MO(2), KC_SPC, KC_RALT ),
    [_LOWER] = LAYOUT_split_3x6_3(
        KC_ESC, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,        KC_CIRC, KC_7, KC_8, KC_9, KC_RPRN, KC_BSPC,
        KC_TAB, KC_BTN3, KC_BTN2, KC_BTN1, BALL_SCR,XXXXXXX,     XXXXXXX, KC_4, KC_5,KC_6, XXXXXXX, XXXXXXX,
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX,     KC_0, KC_1, KC_2, KC_3, XXXXXXX, XXXXXXX,
                               KC_LCTL, KC_SPC, _______,         MO(3),KC_ENT, KC_RALT ),
    [_RAISE] = LAYOUT_split_3x6_3(
        KC_TAB, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,         KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
        KC_LCTL, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, XXXXXXX,      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, KC_GRV,
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
                                   KC_LGUI, KC_SPC, MO(3),         _______,KC_ENT, KC_RALT ),
    [_ADJUST] = LAYOUT_split_3x6_3(
        RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,     BALL_DEC, BALL_HUI, BALL_WHT, XXXXXXX, XXXXXXX, XXXXXXX,
        RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                    KC_LGUI, KC_SPC, _______,     _______,KC_ENT, KC_RALT )
};
uint8_t white = 0;
uint8_t red = 255;
uint8_t green = 0;
uint8_t blue = 0;

void ball_increase_hue(void){
      if(red!=255&&green!=255&&blue!=255){
        red =255;
      }
      if (red==255&&green<255&&blue==0){
       green += 15;
      } else if(green==255&&blue==0&&red>0){
        red-=15;
      } else if(red==0&&blue<255&&green==255){
        blue+=15;
      } else if(blue==255&&green>0&&red==0){
        green -= 15;
      } else if(green == 0&&blue==255&&red<255){
        red +=15;
      } else if(green ==0&&blue>0&&red==255){
        blue -=15;
      }
      trackball_set_rgbw(red,green,blue,white);
}

void decrease_color(void){
  if (green>0){
    green-=15;
  }
  if (red>0){
    red-=15;
  }
  if (blue>0){
    blue-=15;
  }
  trackball_set_rgbw(red,green,blue,white);
}

void cycle_white(void){
  if (white<255){
    white +=15;
  } else{
    white=0;
  }
  trackball_set_rgbw(red,green,blue,white);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record){
  switch (keycode){
  case  BALL_HUI:
    if(record->event.pressed){
      ball_increase_hue();
    }
    break;

  case BALL_WHT:
    if(record-> event.pressed){
      cycle_white();
    }
    break;

  case BALL_DEC:
   if(record-> event.pressed){
      decrease_color();
    }
    break;

  case BALL_SCR:
   if(record->event.pressed){
     trackball_set_scrolling(true);
   } else{
     trackball_set_scrolling(false);
   }
   break;

  case BALL_NCL:
     record->event.pressed?register_code(KC_BTN1):unregister_code(KC_BTN1);
     break;
  case BALL_RCL:
      record->event.pressed?register_code(KC_BTN2):unregister_code(KC_BTN2);
      break;
  case BALL_MCL:
      record->event.pressed?register_code(KC_BTN3):unregister_code(KC_BTN3);
      break;
  }
  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(layer_state)) {
        case _BASE:
             trackball_set_rgbw(139,0,139,0x00);
            break;
        case _LOWER:
            trackball_set_rgbw(40,33,139, 0x00);
            break;
        case _RAISE:
             trackball_set_rgbw(1,33,21, 0x00);
            break;
        case _ADJUST:
            trackball_set_rgbw(171,39,79, 0x00);
    }
    return state;
}
