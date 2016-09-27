PHP_ARG_ENABLE(eventmysql, whether to enable eventmysql support,
Make sure that the comment is aligned:
[  --enable-eventmysql           Enable eventmysql support])

if test "$PHP_EVENTMYSQL" != "no"; then
  PHP_NEW_EXTENSION(eventmysql, eventmysql.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
