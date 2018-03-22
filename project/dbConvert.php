<?php
	if(isset($_POST['dbOpen']))
	{
		$file = $_POST['textSelection'];
		
		exec('./a4 ./files/' . $file . ' 1' );
		
		
		exec('rm ./files/' . $file . '.html');
		header("Location: ./a4.php");
		die();
	}
?>
