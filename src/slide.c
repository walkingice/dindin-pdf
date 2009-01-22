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

/**
 * \file slide.c
 * \author Julian Chu (WalkingIce)
 * \date 2008-12-27
 */

#include <stdio.h>
#include <stdlib.h>

#include <glib/poppler.h>
#include <glib.h>

#include <GL/gl.h>

#include "debug.h"
#include "slide.h"

static int create_texture(GLuint *texture_name, GLvoid* pixels, GLsizei width, GLsizei height);
static gchar * get_absolute_filename (const gchar *fileName);

/**
 * @brief Get the URI of the filename
 * @param filename the name of PDF file you want to read in
 * @return the URI of filename
 */
gchar * get_file_uri(const gchar *filename) {
	gchar *abs_filename = get_absolute_filename(filename);
	gchar *filename_uri = g_filename_to_uri (abs_filename, NULL, NULL);
	return filename_uri;
}

/**
 * @brief To pass in a poppler page then initialize a struct for it
 * @param page A poppler page that be used for initialization of slide
 * @param slide the target you want to initial. the struct should be already allocated.
 */
void init_slide(PopplerPage *page, Slide* slide,int index) {

	assert(slide != NULL);
	assert(page != NULL);

	slide->index = index;

	/* Render page into Pixbuf */
	poppler_page_get_size(page,&(slide->width),&(slide->height));
	debug("index= %d, width=%d, height=%d\n", index, (int)slide->width, (int)slide->height);

	gboolean alpha = 1;
	slide->pixbuf  = gdk_pixbuf_new(GDK_COLORSPACE_RGB, alpha, 8, slide->width, slide->height);

	poppler_page_render_to_pixbuf(page, 0, 0, (int)slide->width, (int)slide->height,
			1.0, 0, slide->pixbuf);

	create_texture(&slide->page_texture, gdk_pixbuf_get_pixels(slide->pixbuf)
			, slide->width, slide->height);

	/* Create thumbnail */
	slide->thumb_width  = THUMB_WIDTH;
	slide->thumb_height = THUMB_HEIGHT;
	double thumb_scale_rate_x = slide->thumb_width  /slide->width;
	double thumb_scale_rate_y = slide->thumb_height /slide->height;

	slide->thumbnail = gdk_pixbuf_new(GDK_COLORSPACE_RGB, alpha, 8, slide->thumb_width, slide->thumb_height);

	gdk_pixbuf_scale(slide->pixbuf, slide->thumbnail, 0, 0, slide->thumb_width, slide->thumb_height
			, 0, 0, thumb_scale_rate_x, thumb_scale_rate_y,GDK_INTERP_BILINEAR);
	create_texture(&slide->texture, gdk_pixbuf_get_pixels(slide->thumbnail)
			, slide->thumb_width, slide->thumb_height);
}

/**
 * @brief An inner function what be used by get_file_uri
 * @return The absolute path of filename
 */
static gchar * get_absolute_filename (const gchar *filename) {

	gchar *absolutefilename = NULL;

	if ( g_path_is_absolute (filename) ) {
		absolutefilename = g_strdup (filename);
	} else {
		gchar *currentDir = g_get_current_dir ();
		absolutefilename = g_build_filename (currentDir, filename, NULL);
		g_free (currentDir);
	}

	return absolutefilename;
}

/**
 * @brief Create a texture object from givein data
 * @param texture_name Refer to the texture object what was created by this function
 * @param pixels RGBA data of this texture
 * @param width Width of this texture
 * @param height Height of this texture
 */
static int create_texture(GLuint *texture_name, GLvoid* pixels, GLsizei width, GLsizei height) {

	glEnable(GL_TEXTURE_RECTANGLE_ARB);
	glPixelStorei(GL_UNPACK_SWAP_BYTES,GL_TRUE);
	glPixelStorei(GL_PACK_SWAP_BYTES,GL_TRUE);
	glGenTextures(1, texture_name);
	glBindTexture(GL_TEXTURE_RECTANGLE_ARB, *texture_name);
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA, width, height, 0,
			GL_RGBA, GL_UNSIGNED_BYTE ,pixels);
	return 0;
}

