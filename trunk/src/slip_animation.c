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

#include "global.h"
#include "slip_animation.h"

static Vertex position = {0, 0, -10};
static int frame;
static int right_or_left;
void clear_slip_animation() {
	position.x = 0;
	position.y = 0;
	position.z = -10;
	frame = 42;
}

int have_next_frame_slip_right() {
	right_or_left = 1;
	if(frame > 32)
		position.z -= 0.1;
	if(frame < 10)
		position.z += 0.1;
	if(frame <= 32 && frame >= 10) {
		position.x -= 10.5/22;
	}
	frame--;
	if(frame <= 0)
		return 0;
	else
		return 1;
}
int have_next_frame_slip_left() {
	right_or_left = -1;
	if(frame > 32)
		position.z -= 0.1;
	if(frame < 10)
		position.z += 0.1;
	if(frame <= 32 && frame >= 10) {
		position.x += 10.5/22;
	}
	frame--;
	if(frame <= 0)
		return 0;
	else
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

