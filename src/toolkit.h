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
 * \file toolkit.h
 * \author Julian Chu (WalkingIce)
 * \date 2009-2-26
 */

#ifndef __DINDIN_TOOLKIT_H__
#define __DINDIN_TOOLKIT_H__
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

struct _toolkit_init_struct {
	int*   cmd_argc;
	char** cmd_argv;

	char* window_name;
	int window_width;
	int window_height;
	int pos_x;
	int pos_y;
};

typedef struct _toolkit_init_struct toolkit_init_struct;

int  toolkit_init(int *argc, char **argv, char *window_name
		, int window_width, int window_height
		, int position_x, int position_y);

void toolkit_mainloop();
void toolkit_redisplay();
int  toolkit_say_byebye();

int set_toolkit_callback_idle(void (*ptr_callback_function)());
int set_toolkit_callback_display(void (*ptr_callback_function)());
int set_toolkit_callback_reshape(void (*ptr_callback_function)(int width, int height));
int set_toolkit_callback_keyboard(void (*ptr_callback_function)(KEYBOARD_KEY key));
#endif
