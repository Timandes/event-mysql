/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_eventmysql.h"
#include "php_network.h"
#include "ext/mysqli/php_mysqli_structs.h"

#define EVENTMYSQL_FETCH_MYSQLI_OBJ_NAME(link) Z_OBJCE_P(link)->name
#ifdef ZEND_ENGINE_3
#define EVENTMYSQL_FETCH_MYSQLI_OBJ_NAME_STR(link) ZSTR_VAL(EVENTMYSQL_FETCH_MYSQLI_OBJ_NAME(link))
#else
#define EVENTMYSQL_FETCH_MYSQLI_OBJ_NAME_STR(link) EVENTMYSQL_FETCH_MYSQLI_OBJ_NAME(link)
#endif

/* If you declare any globals in php_eventmysql.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(eventmysql)
*/

/* True global resources - no need for thread safety here */
static int le_eventmysql;


/* {{{ Get FD of MySQLi connection
 */
PHP_FUNCTION(eventmysql_get_conn_fd)
{
    zval *link;
    MY_MYSQL *mysql;
    php_stream *stream;
    php_socket_t fd = -1;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &link) == FAILURE) {
        return;
    }

    if (Z_TYPE_P(link) != IS_OBJECT
            || strcasecmp(EVENTMYSQL_FETCH_MYSQLI_OBJ_NAME_STR(link), "mysqli") != 0) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Illegal MySQLi object was found");
        RETURN_FALSE;
    }

#if PHP_MAJOR_VERSION > 5
    MYSQLI_FETCH_RESOURCE_CONN(mysql, link, MYSQLI_STATUS_VALID);
    stream = mysql->mysql->data->net->data->m.get_stream(mysql->mysql->data->net TSRMLS_CC);
#elif PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION > 4
    MYSQLI_FETCH_RESOURCE_CONN(mysql, &link, MYSQLI_STATUS_VALID);
    stream = mysql->mysql->data->net->data->m.get_stream(mysql->mysql->data->net TSRMLS_CC);
#else
    MYSQLI_FETCH_RESOURCE_CONN(mysql, &link, MYSQLI_STATUS_VALID);
    stream = mysql->mysql->data->net->stream;
#endif

    if (php_stream_cast(stream, PHP_STREAM_AS_FD_FOR_SELECT | PHP_STREAM_CAST_INTERNAL, (void* )&fd, 1) != SUCCESS
            || fd <= 2) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Fail to convert stream to FD");
        RETURN_FALSE;
    }

    if (fd <= 0) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "Illegal FD was found");
        RETURN_FALSE;
    } else {
        RETURN_LONG((zend_long)fd);
    }
}
/* }}} */


/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(eventmysql)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(eventmysql)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(eventmysql)
{
#if defined(COMPILE_DL_EVENTMYSQL) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(eventmysql)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(eventmysql)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "EventMySQL support", "enabled");
	php_info_print_table_end();
}
/* }}} */

ZEND_BEGIN_ARG_INFO_EX(arginfo_eventmysql_get_conn_fd, 0, 0, 1)
    ZEND_ARG_INFO(0, link)
ZEND_END_ARG_INFO()

/* {{{ eventmysql_functions[]
 *
 * Every user visible function must have an entry in eventmysql_functions[].
 */
const zend_function_entry eventmysql_functions[] = {
    PHP_FE(eventmysql_get_conn_fd, arginfo_eventmysql_get_conn_fd)
	PHP_FE_END	/* Must be the last line in eventmysql_functions[] */
};
/* }}} */

/* {{{ eventmysql_module_entry
 */
zend_module_entry eventmysql_module_entry = {
	STANDARD_MODULE_HEADER,
	"eventmysql",
	eventmysql_functions,
	PHP_MINIT(eventmysql),
	PHP_MSHUTDOWN(eventmysql),
	PHP_RINIT(eventmysql),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(eventmysql),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(eventmysql),
	PHP_EVENTMYSQL_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_EVENTMYSQL
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(eventmysql)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
