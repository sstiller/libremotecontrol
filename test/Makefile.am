## Process this file with automake to produce Makefile.in
AM_CPPFLAGS = \
   -std=c++11 \
   -Werror \
   -Wextra

AM_CFLAGS =\
	 -Wall\
	 -g

noinst_PROGRAMS =  \
	serialize-test \
	servertest

serialize_test_SOURCES =  \
	serialize-test.cpp \
	helpers.h \
	helpers.cpp

serialize_test_LDFLAGS = \
  -L$(abs_builddir)/../src/ \
  -pthread

serialize_test_LDADD =  \
  -lremotectl \
  -lboost_system 


servertest_SOURCES =  \
	servertest.cpp \
	helpers.h \
	helpers.cpp

servertest_LDFLAGS = \
  -L$(abs_builddir)/../src/ \
  -pthread

servertest_LDADD =  \
  -lremotectl \
  -lboost_system
