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

/**
 * \file toolkit_glut.h
 * \author Julian Chu (WalkingIce)
 * \date 2009-4-1  <--- !!
 */

#ifndef __DINDIN_TOOLKIT_GTK_H__
#define __DINDIN_TOOLKIT_GTK_H__
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "toolkit.h"

int  gtk_init(toolkit_init_struct* init_info);
void gtk_mainloop();
void gtk_redisplay();
int  gtk_say_byebye();

int set_gtk_callback_idle(void (*ptr_callback_function)());
int set_gtk_callback_display(void (*ptr_callback_function)());
int set_gtk_callback_reshape(void (*ptr_callback_function)(int width, int height));
int set_gtk_callback_keyboard(void (*ptr_callback_function)(KEYBOARD_KEY));

#endif
