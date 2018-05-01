AC_INIT([addwmark], [0.1], [andregsilv@gmail.com])
AM_INIT_AUTOMAKE

m4_pattern_allow([AC_MSG_ERROR])
LT_INIT
AC_PROG_CXX

AC_CONFIG_MACRO_DIRS([m4])
AC_CONFIG_FILES([Makefile src/Makefile])

AX_OPENCV

AX_BOOST_BASE([],[],[ AC_MSG_ERROR([boost was not found on your system])])
AX_BOOST_PROGRAM_OPTIONS()

AC_OUTPUT

