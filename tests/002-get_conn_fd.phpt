--TEST--
Check for eventmysql_get_conn_fd 
--FILE--
<?php

$h = new MySQLi('localhost', 'root', '');
$fd = eventmysql_get_conn_fd($h);

var_dump($fd);

?>
--EXPECT--
int(3)

