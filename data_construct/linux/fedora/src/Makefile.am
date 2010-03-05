bin_PROGRAMS = fedora_import
fedora_import_SOURCES = dl.cpp import.cpp repo.cpp xml.cpp func.cpp log.cpp
AM_CPPFLAGS = $(XML_CFLAGS) $(CURL_CFLAGS) -I../../simpleini -I../include -Werror
LIBS = $(XML_LIBS) $(CURL_LIBS)
