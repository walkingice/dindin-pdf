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

#ifndef __FIRST_ANIMATION_H_
#define __FIRST_ANIMATION_H_

#include <GL/gl.h>

#include "list.h"
#include "slide.h"

void clear_slip_animation();
int have_next_frame_slip_right();
int have_next_frame_slip_left();
void exec_slip_animation(Slide *slide_now, Slide *slide_next);
#endif
