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

#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#include "global.h"
#include "slip_animation.h"

static double dindin_time_get(void);

static Vertex position = {0, 0, -10};
static double time_swap, time_start;
static int right_or_left;
void clear_slip_animation() {
	position.x = 0;
	position.y = 0;
	position.z = -10;
	time_swap  = 0.4;
	time_start = dindin_time_get();
}

int have_next_frame_slip_right() {

	double time_elapse = dindin_time_get() - time_start;
	if(time_elapse >= time_swap)
		return 0;

	right_or_left = 1;
	float percent = (float)(time_elapse/time_swap);

	if(percent < 0.2) {
		position.x = 0;
		position.z = -10 - 5*percent;
	}else if(percent > 0.8) {
		position.x = -11;
		position.z = -11 + 5 * (percent-0.8);
	}else {
		position.x = -11 * ((percent-0.2)/0.6);
	}
	return 1;
}
int have_next_frame_slip_left() {

	float time_elapse = dindin_time_get() - time_start;
	if(time_elapse >= time_swap)
		return 0;

	right_or_left = -1;
	float percent = time_elapse/time_swap;

	if(percent < 0.2) {
		position.x = 0;
		position.z = -10 - 5*percent;
	}else if(percent > 0.8) {
		position.x = 11;
		position.z = -11 + 5 * (percent-0.8);
	}else {
		position.x = 11 * ((percent-0.2)/0.6);
	}
	return 1;
}

void exec_slip_animation (Slide *slide_now, Slide *slide_next) {

	GLuint texture_now = slide_now->page_texture;
	GLuint texture_next = slide_next->page_texture;

	double now_width   = slide_now->width;
	double now_height  = slide_now->height;
	double next_width  = slide_next->width;
	double next_height = slide_next->height;

	glEnable(GL_TEXTURE_RECTANGLE_ARB);

	glLoadIdentity();
	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture_now);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glTranslatef(position.x, position.y, position.z);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0,0.0);
	glVertex3i(-5, 5, 0); 
	glTexCoord2f(now_width, 0.0);
	glVertex3i(5, 5, 0); 
	glTexCoord2f(now_width, now_height);
	glVertex3i(5, -5, 0); 
	glTexCoord2f(0.0, now_height);
	glVertex3i(-5, -5, 0); 
	glEnd();


	glTranslatef(11* right_or_left, 0, 0); 

	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture_next);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,0.0);
	glVertex3i(-5, 5, 0); 
	glTexCoord2f(next_width, 0.0);
	glVertex3i(5, 5, 0);
	glTexCoord2f(next_width, next_height);
	glVertex3i(5, -5, 0);
	glTexCoord2f(0.0, next_height);
	glVertex3i(-5, -5, 0);
	glEnd();
	glDisable(GL_TEXTURE_RECTANGLE_ARB);
}

// Borrowed this part of code from ecore_time.c of Enlightenment project.
/* FIXME: clock_gettime() is an option... */

/**
 * Retrieves the current system time as a floating point value in seconds.
 * @return  The number of seconds since 12.00AM 1st January 1970.
 */
double dindin_time_get(void) {
	struct timeval timev;

	gettimeofday(&timev, NULL);
	return (double)timev.tv_sec + (((double)timev.tv_usec) / 1000000);
}

