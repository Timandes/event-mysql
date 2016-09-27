--TEST--
Check for eventmysql_get_conn_fd error behavior
--FILE--
<?php

$h = NULL;
$fd = eventmysql_get_conn_fd($h);

var_dump($fd);

?>
--EXPECTF--
Warning: eventmysql_get_conn_fd(): Illegal MySQLi object was found in %s on line %d
bool(false)

