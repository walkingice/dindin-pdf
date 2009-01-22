/*
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

#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glext.h>

#include "slide_view.h"
#include "debug.h"
#include "list.h"
#include "slide.h"

#include "slip_animation.h"
#include "cube_animation.h"
#include "cover_animation.h"

static int slide_index;     // the index of the slide we are showing
static int slide_next = -1; // the index of next slide what is going to be showed

struct list_head* slides_head; // the head of list of struct Slide
int max_slides;                // total number of slides

enum _SLIDE_STATE {
	NORMAL = 0,
	ANIMATION,
};

typedef enum _SLIDE_STATE SLIDE_STATE;

SLIDE_STATE slide_state = NORMAL; // detect should we play animation or not

/* Function pointers, what are used in animation */
static int  (*ptr_have_next_frame)();
static void (*ptr_clear_animation)();
static void (*ptr_animation)(Slide*, Slide*);

/* Interface for key Right, Left, Up, Down, Pageup, Pagedown */
static int  (*ptr_right_have_next_frame)();
static void (*ptr_right_clear_animation)();
static void (*ptr_right_animation)(Slide*, Slide*);
static int  (*ptr_left_have_next_frame)();
static void (*ptr_left_clear_animation)();
static void (*ptr_left_animation)(Slide*, Slide*);
static int  (*ptr_up_have_next_frame)();
static void (*ptr_up_clear_animation)();
static void (*ptr_up_animation)(Slide*, Slide*);
static int  (*ptr_down_have_next_frame)();
static void (*ptr_down_clear_animation)();
static void (*ptr_down_animation)(Slide*, Slide*);
static int  (*ptr_pageup_have_next_frame)();
static void (*ptr_pageup_clear_animation)();
static void (*ptr_pageup_animation)(Slide*, Slide*);
static int  (*ptr_pagedown_have_next_frame)();
static void (*ptr_pagedown_clear_animation)();
static void (*ptr_pagedown_animation)(Slide*, Slide*);

static void (*display_callback)();

static void draw_slide(Slide *slide);
static inline Slide* get_slide_from_list(int index);

/**
 * @brief Pass in the list of struct Slides, initialize inner variables of slide_view
 * @param head The head of the list of struct Slides
 * @param display A callback function that asking redraw screen
 */
void init_slide_view(struct list_head* head, void (*display)()) {
	slides_head = head;
	display_callback = display;
	
	struct list_head* counter = head;
	int i = 0;
	do {
		counter = counter->next;
		i++;
	}while(counter->next != head);
	max_slides = i;

	/* Bind the interface with implementation */
	ptr_right_have_next_frame    = have_next_frame_slip_right;
	ptr_right_clear_animation    = clear_slip_animation;
	ptr_right_animation          = exec_slip_animation;

	ptr_left_have_next_frame     = have_next_frame_slip_left;
	ptr_left_clear_animation     = clear_slip_animation;
	ptr_left_animation           = exec_slip_animation;

	ptr_up_have_next_frame       = have_next_frame_cover_up;
	ptr_up_clear_animation       = clear_cover_animation;
	ptr_up_animation             = exec_cover_animation_up;

	ptr_down_have_next_frame     = have_next_frame_cover_down;
	ptr_down_clear_animation     = clear_cover_animation;
	ptr_down_animation           = exec_cover_animation_down;

	ptr_pageup_have_next_frame   = have_next_frame_cube_left;
	ptr_pageup_clear_animation   = clear_cube_animation;
	ptr_pageup_animation         = exec_cube_animation_left;

	ptr_pagedown_have_next_frame = have_next_frame_cube_right;
	ptr_pagedown_clear_animation = clear_cube_animation;
	ptr_pagedown_animation       = exec_cube_animation_right;
}

/**
 * @brief Callback for main program. Call this function while drawing Slide.
 */
void show_slide() {
	glLoadIdentity();
	
	if(slide_state == NORMAL) {
		Slide *now_slide = get_slide_from_list(slide_index);
		draw_slide(now_slide);
	}else if(slide_state == ANIMATION ){

		Slide *now_slide  = get_slide_from_list(slide_index);
		Slide *next_slide = get_slide_from_list(slide_next);

		if(ptr_animation != NULL)
			ptr_animation(now_slide, next_slide);
	}
}

/**
 * @brief set a new slide we are drawing
 */
void set_slide(int new_slide) {
	if(new_slide >= 0 && new_slide < max_slides) {
		debug("change new slide !!!");

		slide_next = new_slide;

	        if(slide_state == ANIMATION) {
			ptr_clear_animation();
			while(ptr_have_next_frame() == 1) {
				debug("Have next frame\n");
				display_callback();
			}
		}
		slide_state = NORMAL;
		slide_index = new_slide;
		display_callback();
	}
}

/**
 * @brief Get the index of the slide we are showing
 */
int get_slide_index() {
	return slide_index;
}

/**
 * @brief Detect change slide by keyboard or not
 * The main program doesn't know which slide is showing.
 * Pass the keycode to slide_view by this function and let slide_view detect change the slide or not.
 * @param key keycode of the key pressed by user
 */
void change_slide_by_keyboard(KEYBOARD_KEY key) {
	int now_slide = get_slide_index();
	slide_state = ANIMATION;
	if(key == KEY_RIGHT) {
		ptr_animation = ptr_right_animation;
		ptr_clear_animation = ptr_right_clear_animation;
		ptr_have_next_frame = ptr_right_have_next_frame;
		set_slide(now_slide + 1);
	}else if(key == KEY_LEFT) {
		ptr_animation = ptr_left_animation;
		ptr_clear_animation = ptr_left_clear_animation;
		ptr_have_next_frame = ptr_left_have_next_frame;
		set_slide(now_slide - 1);
	}else if(key == KEY_PAGEDOWN) {
		ptr_animation = ptr_pagedown_animation;
		ptr_clear_animation = ptr_pagedown_clear_animation;
		ptr_have_next_frame = ptr_pagedown_have_next_frame;
		set_slide(now_slide + 1);
	}else if(key == KEY_PAGEUP) {
		ptr_animation = ptr_pageup_animation;
		ptr_clear_animation = ptr_pageup_clear_animation;
		ptr_have_next_frame = ptr_pageup_have_next_frame;
		set_slide(now_slide - 1);
	}else if(key == KEY_DOWN) {
		ptr_animation = ptr_down_animation;
		ptr_clear_animation = ptr_down_clear_animation;
		ptr_have_next_frame = ptr_down_have_next_frame;
		set_slide(now_slide + 1);
	}else if(key == KEY_UP) {
		ptr_animation = ptr_up_animation;
		ptr_clear_animation = ptr_up_clear_animation;
		ptr_have_next_frame = ptr_up_have_next_frame;
		set_slide(now_slide - 1);
	}

	slide_state = NORMAL;
}

/**
 * @brief Draw a slide on the screen
 */
static void draw_slide(Slide *slide) {
	/* Fixme: It supposed to be drawed with fullscreen. But it doestn't yet */
	GLuint texture = slide->page_texture;
	double width  = slide->width;
	double height = slide->height;
	debug("draw slide, texture is %d\n", texture);
	glEnable(GL_TEXTURE_RECTANGLE_ARB);
	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTranslatef(0,0,-10);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,0.0);
	glVertex3i(-5, 5, 0);
	glTexCoord2f(width, 0.0);
	glVertex3i(5, 5, 0);
	glTexCoord2f(width, height);
	glVertex3i(5, -5, 0);
	glTexCoord2f(0.0, height);
	glVertex3i(-5, -5, 0);
	glEnd();

	glDisable(GL_TEXTURE_RECTANGLE_ARB);

}

static inline Slide* get_slide_from_list(int index) {
	int i = 0;
	struct list_head* counter = slides_head;

	if(index > max_slides) {
		debug("Out of bounds of list_head: %d/%d\n", index, max_slides);
	}
	for(i=0;i<=index;i++) {
		counter = counter->next;
	}
	return list_entry(counter, Slide, node);
}
