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

#ifndef __SHOW_SLIDE_
#define __SHOW_SLIDE_

#include "list.h"
#include "global.h"

void init_slide_view(struct list_head* slides_head, void (*display)());
void show_slide();
int get_slide_index();
void set_slide(int new_slide);
void change_slide(KEYBOARD_KEY key);
void change_slide_by_keyboard(KEYBOARD_KEY key);
#endif
