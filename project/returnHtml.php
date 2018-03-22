<?php
	
	$urlString = $_SERVER['QUERY_STRING'];
	$htmlName = substr($urlString, 9);


	$htmlReturn = shell_exec('./db -returnHtml ' . $htmlName);
	echo $htmlReturn;

?>

