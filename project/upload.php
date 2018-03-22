<?php
	
	$dir = "./files/";
	$file = $dir . basename($_FILES["fileToUpload"]["name"]);

	if(move_uploaded_file($_FILES["fileToUpload"]["tmp_name"],$file))
	{
		header("Location: ./a4.php");
		die();
	}
	else
	{
		echo "no";
	}


?>
