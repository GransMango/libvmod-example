AM_CFLAGS = $(VARNISHAPI_CFLAGS) -Wall -Werror
AM_LDFLAGS = $(VARNISHAPI_LIBS) $(VMOD_LDFLAGS)

vmod_LTLIBRARIES = libvmod_hiring.la

libvmod_hiring_la_SOURCES = \
	vmod_hiring.c

nodist_libvmod_hiring_la_SOURCES = \
	vcc_hiring_if.c \
	vcc_hiring_if.h

dist_man_MANS = vmod_hiring.3

@BUILD_VMOD_HIRING@

AM_TESTS_ENVIRONMENT = \
	PATH="$(VMOD_TEST_PATH)" \
	LD_LIBRARY_PATH="$(VARNISH_LIBRARY_PATH)"
TEST_EXTENSIONS = .vtc
VTC_LOG_COMPILER = varnishtest -v
AM_VTC_LOG_FLAGS = -Dvmod_hiring="$(VMOD_HIRING)"

TESTS = @VMOD_TESTS@

EXTRA_DIST = \
	vmod_hiring.vcc \
	$(VMOD_TESTS)
