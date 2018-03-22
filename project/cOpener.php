<?php
	if(isset($_POST['cOpen']))
	{
		$file = $_POST['textSelection'];
		
		exec('./a4 ./files/' . $file . ' 0');
		
		header("Location: ./a4.php");
		die();
	}
?>
