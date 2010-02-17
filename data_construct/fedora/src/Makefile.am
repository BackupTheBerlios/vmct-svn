bin_PROGRAMS = fedora_import
fedora_import_SOURCES = dl.cpp import.cpp repo.cpp
#fedora_import_CXXFLAGS = @CXXFLAGS@ -g -I../../simpleini -I../include -I/usr/include/libxml2
#fedora_import_LDFALGS = @LDFLAGS@ -lxml2 -lz -lm -lcurl
AM_CPPFLAGS = $(DEPS_CFLAGS) $(CURL_CFLAGS)  -g -I../../simpleini -I../include
LIBS = $(DEPS_LIBS) $(CURL_LIBS)
