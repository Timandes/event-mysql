--TEST--
Check for eventmysql_get_conn_fd error behavior
--FILE--
<?php

$h = new MySQLi('localhost', 'root', '');
$h->close();
$fd = eventmysql_get_conn_fd($h);

var_dump($fd);

?>
--EXPECTF--
Warning: eventmysql_get_conn_fd(): Couldn't fetch mysqli in %s on line %d
NULL

