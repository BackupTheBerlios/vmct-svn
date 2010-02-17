AC_INIT([fedora-import], [0.1], [andrey.baboshin@gmail.com])
PKG_CHECK_MODULES(DEPS, libxml-2.0 >= 2.4)
PKG_CHECK_MODULES(CURL, libcurl >= 7.10.0)
AC_SUBST(DEPS_CFLAGS)
AC_SUBST(DEPS_LIBS)
AC_SUBST(CURL_CFLAGS)
AC_SUBST(CURL_LIBS)
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CXX
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
])
AC_OUTPUT

