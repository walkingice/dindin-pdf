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
 * \file toolkit.c
 * \author Julian Chu (WalkingIce)
 * \date 2009-2-26
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdlib.h>
#include <GL/glut.h>

#include "global.h"
#include "toolkit.h"
#include "toolkit_glut.h"
#include "debug.h"

/**
 * @brief Set an idle function to toolkit
 * @param ptr_callback_function The idle callback function
 * @return Return 0 means it success
 */
int set_toolkit_callback_idle(void (*ptr_callback_function)()) {
	set_glut_callback_idle(ptr_callback_function);
	return 0;
}

/**
 * @brief Set a display function to toolkit that draw OpenGL screen
 * @param ptr_callback_function The display callback function
 * @return Return 0 means it success
 */
int set_toolkit_callback_display(void (*ptr_callback_function)()) {
	set_glut_callback_display(ptr_callback_function);
	return 0;
}

/**
 * @brief Set an reshape function to toolkit that be called whenever the window size changes
 * @param ptr_callback_function The reshape callback function
 * @return Return 0 means it success
 */
int set_toolkit_callback_reshape(void (*ptr_callback_function)(int width, int height)) {
	set_glut_callback_reshape(ptr_callback_function);
	return 0;
}

/**
 * @brief Set an keyboard function to toolkit that be called whenever user press key
 * @param ptr_callback_function The keyboard callback function
 * @return Return 0 means it success
 */
int set_toolkit_callback_keyboard(void (*ptr_callback_function)(KEYBOARD_KEY)) {
	set_glut_callback_keyboard(ptr_callback_function);
	return 0;
}

/**
 * @brief Toolkit initialize function
 * @param argc Numbers of arguments which come from command line
 * @param argv Command line arguments
 * @param window_name The name of the window
 * @param window_width The width of the window
 * @param window_height The height of the window
 * @param position_x Position of X coordinate of the window
 * @param position_y Position of Y coordinate of the window
 * @return Return 0 means it success
 */
int  toolkit_init(int *argc, char **argv, char *window_name
		, int window_width, int window_height
		, int position_x, int position_y) {

	toolkit_init_struct *init_info;
	init_info = malloc(sizeof(toolkit_init_struct));
	init_info->cmd_argc      = argc;
	init_info->cmd_argv      = argv;
	init_info->window_name   = window_name;
	init_info->window_width  = window_width;
	init_info->window_height = window_height;
	init_info->pos_x         = position_x;
	init_info->pos_y         = position_y;

	glut_init(init_info);

	free(init_info);
	return 0;
}

/**
 * @brief Main loop function of toolkit
 */
void toolkit_mainloop() {
	glut_mainloop();
}

/**
 * @brief Redisplay function while asking toolkit to redraw screen
 */
void toolkit_redisplay() {
	glut_redisplay();
}

/**
 * @brief Show a leaving message to ask user to leave or not
 */
int toolkit_say_byebye() {
	glut_say_byebye();
	return 0;
}

