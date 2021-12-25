#include QMK_KEYBOARD_H

enum layers_user {
    _QWERTY,
    _AD
};

enum keycodes_user {
    _BASEEF = SAFE_RANGE,
    _KITTEF
};

int selected_mode_user = RGB_MATRIX_CUSTOM_base_effect; // for layer_state_set_user()
bool process_record_user(uint16_t keycode, keyrecord_t * record) {
    switch (keycode) {
        case _BASEEF:
            if (record->event.pressed) {
                selected_mode_user = RGB_MATRIX_CUSTOM_base_effect;
            }
            return false;
        case _KITTEF:
            if (record->event.pressed) {
                selected_mode_user = RGB_MATRIX_CUSTOM_kitt_effect;
            }
            return false;
        default:
            return true;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_65_ansi(
        KC_GESC,        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
        KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        CTL_T(KC_CAPS), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGDN,
        KC_LSFT,                 KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
        KC_LCTL,        KC_LGUI, KC_LALT,                            KC_SPC,                    KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_AD] = LAYOUT_65_ansi(
        KC_GESC,        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_HOME,
        _______,        RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, KC_PSCR, KC_SLCK, KC_PAUS, _______,   KC_PGUP,
        CTL_T(KC_CAPS), RGB_SPI, RGB_SPD, _______, _______, _______, _______, _______, _______, _______, _______, _______,          EEP_RST, KC_PGDN,
        KC_LSFT,                 _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______, KC_MPLY, KC_VOLU, KC_MUTE,
        _______,        _______, _______,                            _______,                   _______, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _QWERTY:
            rgb_matrix_mode(selected_mode_user);
            break;
        case _AD:
            if (selected_mode_user == RGB_MATRIX_CUSTOM_base_effect) {
                rgb_matrix_mode(RGB_MATRIX_CUSTOM_base_ad_effect);
            } else {
                rgb_matrix_mode(selected_mode_user);
            }
            break;
    }

    return state;
}
