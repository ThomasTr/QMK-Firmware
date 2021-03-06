#include QMK_KEYBOARD_H
#include <print.h>
#include "sendstring_german.h"

/*
Changes:
KC_NUBS instead of MOD(1) for the key right from the left shift
Switched the left KC_LGUI &  KC_LALT
Replaced KC_RALT with KC_RGUI
Replaced MO(1) at Row 1 with KC_RALT
Replaced KC_RCTL with MO(1)
Replaced KC_LSFT with KC_LSPO -- Reverted back, since double shift needed for PHPStorm
Replaced KC_RSFT with KC_RSPC -- Reverted back, since it causes wrong typings
CAPS is now a “layer tap” where it serves as CAPSLOCK when tapped but brings up layer 1 when held.
Added KC_POWER instead ESC on layer1
Added media controls in layer1
Added macros for power led off & alfred sleep since leds wont switch off when mac sleeps
Added several macros for typical progamming needs

Instructions:
Make:  make kbdfans/kbd75/rev2:thomastr
Bring keybord in bootloader mode: unplug, press Space + b and plug or better: FN + backspace
Flash: make kbdfans/kbd75/rev2:thomastr:dfu


Light control:
FN is currently Entf on row 1 or POS1 on row 6

Q - Toggle (on/off)
W - Cycle trough modes
E - Increase hue (color)
R - Decrease hue
T - Increase saturation
Z - Decrease saturation
U - Increase value (brightness)
I - Decrease value

C - Decrease the backlight level
V - Turn the backlight on or off
B - Increase the backlight level
N - Cycle through backlight levels  

 Explanations:
 LT(1, KC_CAPS) Switch to layer 1 when hold, TAB when tapped
*/

enum custom_keycodes {
  LED_PWR_OFF = SAFE_RANGE,
  LED_PWR_ON,
  ARROW_LEFT,
  DBL_ARROW,
  BSLASH,
  SBRKTS,
  TS_EQUAL,
  TS_NEQUAL,
  AND
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {

    /* Switch RGB & backlight off, send LGUI & space for alfred, type sleep and press return to send mac to sleep */
    case LED_PWR_OFF:
      if (record->event.pressed) {

        SEND_STRING(SS_LGUI(" "));
        _delay_ms(200);
        SEND_STRING("sleep"SS_TAP(X_ENTER));

        backlight_disable();
        rgblight_disable();
      } 
    break;

    /* Switch RGB & backlight on, press return to wake mac up from sleep */
    case LED_PWR_ON:
      if (record->event.pressed) {

        SEND_STRING(SS_TAP(X_ENTER));

        backlight_enable();
        rgblight_enable();
      } 
    break;

    /* Type minus & arrow left: -> */
    case ARROW_LEFT:
      if (record->event.pressed) {
        SEND_STRING("->");
      } 
    break;

    /* Type equal & arrow left: => */
    case DBL_ARROW:
      if (record->event.pressed) {
        SEND_STRING("=>");
      } 
    break;

    /* Type backslash: \ */
    case BSLASH:
      if (record->event.pressed) {
        SEND_STRING(SS_RALT(SS_RSFT("7")));
      } 
    break;

    /* Type open & closing square brackets: \ */
    case SBRKTS:
      if (record->event.pressed) {
        SEND_STRING(SS_RALT("5")SS_RSFT("#"));
      } 
    break;

    /* Type save equal: === */
    case TS_EQUAL:
      if (record->event.pressed) {
        SEND_STRING(SS_RSFT("000"));
      } 
    break;    

    /* Type save not equal: !== */
    case TS_NEQUAL:
      if (record->event.pressed) {
        SEND_STRING(SS_RSFT("100"));
      } 
    break;  

    /* Type save not equal: !== */
    case AND:
      if (record->event.pressed) {
        SEND_STRING(SS_RSFT("66"));
      } 
    break;  

  }
  return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
    KC_ESC,         KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,      KC_F12,    KC_PSCR,    MO(1),       KC_DEL,
    KC_GRV,         KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,     KC_EQL,    KC_DEL,     KC_BSPC,     KC_HOME,
    KC_TAB,         KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,     KC_RBRC,   KC_BSLS,                 KC_PGUP,
    LT(1, KC_CAPS), KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,                            KC_ENT,      KC_PGDN,
    KC_LSFT,        KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,     KC_RSFT,               KC_UP,       KC_END,
    KC_LCTL,        KC_LALT,  KC_LGUI,                      KC_SPC,   KC_SPC,   KC_SPC,                       KC_RGUI,  KC_RALT,     MO(1),     KC_LEFT,    KC_DOWN,     KC_RGHT
  ),

	[1] = LAYOUT(
    _______,        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC__MUTE, KC__VOLDOWN, KC__VOLUP, LED_PWR_ON, _______,     LED_PWR_OFF,
    _______,        TS_NEQUAL,_______,  _______,  _______,  SBRKTS,   AND,      BSLASH,   _______,  _______,  TS_EQUAL, _______,     _______,   _______,    RESET,       _______,
    _______,        RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_HUD,  RGB_SAI,  RGB_SAD,  RGB_VAI,  RGB_VAD,  _______,  _______,  _______,     _______,   _______,                 _______,
    _______,        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                            _______,     _______,
    _______,        DBL_ARROW,_______,  _______,  BL_DEC,   BL_TOGG,  BL_INC,   BL_STEP,  _______,  _______,  _______,  ARROW_LEFT,     _______,               LED_PWR_ON,  _______,
    _______,        _______,  _______,                      _______,  _______,  _______,                      _______,  _______,     _______,   _______,    LED_PWR_OFF, _______
  )

};
