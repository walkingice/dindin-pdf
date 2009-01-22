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

#include <time.h>
#include <sys/times.h>

#include "debug.h"
#include "thumb_view.h"
#include "slide.h"

struct list_head* slides_head; // refer to struct Slides what are created from PDF
int max_slides; // How many pages of these slides
int cursor;     // Which slide was be refered by cursor

Quard cursor_quard; // the location of cursor which on the screen

static void (*display_callback)();

static void draw_thumb(Slide *slide, Vertex a, Vertex b, Vertex c, Vertex d); 
static void draw_cursor(Vertex a, Vertex b, Vertex c, Vertex d); 
static void get_quard(Quard *quard, int index);
static void move_view(int now_cursor);
static void cursor_animation(int new_cursor);
inline static Slide* get_slide_from_list(int index);

/**
 * @brief Pass in the list of struct Slides, initialize inner variables of thumb_view
 * @param head The head of the list of struct Slides
 * @param display A callback function that asking redraw screen
 */
void init_thumb_view(struct list_head* head, void (*display)()) {
	slides_head = head;
	display_callback = display;
	struct list_head* counter = head;
	int i = 0;
	do {
		counter = counter->next;
		i++;
	}while(counter->next != head);
	max_slides = i;
}

/**
 * @brief Callback for main program. Call this function while drawing Thumbnails.
 */
void show_thumbnail() {

	assert(&cursor_quard != NULL);
	glLoadIdentity();

	move_view(cursor); //move view to current cursor

	struct list_head *counter,*temp;
	list_for_each_safe(counter, temp, slides_head) {
		Slide *slide = list_entry(counter, Slide, node);
		Quard q;
		get_quard(&q, slide->index);
		draw_thumb(slide, q.lt, q.rt, q.rb, q.lb);
	}

	draw_cursor(cursor_quard.lt, cursor_quard.rt,
			cursor_quard.rb, cursor_quard.lb);
}

/**
 * @brief Change the cursor to refer specified Slide.
 * @param new_cursor The index of the slide what will be refer to.
 */
void set_cursor(int new_cursor) {
	if(new_cursor < 0 || new_cursor >= max_slides) {
		debug("new cursor out of range, 0<= new < %d\n", max_slides);
		return;
	}
	cursor = new_cursor;
	get_quard(&cursor_quard, new_cursor);
}

/**
 * @brief Get the index of the slide
 * @return The index of the slide what was be refered by cursor
 */
int get_cursor() {
	return cursor;
}

/**
 * @brief Detect move cursor by keyboard or not
 * The main program don't know the layout of those thumbnails.
 * Pass the keycode to thumb_view by this function and let thumb_view to decide move the cursor or not.
 * @param key Keycode of the key pressed by user
 */
void move_cursor_by_keyboard(KEYBOARD_KEY key) {
	int cursor = get_cursor();
	if(key == KEY_RIGHT) {
		if(cursor%THUMB_ROW_NUM < THUMB_ROW_NUM -1  
				&& cursor < max_slides - 1) {
			cursor++;
		}
	}else if(key == KEY_LEFT) {
		if(cursor%THUMB_ROW_NUM > 0) {
			cursor--;
		}
	}else if(key == KEY_UP) {
		if(cursor - THUMB_ROW_NUM >= 0 ) { 
			cursor -= THUMB_ROW_NUM;
		}
	}else if(key == KEY_DOWN) {
		if(cursor + THUMB_ROW_NUM < max_slides) {
			cursor += THUMB_ROW_NUM;
		}
	}else if(key == KEY_PAGEUP) {
	}else if(key == KEY_PAGEDOWN) {
	}

#ifdef CURSOR_ANIMATION
	cursor_animation(cursor);
#else
	set_cursor(cursor);
#endif
}

/**
 * @brief Drawing a thumbnail image of a slide.
 * @param slide The slide provide the thumbnail
 * @param a The left-bottom  corner coordinate of the thumbnail.
 * @param b The right-bottom corner coordinate of the thumbnail.
 * @param c The right-top    corner coordinate of the thumbnail.
 * @param d The left-top     corner coordinate of the thumbnail.
 */
static void draw_thumb(Slide *slide, Vertex a, Vertex b,Vertex c, Vertex d) {
	/* Give a Slide and quard. Draw thumbnail of the slide with the quard*/
	GLuint texture = slide->texture;
	double width  = slide->thumb_width;
	double height = slide->thumb_height;
	glEnable(GL_TEXTURE_RECTANGLE_ARB);
	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBegin(GL_QUADS);
 	 glTexCoord2f(0.0,0.0);
	 glVertex3i(a.x, a.y, a.z);
	 glTexCoord2f(width,0.0);
	 glVertex3i(b.x, b.y, b.z);
	 glTexCoord2f(width,height);
	 glVertex3i(c.x, c.y, c.z);
	 glTexCoord2f(0.0,height);
	 glVertex3i(d.x, d.y, d.z);
	glEnd();

	glDisable(GL_TEXTURE_RECTANGLE_ARB);
}

/**
 * @brief Drawing a quard for cursor
 * @param a The left-top     corner coordinate of the thumbnail.
 * @param a The right-top    corner coordinate of the thumbnail.
 * @param a The right-bottom corner coordinate of the thumbnail.
 * @param a The left-bottom  corner coordinate of the thumbnail.
 */
static void draw_cursor(Vertex a, Vertex b, Vertex c, Vertex d) {
	/* Give a quard and draw cursor*/
	glPushMatrix();
	glLoadIdentity();
	move_view(cursor);
	glColor3f(1.0f, 0.0f, 0.0f);
	glLineWidth(5.2f);
	float gap = 0.2;
	glBegin(GL_LINE_STRIP);
	 glVertex3f(a.x - gap, a.y + gap, a.z);
	 glVertex3f(b.x + gap, b.y + gap, b.z);
	 glVertex3f(c.x + gap, c.y - gap, c.z);
	 glVertex3f(d.x - gap, d.y - gap, d.z);
	 glVertex3f(a.x - gap, a.y + gap, a.z);
	glEnd();
	glPopMatrix();
}

static void move_view(int now_cursor) {
	/* Calculate the index of the left-top thumbnail in the screen */
	int num_per_page = ROW_PER_PAGE * THUMB_ROW_NUM;
	int offset = now_cursor % num_per_page;
	int left_top = now_cursor - offset;

	/* Get the coordinate of the left-top point of the thumbnail */
	Quard q;
	get_quard(&q, left_top);
	glTranslatef(-4.5, 0-q.lt.y +4.5 ,-10);
}

/**
 * @brief Get the location of a thumbnail what was specified by index
 * Calculate the coordinate of four corner of the thumbnail what was specified by index.
 * @param quard Contain the location of a thumbnail. It should be initialized first.
 * @param index The index of a thumbnail.
 */
static void get_quard(Quard *quard, int index) {
	int x = index % THUMB_ROW_NUM;
	int y = index / THUMB_ROW_NUM;
	SET_THUMB_LOCATION(quard->lt, x*2, y*-2, 0);
	SET_THUMB_LOCATION(quard->rt, x*2+1, y*-2, 0);
	SET_THUMB_LOCATION(quard->rb, x*2+1, y*-2 -1, 0);
	SET_THUMB_LOCATION(quard->lb, x*2, y*-2 -1, 0);
}

/**
 * @brief Provide an animation while moving cursor
 * Pass in an index of a thumbnail what we want to move to.
 * @param new_cursor The index of next thumbnail.
 */
static void cursor_animation(int new_cursor) {
	Quard new_quard;
	get_quard(&new_quard, new_cursor);

	/* well...I know its stupid.....:P */
	int frame = 10;
	float x_gap = (float)(new_quard.lt.x - cursor_quard.lt.x)/frame;
	float y_gap = (float)(new_quard.lt.y - cursor_quard.lt.y)/frame;
	int i;

	for(i=0 ; i < frame; i++) {
		cursor_quard.lt.x += x_gap;
		cursor_quard.lt.y += y_gap;
		cursor_quard.rt.x += x_gap;
		cursor_quard.rt.y += y_gap;
		cursor_quard.rb.x += x_gap;
		cursor_quard.rb.y += y_gap;
		cursor_quard.lb.x += x_gap;
		cursor_quard.lb.y += y_gap;
		display_callback();
	}
		set_cursor(new_cursor);
		glutPostRedisplay();
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

