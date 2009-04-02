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
 * \file toolkit_gtk.c
 * \author Julian Chu (WalkingIce)
 * \date 2009-4-1 (Come on, this file is not a joke :P)
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "debug.h"

#include "global.h"
#include "toolkit_gtk.h"

static GtkWindow* main_window;

/* Function pointers which refer to dindin main body *
 * They do not related to GUI toolkit                */
static void (*dindin_display)();
static void (*dindin_idle)();
static void (*dindin_reshape)(GLsizei width, GLsizei height);
static void (*dindin_keyboard)(KEYBOARD_KEY key);

/* Callback functions for GTK */
static void glut_display();
static void glut_idle();
static void glut_reshape(int width, int height);
static void gtk_keyboard(GtkWidget* widget, GdkEventKey* event, gpointer data);

static KEYBOARD_KEY convert_keycode_from_gdk(guint key);


/* **Implement Interface** */

int set_gtk_callback_display(void (*ptr_callback_function)()) {
	dindin_display = ptr_callback_function;
	//glutDisplayFunc(glut_display);
	return 0;
}

int set_gtk_callback_idle(void (*ptr_callback_function)()) {
	dindin_idle = ptr_callback_function;
	//glutIdleFunc(glut_idle);
	return 0;
}

int set_gtk_callback_reshape(void (*ptr_callback_function)(GLsizei width, GLsizei height)) {
	dindin_reshape = ptr_callback_function;
	//glutReshapeFunc(glut_reshape);
	return 0;
}
int set_gtk_callback_keyboard(void (*ptr_callback_function)(KEYBOARD_KEY key)) {
	dindin_keyboard = ptr_callback_function;
	g_signal_connect(window, "key_press_event", G_CALLBACK(gtk_keyboard), NULL);
	return 0;
}

int  gtk_init(toolkit_init_struct* init_info) {
	gtk_init(info->cmd_argc, init_info->cmd_argv);
	main_window = (GtkWindow*) gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(window, init_info->window_name);
	gtk_window_set_default_size(window, init_info->window_width, init_info->window_height);
	return 0;
}

void gtk_mainloop() {
	gtk_widget_show_all((GtkWidget*) main_window);
	gtk_main();
}

void gtk_redisplay() {
	// not implemented yet
}

int gtk_say_byebye() {
	// not implemented yet
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

static gint gtk_keyboard(GtkWidget* widget, GdkEventKey* event, gpointer data) {
	KEYBOARD_KEY dindin_key = convert_keycode_from_gtk(event->keyval);
	if(dindin_keyboard != NULL) {
		dindin_keyboard(dindin_key);
	}
}

/**
 * @brief An implementation for converting GDK keycode to Dindin KEYBOARD_KEY
 * @param key The key code what user press
 */
static KEYBOARD_KEY convert_keycode_from_gdk(guint key) {
	if(key == GDK_Right) {
		return KEY_RIGHT;
	}else if(key == GDK_Left) {
		return KEY_LEFT;
	}else if(key == GDK_Up) {
		return KEY_UP;
	}else if(key == GDK_Down) {
		return KEY_DOWN;
	}else if(key == GDK_Page_Up) {
		return KEY_PAGEUP;
	}else if(key == GDK_Page_Down) {
		return KEY_PAGEDOWN;
	}else if(key == GDK_Return) {
		return KEY_ENTER;
	}else if(key == GDK_Escape) {
		return KEY_ESC;
	}else if(key == GDK_Y || key == GDK_y) {
		return KEY_Y;
	}else {
		debug("unknow key  %c = %x\n",key,key);
		return KEY_UNKNOWN;
	}
}

