#include "dactyl.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#include "keymap_german.h"

#include "keymap_nordic.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE] = KEYMAP(
                  // Left hand
     KC_ESCAPE,     KC_1,     KC_2,          KC_3,           KC_4,           KC_5,
     KC_TAB,        KC_Q,     KC_W,          KC_E,           KC_R,           KC_T,
     KC_TRANSPARENT,KC_A,     KC_S,          KC_D,           KC_F,           KC_G,
     KC_TRANSPARENT,KC_Z,     KC_X,          KC_C,           KC_V,           KC_B, 
     KC_GRAVE,      KC_QUOTE, KC_TRANSPARENT,KC_TRANSPARENT, KC_TRANSPARENT,

                                                       OSL(1), KC_LGUI,
                                                               ALL_T(KC_HOME),
                           CTL_T(KC_BSPACE), ALT_T(KC_DELETE), SFT_T(KC_END),

     // Right hand
     KC_6,          KC_7,          KC_8,         KC_9,           KC_0,           KC_MINUS,
     KC_Y,          KC_U,          KC_I,         KC_O,           KC_P,           KC_BSLASH,
     KC_H,          KC_J,          KC_K,         KC_L,           KC_SCOLON,      KC_QUOTE,
     KC_N,          KC_M,          KC_COMMA,     KC_DOT,         KC_KP_SLASH,    KC_DQUO,
                    KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT, KC_TRANSPARENT,
     
     KC_RALT,          TT(2),
     ALL_T(KC_PGUP),
     SFT_T(KC_PGDOWN), ALT_T(KC_ENTER), CTL_T(KC_SPACE)),

  [SYMB] = KEYMAP(
     // Left hand
     M(0)           ,KC_F1,   KC_F2,   KC_F3,      KC_F4,       KC_F5,
     KC_TRANSPARENT ,KC_EXLM, KC_AT,   KC_LCBR,    KC_RCBR,     KC_PIPE,
     KC_TRANSPARENT ,KC_HASH, KC_DLR,  KC_LPRN,    KC_RPRN,     KC_GRAVE,
     KC_TRANSPARENT, KC_PERC, KC_CIRC, KC_LBRACKET,KC_RBRACKET, KC_TILD, 
     KC_TRANSPARENT ,KC_AMPR, KC_QUES, KC_LABK,    KC_RABK,

                                                KC_TRANSPARENT, KC_TRANSPARENT,
                                                                KC_TRANSPARENT,
                                  KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,

     // Right hand
     KC_F6,         KC_F7,    KC_F8,    KC_F9,KC_F10,        KC_F11,
     KC_KP_SLASH,   KC_7,     KC_8,     KC_9, KC_KP_MINUS,   KC_F12,
     KC_KP_ASTERISK,KC_4,     KC_5,     KC_6, KC_PLUS,       KC_TRANSPARENT,
     KC_TRANSPARENT,KC_1,     KC_2,     KC_3, KC_EQUAL,      KC_TRANSPARENT,
                    KC_KP_0,  KC_KP_DOT,KC_0, KC_CIRC,       KC_TRANSPARENT,

     KC_TRANSPARENT,KC_TRANSPARENT,
     KC_TRANSPARENT,
     KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT),

  [MDIA] = KEYMAP(
     // Left hand
     KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
     KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
     KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
     KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
     KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,

                                                                 KC_TRANSPARENT,KC_TRANSPARENT,
                                                                                KC_TRANSPARENT,     
                                                  KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,

     // Right hand
     KC_TRANSPARENT,     KC_TRANSPARENT,   KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,KC_TRANSPARENT,
     KC_TRANSPARENT,KC_MEDIA_NEXT_TRACK,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_AUDIO_MUTE,KC_TRANSPARENT,
     KC_TRANSPARENT,KC_LEFT,            KC_DOWN,          KC_UP,          KC_RIGHT,     KC_TRANSPARENT,
     KC_TRANSPARENT,KC_MS_LEFT,         KC_MS_DOWN,       KC_MS_UP,       KC_MS_RIGHT,  KC_TRANSPARENT,
                    KC_MS_BTN1,         KC_MS_BTN3,       KC_MS_BTN2,    KC_TRANSPARENT,KC_TRANSPARENT,
     
     KC_TRANSPARENT,KC_TRANSPARENT,
     KC_TRANSPARENT,
     KC_TRANSPARENT,KC_WWW_BACK,KC_WWW_FORWARD),

};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(1)
};

// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
      break;
    
  }
  return true;
}

void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    dactyl_board_led_off();
    dactyl_right_led_1_off();
    dactyl_right_led_2_off();
    dactyl_right_led_3_off();
    switch (layer) {
        case 1:
            dactyl_right_led_1_on();
            break;
        case 2:
            dactyl_right_led_2_on();
            break;
        case 3:
            dactyl_right_led_3_on();
            break;
        case 4:
            dactyl_right_led_1_on();
            dactyl_right_led_2_on();
            break;
        case 5:
            dactyl_right_led_1_on();
            dactyl_right_led_3_on();
            break;
        case 6:
            dactyl_right_led_2_on();
            dactyl_right_led_3_on();
            break;
        case 7:
            dactyl_right_led_1_on();
            dactyl_right_led_2_on();
            dactyl_right_led_3_on();
            break;
        default:
            break;
    }

};
