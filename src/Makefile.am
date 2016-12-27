## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = \
   -std=c++11 \
   -Werror \
   -Wextra

AM_CFLAGS =\
	 -Wall\
	 -g

lib_LTLIBRARIES = \
    libremotectl.la


libremotectl_la_SOURCES = \
	control-command.cpp \
	set-linux-servo-pwm-command.cpp \
	slave.cpp 

libremotectl_la_LDFLAGS = 

libremotectl_la_LIBADD = 



include_HEADERS = \
	remotectl.h \
	control-command.h \
	set-linux-servo-pwm-command.h \
	slave.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libremotectl.pc

EXTRA_DIST = \
	libremotectl.pc.in

