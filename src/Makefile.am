AM_CXXFLAGS = -std=c++11 -I$(top_srcdir)/src

if DEBUG
AM_CXXFLAGS += -O0 -Wall -Wextra -pedantic
endif

if USE_ROOT
AM_CXXFLAGS += $(ROOTCFLAGS)
endif

lib_LTLIBRARIES      = libCLHEF.la
libCLHEF_la_SOURCES  = event.cc lhef.cc parser.cc particle.cc kinematics.cc
if USE_ROOT
libCLHEF_la_LIBADD   = -L$(ROOTLIBDIR) $(ROOTLIBS)
endif

pkginclude_HEADERS = event.h lhef.h parser.h particle.h kinematics.h \
	pdg_numbering.h

if DEBUG
noinst_bindir = $(top_builddir)
noinst_bin_PROGRAMS = test_parse test_render

test_parse_SOURCES = test_parse.cc
test_parse_LDADD   = libCLHEF.la

test_render_SOURCES = test_render.cc
test_render_LDADD   = libCLHEF.la

if USE_ROOT
test_parse_LDADD += -L$(ROOTLIBDIR) $(ROOTLIBS)
test_render_LDADD += -L$(ROOTLIBDIR) $(ROOTLIBS)
endif
endif
