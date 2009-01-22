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

#ifndef __DINDIN_GLOBAL_H_
#define __DINDIN_GLOBAL_H_

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

#define PROJECTION_LEFT   -5.0
#define PROJECTION_RIGHT   5.0
#define PROJECTION_TOP     5.0
#define PROJECTION_BOTTOM -5.0
#define PROJECTION_NEAR    9.1
#define PROJECTION_FAR     50.0

enum _KEYBOARD_KEY {
	KEY_RIGHT = 0,
	KEY_LEFT,
	KEY_UP,
	KEY_DOWN,
	KEY_PAGEUP,
	KEY_PAGEDOWN,
	KEY_ENTER,
	KEY_ESC,
	KEY_Y,
	KEY_UNKNOWN,
};

typedef enum _KEYBOARD_KEY KEYBOARD_KEY;

struct _Vertex {
	float x;
	float y;
	float z;
};

typedef struct _Vertex Vertex;

#include "state.h"
#endif
