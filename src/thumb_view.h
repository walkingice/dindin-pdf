/*
 *   Copyright (C) 2009 Julian Chu(Walkingice)
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

#ifndef __SHOW_THUMBNAIL_H_
#define __SHOW_THUMBNAIL_H_

#include "global.h"
#include "list.h"

#define CURSOR_ANIMATION

#define THUMB_ROW_NUM 5
#define ROW_PER_PAGE 5

#define SET_THUMB_LOCATION(_cord, _x, _y, _z) \
	{ \
	_cord.x = _x; \
	_cord.y = _y; \
	_cord.z = _z; \
	}while(0)

struct _Quard {
	Vertex lt; 
	Vertex rt; 
	Vertex rb; 
	Vertex lb; 
};
typedef struct _Quard Quard;

void init_thumb_view(struct list_head* head, void (*display)());
void show_thumbnail();
void move_cursor_by_keyboard(KEYBOARD_KEY key);
void set_cursor(int new_cursor);
int get_cursor();

#endif
