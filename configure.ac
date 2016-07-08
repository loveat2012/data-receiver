#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([data-receiver], [0.1.0], [mombol@163.com])
AC_CONFIG_AUX_DIR(utils)
#AM_INIT_AUTOMAKE(src/data-receiver.c)
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/setup.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h memory.h netinet/in.h stdlib.h string.h sys/file.h sys/param.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_PID_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_CHECK_FUNCS([dup2 inet_ntoa memset mkdir socket strchr strrchr])

# Check for socket library
#AC_CHECK_LIB(socket, socket)

#AC_CONFIG_FILES([Makefile])
#AC_OUTPUT
AC_OUTPUT(Makefile src/Makefile)

echo
echo "--------------------------------------------------------"
echo "Configuration is complete"
echo
echo "Run the following commands to complete the installation:"
echo "  make "
echo "  make install"
echo "--------------------------------------------------------" 
