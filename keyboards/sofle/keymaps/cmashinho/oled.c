 /* Copyright 2020 Josef Adamcik
  * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

//Sets up what the OLED screens display.

#ifdef OLED_ENABLE

static void render_logo(int LUNA_X, int LUNA_Y) {
    static const char PROGMEM luna_logo[] = {
        0x00, 0x00, 0x04, 0xf6, 0xb8, 0xf8, 0xd8, 0xf0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0,
        0xe0, 0xf0, 0xf0, 0xf0, 0xf0, 0xe0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x80, 0xc0, 0xe1, 0xf3, 0xfb, 0x7f, 0x1f, 0x0f, 0x00, 0x00, 0xf0, 0xff, 0xff, 0x3f, 0x03,
        0x01, 0x00, 0x00, 0x00, 0x80, 0xc1, 0xf3, 0xff, 0x7f, 0x1f, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x30,
        0x1e, 0x3f, 0x3f, 0x7f, 0xf9, 0xf0, 0xf0, 0x70, 0x78, 0x3c, 0x3f, 0x1f, 0x0f, 0x03, 0x00, 0x00,
        0x00, 0x00, 0x1c, 0x3f, 0x7f, 0x7f, 0xfb, 0xf1, 0xf0, 0x78, 0x3c, 0x1e, 0x0f, 0x03, 0x00, 0x00,
        };
    oled_set_cursor(LUNA_X,LUNA_Y);
    oled_write_raw_P(luna_logo, sizeof(luna_logo));
}

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n\n"), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("qwrt"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("clmk"), false);
            break;
        default:
            oled_write_P(PSTR("mod\n"), false);
            break;
    }
    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    switch (get_highest_layer(layer_state)) {
        case 0:
        case 1:
            oled_write_P(PSTR("B\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("R"), false);
            break;
        case 3:
            oled_write_P(PSTR("L"), false);
            break;
        default:
            oled_write_ln_P(PSTR("undef"), false);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo(0,2); //Not defining this in config.h will save space (+112).

        /* wpm counter */
        oled_set_cursor(0,13);
        oled_write_P(PSTR("WPM: "), false);
        oled_write(get_u8_str(get_current_wpm(), ' '), false);
    }
    return false;
}

#endif
