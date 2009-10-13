METASOURCES = AUTO
SUBDIRS = detector action generator geometry physics ui config
bin_PROGRAMS = gsms
gsms_SOURCES = main.cpp typedefs.h
gsms_LDADD = $(top_builddir)/src/ui/libui.la \
	$(top_builddir)/src/config/libconfig.la $(top_builddir)/src/physics/libphysics.la \
	$(top_builddir)/src/geometry/libgeometry.la $(top_builddir)/src/generator/libgenerator.la \
	$(top_builddir)/src/detector/libdetector.la $(top_builddir)/src/action/libaction.la -L/usr/lib/geant4 -lCLHEP \
	-lG4FR -lG4OpenGL -lG4RayTracer -lG4Tree -lG4UIGAG -lG4UIbasic -lG4UIcommon \
	-lG4VRML -lG4baryons -lG4bosons -lG4csg -lG4cuts -lG4decay -lG4detector \
	-lG4detscorer -lG4detutils -lG4digits -lG4digits_hits -lG4emlowenergy -lG4emstandard \
	-lG4emutils -lG4event -lG4geomBoolean -lG4geombias -lG4geomdivision -lG4geometrymng \
	-lG4globman -lG4graphics_reps -lG4hepnumerics -lG4hits -lG4intercoms -lG4ions \
	-lG4leptons -lG4magneticfield -lG4materials -lG4mesons -lG4modeling -lG4navigation \
	-lG4optical -lG4partman -lG4procman -lG4readout -lG4run -lG4scoring -lG4specsolids \
	-lG4track -lG4tracking -lG4transportation -lG4visHepRep -lG4visXXX \
	-lG4vis_management -lG4volumes -lG4xrays -lboost_iostreams -lboost_serialization
INCLUDES = -I$(top_srcdir)/src
