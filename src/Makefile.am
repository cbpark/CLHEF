AM_CXXFLAGS = -O2 -Wall -Wextra -std=c++14 -pedantic -I$(top_srcdir)/src

lib_LTLIBRARIES      = libCLHEF.la
libCLHEF_la_SOURCES  = event.cc lhef.cc parser.cc particle.cc
if USE_ROOT
libCLHEF_la_CXXFLAGS = $(AM_CXXFLAGS) @ROOTCFLAGS@
endif

pkginclude_HEADERS = event.h lhef.h parser.h particle.h kinematics.h \
	pdg_numbering.h
