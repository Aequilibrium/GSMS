INCLUDES = -I$(top_srcdir)/src
METASOURCES = AUTO
noinst_LTLIBRARIES = libgenerator.la
libgenerator_la_SOURCES = Generator.cpp Generator.h Source.cpp Source.h \
	SourceLib.cpp SourceLib.h
SUBDIRS = database
libgenerator_la_LIBADD = $(top_builddir)/src/generator/database/libdatabase.la
