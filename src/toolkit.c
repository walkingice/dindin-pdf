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

#include <GL/glut.h>

#include "global.h"
#include "toolkit.h"
#include "debug.h"

static KEYBOARD_KEY convert_keycode_from_glut(unsigned char key);


int set_toolkit_callback_idle(void (*ptr_callback_function)()) {
	glutIdleFunc(ptr_callback_function);
	return 0;
}

int set_toolkit_callback_display(void (*ptr_callback_function)()) {
	glutDisplayFunc(ptr_callback_function);
	return 0;
}

int set_toolkit_callback_reshape(void (*ptr_callback_function)(int width, int height)) {
	glutReshapeFunc(ptr_callback_function);
	return 0;
}
int set_toolkit_callback_keyboard(void (*ptr_callback_function)(
				unsigned char key, int x, int y)) {
	glutKeyboardFunc(ptr_callback_function);
	return 0;
}
int set_toolkit_callback_special(void (*ptr_callback_function)(
				int key, int x, int y)) {
	glutSpecialFunc(ptr_callback_function);
	return 0;
}
int set_toolkit_callback_mouse(void (*ptr_callback_function)(
				int button, int state, int x UNUSED, int y UNUSED)) {
	glutMouseFunc(ptr_callback_function);
	return 0;
}

int  toolkit_init(int *argc, char **argv, char *window_name
		, int window_width, int window_height
		, int position_x, int position_y) {

	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(position_x, position_y);
	glutCreateWindow(window_name);
	return 0;
}

void toolkit_mainloop() {
	glutMainLoop();
}

void toolkit_redisplay() {
	glutPostRedisplay();
}

int toolkit_say_byebye() {
	glutWireCube(2);
	return 0;
}

/**
 * @brief An interface. Return KEYBOARD_KEY while user press a key
 * @param key The key code what user press
 */
KEYBOARD_KEY toolkit_convert_keycode(unsigned char key) {
	return convert_keycode_from_glut(key);
}

/**
 * @brief An implementation of interface conver_keycode
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

