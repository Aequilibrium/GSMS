INCLUDES = -I$(top_srcdir)/src
METASOURCES = AUTO
noinst_LTLIBRARIES = libconfig.la
libconfig_la_SOURCES = Config.cpp DetectorConfig.cpp Exception.cpp GSMS.cpp \
	GlobalConfig.cpp HullConfig.cpp Job.cpp MaskConfig.cpp SceneConfig.cpp
libconfig_la_LIBADD = $(top_builddir)/src/action/libaction.la
noinst_HEADERS = Config.h DetectorConfig.h Exception.h GSMS.h GlobalConfig.h \
	HullConfig.h Job.h MaskConfig.h SceneConfig.h Waypoint.h
