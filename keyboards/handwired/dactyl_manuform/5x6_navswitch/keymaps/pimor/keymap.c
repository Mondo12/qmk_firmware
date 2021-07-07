#include QMK_KEYBOARD_H
#include "pimoroni_trackball.h"
#include "i2c_master.h"

enum layer_names {
    _BASE,
    _LOWER,
    _RAISE
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

  [_BASE] = LAYOUT_5x6(
     KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_MINS,
     KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                         KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_BSPC,
     KC_LSFT, KC_A  , KC_S , KC_D , KC_F  , KC_G  ,                           KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN ,KC_QUOT,
     KC_LCTL, KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  ,                         KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_BSLS,
                      KC_LBRC,KC_RBRC,                                                       KC_PLUS, KC_EQL,
                                      MO(1) ,KC_ENT,                           KC_SPC, MO(2),
                                      KC_TAB, KC_HOME,                        KC_END,  KC_DEL,
                                      KC_DEL, KC_GRV,                        KC_LGUI, KC_LALT,
       KC_LEFT, KC_UP ,KC_DOWN, KC_RGHT, KC_ENT,                                   KC_UP, KC_LEFT ,KC_ENT, KC_DOWN, KC_RGHT 
  ),

  [_LOWER] = LAYOUT_5x6(
     KC_TILD,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,                        KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_DEL,
     _______,KC_PGUP,KC_UP,KC_PGDN,_______,KC_LBRC,                        KC_RBRC, KC_P7 , KC_P8 , KC_P9 ,KC_PLUS,_______,
     KC_HOME,KC_LEFT,KC_DOWN,KC_RGHT,KC_END ,KC_LPRN,                        KC_RPRN, KC_P4 , KC_P5 , KC_P6 ,KC_MINS,KC_BSLS,
     _______,_______,_______,_______,_______,_______,                        KC_P0,   KC_P1 , KC_P2 , KC_P3 ,KC_EQL ,KC_UNDS,
                    _______,_______,                                                        _______, _______,
                                             _______,_______,            _______,_______,
                                             _______,_______,            _______,_______,
                                             _______,_______,            _______,_______,
        KC_LEFT, KC_UP ,KC_DOWN, KC_RGHT, KC_ENT,                                   KC_UP, LCTL(LSFT(KC_TAB)) ,KC_ENT, KC_DOWN, LCTL(KC_TAB) 
  ),

  [_RAISE] = LAYOUT_5x6(
       KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                        KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
       BALL_HUI,BALL_WHT,_______,_______,BALL_SCR,KC_LBRC,                        KC_RBRC,_______,_______,_______,_______,_______,
       BALL_DEC,_______,BALL_MCL,BALL_RCL,BALL_NCL,KC_LPRN,                        KC_RPRN,_______,_______,_______,_______,KC_VOLU,
       _______,_______,_______,_______,_______,_______,                        _______,_______,_______,_______,KC_MUTE,KC_VOLD,
                       _______,_______,                                                        _______ ,_______,
                                               _______,_______,            _______,_______,
                                               _______,_______,            _______,_______,
                                               _______,_______,            _______,_______,
        KC_LEFT, KC_UP ,KC_DOWN, KC_RGHT, KC_ENT,                                   KC_UP, KC_LEFT ,KC_ENT, KC_DOWN, KC_RGHT 
  )
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
    }
    return state;
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
	switch(get_highest_layer(layer_state)){
		case _RAISE:
		if (clockwise) {
            tap_code16(C(KC_TAB));
        } else {
            tap_code16(S(C(KC_TAB)));
        }		
		default:
		if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
	}
    return true;
}
#endif
