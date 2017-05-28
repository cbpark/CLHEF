#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.69])
AC_INIT([CLHEF], [0.1.0.0], [cbpark@gmail.com])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_HEADERS([config/config.h])
AC_CONFIG_MACRO_DIR([m4])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CXX
AC_LANG([C++])
AX_CXX_COMPILE_STDCXX(14,noext,mandatory)
AC_PROG_INSTALL
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
LT_INIT

AC_CHECK_FUNCS([sqrt],,AC_MSG_ERROR([Required math functions not found]))
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE

# ROOT (http://root.cern.ch/)
ROOT_PATH(,AC_MSG_NOTICE([ROOT $ROOTVERSION is found])
           AC_DEFINE([HAVE_ROOT], [1], [Define to 1 if you have ROOT])
           HAVE_ROOT=1, HAVE_ROOT=0)
AM_CONDITIONAL([USE_ROOT], [test "$HAVE_ROOT" -eq 1])

AC_ARG_ENABLE([debug],
[  --enable-debug          turn on debugging],
[case "${enableval}" in
  yes) debug=true ;;
  no)  debug=false ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
esac],[debug=false])
AM_CONDITIONAL([DEBUG], [test x$debug = xtrue])

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
