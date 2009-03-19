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
 * \file toolkit_glut.c
 * \author Julian Chu (WalkingIce)
 * \date 2009-3-19
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "debug.h"

#include <GL/glut.h>

#include "global.h"
#include "toolkit_glut.h"

/* Function pointers which refer to dindin main body *
 * They do not related to GUI toolkit                */
static void (*dindin_display)();
static void (*dindin_idle)();
static void (*dindin_reshape)(GLsizei width, GLsizei height);
static void (*dindin_keyboard)(KEYBOARD_KEY key);

/* Callback functions for GLUT */
static void glut_display();
static void glut_idle();
static void glut_reshape(int width, int height);
static void glut_keyboard(unsigned char key, int x UNUSED, int y UNUSED);
static void glut_keyboard_s(int key, int x, int y);

static KEYBOARD_KEY convert_keycode_from_glut(unsigned char key);


/* **Implement Interface** */

int set_glut_callback_display(void (*ptr_callback_function)()) {
	dindin_display = ptr_callback_function;
	glutDisplayFunc(glut_display);
	return 0;
}

int set_glut_callback_idle(void (*ptr_callback_function)()) {
	dindin_idle = ptr_callback_function;
	glutIdleFunc(glut_idle);
	return 0;
}

int set_glut_callback_reshape(void (*ptr_callback_function)(GLsizei width, GLsizei height)) {
	dindin_reshape = ptr_callback_function;
	glutReshapeFunc(glut_reshape);
	return 0;
}
int set_glut_callback_keyboard(void (*ptr_callback_function)(KEYBOARD_KEY key)) {
	dindin_keyboard = ptr_callback_function;
	glutKeyboardFunc(glut_keyboard);
	glutSpecialFunc(glut_keyboard_s);
	return 0;
}

int  glut_init(toolkit_init_struct* init_info) {
	glutInit(init_info->cmd_argc, init_info->cmd_argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(init_info->window_width, init_info->window_height);
	glutInitWindowPosition(init_info->pos_x, init_info->pos_y);
	glutCreateWindow(init_info->window_name);
	return 0;
}

void glut_mainloop() {
	glutMainLoop();
}

void glut_redisplay() {
	glut_display();
}

int glut_say_byebye() {
	glutWireCube(2);
	return 0;
}

/* **Implement callback function for GLUT** */

static void glut_display() {
	if(dindin_display != NULL) {
		dindin_display();
		glutSwapBuffers();
	}
}

static void glut_idle() {
	if(dindin_idle != NULL) {
		dindin_idle();
	}
}

static void glut_reshape(int width, int height) {
	if(dindin_reshape != NULL) {
		dindin_reshape((GLsizei)width, (GLsizei)height);
	}
}

static void glut_keyboard(unsigned char key, int x UNUSED, int y UNUSED) {
	KEYBOARD_KEY dindin_key = convert_keycode_from_glut(key);
	if(dindin_keyboard != NULL) {
		dindin_keyboard(dindin_key);
	}
}

static void glut_keyboard_s(int key, int x, int y) {
	glut_keyboard((unsigned char)key, x, y);
}

/**
 * @brief An implementation for converting GLUT keycode to Dindin KEYBOARD_KEY
 * @param key The key code what user press
 */
static KEYBOARD_KEY convert_keycode_from_glut(unsigned char key) {
	if(key == GLUT_KEY_RIGHT) {
		return KEY_RIGHT;
	}else if(key == GLUT_KEY_LEFT) {
		return KEY_LEFT;
	}else if(key == GLUT_KEY_UP) {
		return KEY_UP;
	}else if(key == GLUT_KEY_DOWN) {
		return KEY_DOWN;
	}else if(key == GLUT_KEY_PAGE_UP) {
		return KEY_PAGEUP;
	}else if(key == GLUT_KEY_PAGE_DOWN) {
		return KEY_PAGEDOWN;
	}else if(key == 0x0d) {
		return KEY_ENTER;
	}else if(key == 0x1b) {
		return KEY_ESC;
	}else if(key == 'Y' || key == 'y') {
		return KEY_Y;
	}else {
		debug("unknow key  %c = %x\n",key,key);
		return KEY_UNKNOWN;
	}
}

