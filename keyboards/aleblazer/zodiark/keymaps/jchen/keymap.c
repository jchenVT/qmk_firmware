/*
Copyright 2021 Spencer Deven <splitlogicdesign@gmail.com>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H

enum sofle_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTY,
    _RAISE,
    _GAMER,
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_GAMER,
    KC_RAISE,
};

// Tap Dance names
enum {
    LAYERS,
};

void dance_layers (qk_tap_dance_state_t *state, void *user_data){
    if (state->count == 1) {
        tap_code16(KC_RAISE);
    } else if (state->count == 2) {
        tap_code16(KC_GAMER);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [LAYERS] = ACTION_TAP_DANCE_FN(dance_layers),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_QWERTY] = LAYOUT(
      KC_CAPS,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
      KC_ESC,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  KC_GRV,                               KC_BSLS,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
      KC_LALT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,  KC_LBRC ,                             KC_RBRC,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSPO,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  TO(_RAISE),  KC_MUTE,/*<-encoder->*/KC_RALT, KC_DEL, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
      KC_LCTL,    KC_LGUI, KC_LALT, KC_LALT, KC_DEL,    KC_SPC,    KC_TAB,                     KC_ENT,    KC_BSPC,    KC_LEFT, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

	[_RAISE] = LAYOUT(
      _______, KC_F1, KC_F2, KC_F3, KC_F4,   KC_F5,                                KC_F6,   KC_F7,   KC_F8, KC_F9, KC_F10, KC_F11,
      KC_PSLS, KC_P7, KC_P8, KC_P9, KC_NLCK, _______, _______,                   _______, _______, KC_PSLS, KC_P7, KC_P8, KC_P9, KC_F12,
      KC_CAPS, KC_P4, KC_P5, KC_P6, KC_NLCK, _______, _______,                   _______, _______, _______, KC_P4, KC_P5, KC_P6, KC_NLCK,
      _______, KC_P1, KC_P2, KC_P3, _______, _______, TO(_GAMER), KC_MUTE,       _______, _______, _______, _______, KC_P1, KC_P2, KC_P3, _______,
      _______, KC_P0, KC_PDOT, KC_PENT, _______,     _______,  _______,   _______,    _______,   _______, KC_P0, KC_PDOT, KC_PENT, _______
      ),

	[_GAMER] = LAYOUT(
      KC_CAPS,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
      KC_ESC,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  KC_GRV,                                    KC_BSLS,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
      KC_LALT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,  KC_LBRC,                                   KC_RBRC,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  TO(_QWERTY),     KC_MUTE,/*<-encoder->*/RGB_TOG, KC_DEL, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
      KC_LCTL,    KC_LGUI, KC_LALT, KC_LALT, KC_DEL,    KC_SPC,   KC_TAB,                     KC_ENT,    KC_BSPC,    KC_LEFT, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),


};
#ifdef OLED_ENABLE

/*
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
    };

    oled_write_P(qmk_logo, false);
}
*/

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("MODE"), false);
    oled_write_ln_P(PSTR(""), false);
    if (keymap_config.swap_lctl_lgui) {
        oled_write_ln_P(PSTR("MAC"), false);
    } else {
        oled_write_ln_P(PSTR("WIN"), false);
    }

    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("Qwrt"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case _GAMER:
            oled_write_P(PSTR("Gamer"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

char wpm_str[8] = "WPM:\n";

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        oled_set_cursor(0,0);
        uint8_t wpm = get_current_wpm();
        wpm_str[5] = (wpm / 100) + '0';
        wpm_str[6] = ((wpm / 10) % 10) + '0';
        wpm_str[7] = (wpm % 10) + '0';
        oled_write(wpm_str, false);
    }
    return false;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
            }
            return false;
        case KC_GAMER:
            if (record->event.pressed) {
                layer_on(_GAMER);
            }
            return false;
        case KC_COPY:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_C);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_C);
            }
            return false;
        case KC_PASTE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_V);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_V);
            }
            return false;
        case KC_CUT:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_X);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_X);
            }
            return false;
            break;
        case KC_UNDO:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_LCTL));
                register_code(KC_Z);
            } else {
                unregister_mods(mod_config(MOD_LCTL));
                unregister_code(KC_Z);
            }
            return false;
    }
    return true;
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (!clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
              rgblight_step();
        } else {
           rgblight_step_reverse();
        }
    }
    return true;
}

#endif
