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

#ifndef __STATE_H_
#define __STATE_H_

#include "global.h"

enum _STATE {
        SHOW_THUMBNAIL = 0,
	SHOW_SLIDE,
	NOTHING_HAPPENED,
	CHECK_EXIT_OR_NOT,
	EXIT,
};

typedef enum _STATE STATE;

STATE get_state();
void set_state(STATE state);
STATE get_state_by_key(KEYBOARD_KEY key);
#endif
