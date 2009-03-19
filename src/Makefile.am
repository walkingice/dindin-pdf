ACLOCAL_AMFLAGS = -I m4
MAINTAINERCLEANFILES = Makefile.in aclocal.m4 config.guess config.h.in \
		       config.sub configure depcomp install-sh ltmain.sh \
		       missing config.rpath mkinstalldirs 
SUBDIRS = 

confdir = $(pkgdatadir)

othercflag = `pkg-config --cflags glib-2.0`
otherlibs = `pkg-config --libs glib-2.0` -lglut

INCLUDES = -I. \
         -I$(top_srcdir) \
	-Wall	\
	-Werror \
	-DPACKAGE_NAME=\"@PACKAGE_NAME@\"  \
        @poppler_cflags@ \
	@pango_cflags@ \
	@cairo_cflags@ \
	@gdkpixbuf_cflags@ \
	$(othercflag)

bin_PROGRAMS =dindin

noinst_HEADERS = cover_animation.h \
		 cube_animation.h \
		 debug.h \
		 global.h \
		 list.h \
		 slide.h \
		 slide_view.h \
		 slip_animation.h \
		 state.h \
		 toolkit.h \
		 toolkit_glut.h \
		 thumb_view.h

dindin_SOURCES = cover_animation.c \
		 cube_animation.c \
		 dindin.c \
		 slide.c \
		 slide_view.c \
		 slip_animation.c \
		 state.c \
		 toolkit.c \
		 toolkit_glut.c \
		 thumb_view.c
		  
dindin_LDADD = @poppler_libs@\
	       @pango_libs@ \
               @cairo_libs@ \
	       @gdkpixbuf_libs@

dindin_LDFLAGS = $(otherlibs)

files_BIN = dindin

	     
EXTRA_DIST = $(files_BIN)

clean-local:
	rm -rf *~
	
uninstall-hook:
	rm -rf $(datadir)

indent:
	astyle --style=linux -p -s4 -n --brackets=attach *.[ch]
