PHP_ARG_ENABLE(eventmysql, whether to enable eventmysql support,
Make sure that the comment is aligned:
[  --enable-eventmysql           Enable eventmysql support])

if test "$PHP_EVENTMYSQL" != "no"; then

  if test "$PHP_MYSQLI" != "no" && test "$PHP_MYSQLND" != "no"; then
    AC_DEFINE([MYSQLI_USE_MYSQLND], 1, [Whether mysqli is enabled with mysqlnd])
  else
    AC_MSG_RESULT([no])
  fi

  PHP_NEW_EXTENSION(eventmysql, eventmysql.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
