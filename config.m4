dnl $Id$
dnl config.m4 for extension eventmysql

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(eventmysql, for eventmysql support,
dnl Make sure that the comment is aligned:
dnl [  --with-eventmysql             Include eventmysql support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(eventmysql, whether to enable eventmysql support,
dnl Make sure that the comment is aligned:
dnl [  --enable-eventmysql           Enable eventmysql support])

if test "$PHP_EVENTMYSQL" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-eventmysql -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/eventmysql.h"  # you most likely want to change this
  dnl if test -r $PHP_EVENTMYSQL/$SEARCH_FOR; then # path given as parameter
  dnl   EVENTMYSQL_DIR=$PHP_EVENTMYSQL
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for eventmysql files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       EVENTMYSQL_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$EVENTMYSQL_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the eventmysql distribution])
  dnl fi

  dnl # --with-eventmysql -> add include path
  dnl PHP_ADD_INCLUDE($EVENTMYSQL_DIR/include)

  dnl # --with-eventmysql -> check for lib and symbol presence
  dnl LIBNAME=eventmysql # you may want to change this
  dnl LIBSYMBOL=eventmysql # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $EVENTMYSQL_DIR/$PHP_LIBDIR, EVENTMYSQL_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_EVENTMYSQLLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong eventmysql lib version or lib not found])
  dnl ],[
  dnl   -L$EVENTMYSQL_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(EVENTMYSQL_SHARED_LIBADD)

  PHP_NEW_EXTENSION(eventmysql, eventmysql.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
