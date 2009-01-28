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

#ifndef __SLIDE_H_
#define __SLIDE_H_

#include <glib/poppler.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

#include "list.h"

#define THUMB_WIDTH 128
#define THUMB_HEIGHT 128

struct _Slide{
	struct list_head node;
	int index;
	double width;
	double height;
	GdkPixbuf* pixbuf;

	double thumb_width;
	double thumb_height;
	GdkPixbuf* thumbnail;

	GLuint texture;
	GLuint page_texture;
};

typedef struct _Slide Slide;

gchar* get_file_uri(const gchar *filename);
void   init_slide(PopplerPage *page, Slide* slide, int index);
#endif
