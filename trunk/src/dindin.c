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
 * \file dindin.c
 * \author Julian Chu (WalkingIce)
 * \date 2008-12-27
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <glib/poppler.h>

#include "debug.h"

#include "global.h"
#include "state.h"

#include "list.h"
#include "slide.h"
#include "thumb_view.h"
#include "slide_view.h"

#define MAX_FILE_PATH 1024

struct list_head* slides_head; // Poppler read in PDF into struct Slide, then put them here
static PopplerDocument* document = NULL;
static int max_slides_number = 0;

static void         print_usage();
static void         change_slide_or_not(KEYBOARD_KEY key);
static void         move_cursor_or_not(KEYBOARD_KEY key);
static int          keep_read_slide(PopplerDocument* doc, struct list_head* slides_head, int max_slides);
static KEYBOARD_KEY convert_keycode(unsigned char key);
static KEYBOARD_KEY convert_keycode_from_glut(unsigned char key);

void display();

/**
 * @brief Initialize Dindin with filename and number of reading pages
 * @param filename The PDF file path
 * @param page_number_by_user User use -p option to specify the number of reading pages
 */
void init(char* filename, int page_number_by_user) {

	gchar *filename_uri  = NULL;

	debug("GL version:%s\n",(char*)glGetString(GL_VERSION));

	glClearColor(1.0, 1.0, 0.5, 1.0); // Clear background
	glShadeModel(GL_FLAT);
	glEnable(GL_TEXTURE_RECTANGLE_ARB);
	glEnable(GL_DEPTH_TEST);

	/* Use Poppler to read in PDF file */
	g_type_init();

	debug("Read in file %s\n",filename);
	filename_uri = get_file_uri (filename);
	document = poppler_document_new_from_file(filename_uri, NULL, NULL);

	if(page_number_by_user == 0)
		max_slides_number = poppler_document_get_n_pages(document);
	else
		max_slides_number = page_number_by_user;

	/* Initialize Slides structures  */
	/* Fixme: someone implement a function deinit_list_head ? */
	slides_head = (struct list_head*) malloc(sizeof(struct list_head));
	INIT_LIST_HEAD(slides_head);

	keep_read_slide(document, slides_head, max_slides_number);
	set_state(SHOW_THUMBNAIL);
	set_cursor(0);
}

/**
 * @brief callback function for GLUT
 */
void display() {
	STATE state = get_state();

	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(state == SHOW_THUMBNAIL) {
		debug("state is Show Thumbnail\n");
		show_thumbnail(slides_head);
	}else if(state == SHOW_SLIDE) {
		show_slide();
	}else if(state == CHECK_EXIT_OR_NOT) {
		glTranslatef(0,0,-12);
		glRotatef(45,1,1,1);
		glutWireCube(2);
	}else {
		debug("Nothing happened\n");
	}

	glFlush();
	glutSwapBuffers();
}

/**
 * @brief callback function for GLUT
 */
void resize(GLsizei width, GLsizei height) {
	debug("function resize was called\n");

	glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(PROJECTION_LEFT, PROJECTION_RIGHT
			,PROJECTION_BOTTOM, PROJECTION_TOP
			,PROJECTION_NEAR, PROJECTION_FAR);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/**
 * @brief callback function for GLUT
 */
void keyboard(unsigned char key, int x UNUSED, int y UNUSED) {
	/* Get a keycode while user press any key.
	   Pass it into State machine */
	KEYBOARD_KEY new_key = convert_keycode(key);
	STATE next = get_state_by_key(new_key);
	debug("return state is %d\n",next);

	if(next == SHOW_SLIDE) {
		debug("show slide \n");
		set_state(next);
		change_slide_or_not(new_key);
	}else if(next == SHOW_THUMBNAIL) {
		debug("show thumbnail\n");
		set_state(next);
		move_cursor_or_not(new_key);
	}else if(next == CHECK_EXIT_OR_NOT) {
		debug("Exit? Press Y to exit\n");
		set_state(next);
	}else if (next == EXIT) {
		debug("exit\n");
		exit(0);
	}else {
		debug("nothing happened\n");
	}

	glutPostRedisplay();
}
/**
 * @brief callback function for GLUT
 */
void keyboard_s(int key, int x, int y) {
	keyboard((unsigned char)key, x, y);
}

/**
 *  @brief A callback function for GLUT. It will keep read in unread slides while idle and terminate while finish.
 */
static void idle_read_slides() {
	int keep = keep_read_slide(document, slides_head, max_slides_number);
	if(keep == 0) {
		/* We already read whole slides, terminate Idle function */
		glutIdleFunc(NULL);
	} else {
		debug("Dindin alread read in %dth slide\n", keep);
	}
}

/**
 * @brief callback function for GLUT, non-usable yet
 */
void mouse(int button, int state, int x UNUSED, int y UNUSED) {
	switch(button) {
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN) {
				debug("mouse down\n");
				glutIdleFunc(display);
			}else if (state == GLUT_UP) {
				debug("mouse up\n");
			}
			break;
		default:
			break;
	}
}

/**
 * @brief Pass the keycode to thumb_view for deciding move cursor or not.
 * @param key The key code what user press
 */
static void move_cursor_or_not(KEYBOARD_KEY key) {
	debug("function keyboard_s was called\n");
	move_cursor_by_keyboard(key);
	set_slide(get_cursor());
	glutPostRedisplay();
}

/**
 * @brief Pass the keycode to slide_view for deciding change slide or not
 * @param key The key code what user press
 */
static void change_slide_or_not(KEYBOARD_KEY key) {
	//int now_cursor = get_cursor();
	change_slide_by_keyboard(key);
	set_cursor(get_slide_index());
	glutPostRedisplay();
}

/**
 * @brief Read in one more slide into internal struct.
 * @param doc Read slides from here
 * @param slides_head Put the read-in slide into here
 * @param max_slides Limit the maximum numbers of slides we want to read in
 * @return Shall we keep read more slides (return Number of pages already read) or not (return 0)
 */
static int keep_read_slide(PopplerDocument* doc, struct list_head* slides_head, int max_slides) {
	int now_page = 0; // How many pages we already read in
	struct list_head* counter = slides_head;
	Slide *slide;
	PopplerPage *page;

	/* Calculate which page of _doc_ we already read in */
	while(counter->next != slides_head) {
		counter = counter->next;
		now_page++;
	}

	if(now_page >= max_slides) {
		return 0;
	}

	if(now_page >= poppler_document_get_n_pages(doc)) {
		return 0;
	}

	/* It is a bit tricky. If we already read N pages,so now_page == N
	 * We are going to read N+1 page ,but we just call poppler_document_get_page(doc, N)
	 * because of that the first page of _doc_ is 0 but not 1 */
	slide = (Slide *) calloc(1, sizeof(Slide));
	page  = poppler_document_get_page(doc, now_page);
	init_slide(page, slide, now_page);
	INIT_LIST_HEAD(&slide->node);
	list_add_tail(&slide->node, slides_head);

	init_slide_view(slides_head, display);
	init_thumb_view(slides_head, display);

	glutPostRedisplay();
	return now_page;
}

/**
 * @brief An interface. Return KEYBOARD_KEY while user press a key
 * @param key The key code what user press
 */
static KEYBOARD_KEY convert_keycode(unsigned char key) {
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

static void print_usage() {
	printf("\n dindin -p <num> <filename>\n");
	printf(" dindin -h\n");
	printf(" -p <num>   : How many pages you only want to read in\n");
	printf(" -h         : Print out this help\n");
	printf(" <filename> : The PDF file\n");
	printf("\n");
	exit(0);
}

int main(int argc, char **argv)
{
	// parsing args, borrowed from GNU :-P
	// http://www.gnu.org/software/libtool/manual/libc/Getopt.html
	int h_flag = 0;
	int p_flag = 0;
	char *page_opt_value = NULL;
	int page_number_by_user = 0;
	char *filename = NULL;

	int index;
	int c;
	opterr = 0;

	while ((c = getopt (argc, argv, "hp:")) != -1) {
		switch (c)
		{
			case 'h':
				h_flag = 1;
				break;
			case 'p':
				page_opt_value = optarg;
				p_flag = 1;
				break;
			case '?':
				if (optopt == 'p')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr, "Unknown option character `\\x%x'.\n",optopt);
				return 1;
			default:
				abort ();
		}
	}

	/* User specify -h or -p <num> ?? */
	if(h_flag) {
		print_usage();
	}
	if(p_flag) {
		page_number_by_user = atoi(page_opt_value);
		if(page_number_by_user <= 0)
			print_usage();
	}

	/* At least, User should provide a PDF file name */
	filename = (char*) malloc(sizeof(char) * MAX_FILE_PATH);

	for (index = optind; index < argc; index++) {
		strncpy(filename, argv[index], MAX_FILE_PATH);
	}

	if(strlen(filename) == 0) {
		print_usage();
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT );
	glutInitWindowPosition(200,150);
	glutCreateWindow("Din Din");
	/* Set callback function */
	glutDisplayFunc(display);
	glutReshapeFunc (resize);
	glutKeyboardFunc (keyboard);
	glutSpecialFunc (keyboard_s);
	glutIdleFunc (idle_read_slides);
	glutMouseFunc(mouse);

	init(filename, page_number_by_user);
	glutMainLoop();

	free(filename);
	return(0);
}

