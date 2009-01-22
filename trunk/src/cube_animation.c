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

#include "global.h"
#include "slip_animation.h"

float angle;
int left_or_right;
void clear_cube_animation() {
	angle = 0;
}

int have_next_frame_cube_right() {
	left_or_right = 1;
	angle = angle + 1;
	if(angle > 90)
		return 0;
	else
		return 1;
}
int have_next_frame_cube_left() {
	left_or_right = -1;
	angle = angle + 1;
	if(angle > 90)
		return 0;
	else
		return 1;
}

void exec_cube_animation_right (Slide *slide_now, Slide *slide_next) {

	GLuint texture_now = slide_now->page_texture;
	GLuint texture_next = slide_next->page_texture;

	double now_width   = slide_now->width;
	double now_height  = slide_now->height;
	double next_width  = slide_next->width;
	double next_height = slide_next->height;

	glLoadIdentity();

	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(0, 0, -15);

	if(angle < 45) {
		glTranslatef(0,0,-1*(angle/5.0));
		glRotatef(angle,1,0,0);
	}else {
		glTranslatef(0, 0, -1*((90-angle)/5.0));
		glRotatef(90 - angle, 1, 0, 0);
	}

	glRotatef(left_or_right *angle, 0, -1, 0);
	glEnable(GL_TEXTURE_RECTANGLE_ARB);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	if(angle < 45) {

	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture_next);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,0.0);
	glVertex3i(5, 5, 5); 
	glTexCoord2f(next_width, 0.0);
	glVertex3i(5, 5, -5);
	glTexCoord2f(next_width, next_height);
	glVertex3i(5, -5, -5);
	glTexCoord2f(0.0, next_height);
	glVertex3i(5, -5, 5);
	glEnd();

	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture_now);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,0.0);
	glVertex3i(-5, 5, 5); 
	glTexCoord2f(now_width, 0.0);
	glVertex3i(5, 5, 5);
	glTexCoord2f(now_width, now_height);
	glVertex3i(5, -5, 5);
	glTexCoord2f(0.0, now_height);
	glVertex3i(-5, -5, 5);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3i(0,1,0);
	glVertex3i(-5, 5,5);
	glVertex3i(5, 5,5);
	glVertex3i(5, 5,-5);
	glVertex3i(-5, 5,-5);
	glEnd();

	}else {
	glBegin(GL_POLYGON);
	glNormal3i(0,1,0);
	glVertex3i(-5, 5,5);
	glVertex3i(5, 5,5);
	glVertex3i(5, 5,-5);
	glVertex3i(-5, 5,-5);
	glEnd();

	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture_now);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,0.0);
	glVertex3i(-5, 5, 5); 
	glTexCoord2f(now_width, 0.0);
	glVertex3i(5, 5, 5);
	glTexCoord2f(now_width, now_height);
	glVertex3i(5, -5, 5);
	glTexCoord2f(0.0, now_height);
	glVertex3i(-5, -5, 5);
	glEnd();

	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture_next);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,0.0);
	glVertex3i(5, 5, 5); 
	glTexCoord2f(next_width, 0.0);
	glVertex3i(5, 5, -5);
	glTexCoord2f(next_width, next_height);
	glVertex3i(5, -5, -5);
	glTexCoord2f(0.0, next_height);
	glVertex3i(5, -5, 5);
	glEnd();

	}
	glDisable(GL_TEXTURE_RECTANGLE_ARB);

}
void exec_cube_animation_left (Slide *slide_now, Slide *slide_next) {

	GLuint texture_now = slide_now->page_texture;
	GLuint texture_next = slide_next->page_texture;

	double now_width   = slide_now->width;
	double now_height  = slide_now->height;
	double next_width  = slide_next->width;
	double next_height = slide_next->height;

	glLoadIdentity();

	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(0, 0, -15);

	if(angle < 45) {
		glTranslatef(0,0,-1*(angle/5.0));
		glRotatef(angle,1,0,0);
	}else {
		glTranslatef(0, 0, -1*((90-angle)/5.0));
		glRotatef(90 - angle, 1, 0, 0);
	}

	glRotatef(left_or_right *angle, 0, -1, 0);
	glEnable(GL_TEXTURE_RECTANGLE_ARB);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	if(angle < 45) {

	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture_next);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,0.0);
	glVertex3i(-5, 5, -5); 
	glTexCoord2f(next_width, 0.0);
	glVertex3i(-5, 5, 5);
	glTexCoord2f(next_width, next_height);
	glVertex3i(-5, -5, 5);
	glTexCoord2f(0.0, next_height);
	glVertex3i(-5, -5, -5);
	glEnd();

	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture_now);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,0.0);
	glVertex3i(-5, 5, 5); 
	glTexCoord2f(now_width, 0.0);
	glVertex3i(5, 5, 5);
	glTexCoord2f(now_width, now_height);
	glVertex3i(5, -5, 5);
	glTexCoord2f(0.0, now_height);
	glVertex3i(-5, -5, 5);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3i(0,1,0);
	glVertex3i(-5, 5,5);
	glVertex3i(5, 5,5);
	glVertex3i(5, 5,-5);
	glVertex3i(-5, 5,-5);
	glEnd();

	}else {
	glBegin(GL_POLYGON);
	glNormal3i(0,1,0);
	glVertex3i(-5, 5,5);
	glVertex3i(5, 5,5);
	glVertex3i(5, 5,-5);
	glVertex3i(-5, 5,-5);
	glEnd();

	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture_now);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,0.0);
	glVertex3i(-5, 5, 5); 
	glTexCoord2f(now_width, 0.0);
	glVertex3i(5, 5, 5);
	glTexCoord2f(now_width, now_height);
	glVertex3i(5, -5, 5);
	glTexCoord2f(0.0, now_height);
	glVertex3i(-5, -5, 5);
	glEnd();

	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture_next);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,0.0);
	glVertex3i(-5, 5, -5); 
	glTexCoord2f(next_width, 0.0);
	glVertex3i(-5, 5, 5);
	glTexCoord2f(next_width, next_height);
	glVertex3i(-5, -5, 5);
	glTexCoord2f(0.0, next_height);
	glVertex3i(-5, -5, -5);
	glEnd();

	}
	glDisable(GL_TEXTURE_RECTANGLE_ARB);

}

