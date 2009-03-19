ACLOCAL_AMFLAGS = -I m4
MAINTAINERCLEANFILES = Makefile.in aclocal.m4 config.guess config.h.in \
		       config.sub configure depcomp install-sh ltmain.sh \
		       missing config.rpath mkinstalldirs 
SUBDIRS = 

confdir = $(pkgdatadir)

INCLUDES = -I. \
         -I$(top_srcdir) \
	-Wall	\
	-Werror \
	-DPACKAGE_NAME=\"@PACKAGE_NAME@\"  \
	$(DINDIN_CFLAGS)

bin_PROGRAMS = dindin

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
		  
dindin_LDADD = $(DINDIN_LIBS) -lglut

clean-local:
	rm -rf *~
	
uninstall-hook:
	rm -rf $(datadir)

indent:
	astyle --style=linux -p -s4 -n --brackets=attach *.[ch]
