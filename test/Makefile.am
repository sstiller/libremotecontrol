## Process this file with automake to produce Makefile.in
AM_CPPFLAGS = \
   -std=c++11 \
   -Werror \
   -Wextra

AM_CFLAGS =\
	 -Wall\
	 -g

noinst_PROGRAMS =  \
	serialize-test

serialize_test_SOURCES =  \
	serialize-test.cpp

serialize_test_LDFLAGS = \
  -L$(abs_builddir)/../src/

serialize_test_LDADD =  \
  -lremotectl
