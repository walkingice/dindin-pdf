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

#ifndef __CUBE_ANIMATION_H_
#define __CUBE_ANIMATION_H_

#include "list.h"
#include "slide.h"

void clear_cube_animation();
int have_next_frame_cube_right();
int have_next_frame_cube_left();
void exec_cube_animation_right(Slide *slide_now, Slide *slide_next);
void exec_cube_animation_left(Slide *slide_now, Slide *slide_next);
#endif
