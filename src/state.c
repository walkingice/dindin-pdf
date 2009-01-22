/*
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "state.h"

static STATE now_state;

static STATE thumbnail_to_next(KEYBOARD_KEY key);
static STATE slide_to_next(KEYBOARD_KEY key);
static STATE check_exit_to_next(KEYBOARD_KEY key);

/**
 * @brief Get the state of now
 */
STATE get_state() {
	return now_state;
}

/**
 * @brief Set the state of now
 * @param The new state what will be set
 */
void set_state(STATE state) {
	now_state = state;
}

/**
 * @brief calculate the next state by key. It doesn't set the state.
 * @param key The keycode of the key pressed by user
 * @return The next state
 */
STATE get_state_by_key(KEYBOARD_KEY key) {
	STATE now = get_state();
	if (now == SHOW_THUMBNAIL) {
		return thumbnail_to_next(key);
	}else if(now == SHOW_SLIDE) {
		return slide_to_next(key);
	}else if (now == CHECK_EXIT_OR_NOT) {
		return check_exit_to_next(key);
	}
	return NOTHING_HAPPENED;
}

static STATE thumbnail_to_next(KEYBOARD_KEY key) {
	if(key == KEY_ENTER) {
		return SHOW_SLIDE;
	}else if (key == KEY_ESC) {
		return CHECK_EXIT_OR_NOT;
	}

	return SHOW_THUMBNAIL;;
}

static STATE slide_to_next(KEYBOARD_KEY key) {
	if(key == KEY_ESC) {
		return SHOW_THUMBNAIL;
	}
	return SHOW_SLIDE;
}

static STATE check_exit_to_next(KEYBOARD_KEY key) {
	if(key == KEY_Y) {
		return EXIT;
	}else {
		return SHOW_THUMBNAIL;
	}
}
