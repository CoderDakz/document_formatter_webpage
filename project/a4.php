<html>
	
<script type = "text/javascript">
	
	
	function popVisibility(id) {
		var popVar = document.getElementById(id);
		if(popVar.style.display == 'block')
			popVar.style.display = 'none';
		else
			popVar.style.display = 'block';
	}
	
	
	var popup;
	function openPopup()
	{
		popup = document.getElementById('convertBoxC').style.display = "block";
		popup.document.close();
	}
	
	var db;
	function openDB()
	{
		db = document.getElementById('convertBoxDb').style.display = "block";
		db.document.close();
	}
	
	
	function uploadFile()
	{
		document.getElementById('fileToUpload').click();
		
		document.getElementById('fileToUpload').addEventListener("change", myFunction);
	}
	
	function myFunction()
	{
		document.getElementById('submitButton').click();
	}
	
</script>

<style type="text/css">

			#convertBoxC
			{
				position: fixed; 
				width: 100%; 
				height: 120%;
				background-color: rgba(0,0,0,0.7); 
				display: none;
			}
			
			#convertBoxDb
			{
				position: fixed; 
				width: 100%; 
				height: 120%;
				background-color: rgba(0,0,0,0.7); 
				display: none;
			}
			
			.convertBoxWrapper
			{
				width: 400px; 
				margin: 50px auto; 
			}
			
			.convertBoxSpecs
			{
				height: 60%; 
				width: 100%;
				background-color: #F2F2F2; 
				padding: 15px;
			}

</style>



<body style = "background-color: #CCCCCC;">

	<!--Convert Button-->
	<div id="convertBoxC">
		
		<div class="convertBoxWrapper">
			
			<div class="convertBoxSpecs" style = "position: relative; text-align: center;">
				
				<p><b><font size = "15" color = "black" face = "Impact"><center><u>Convert</u></center></font></b></p>
				
				<div style = "height:60%; overflow:scroll; background-color:#F2F2F2; color: #CE54FF;
				scrollbar-base-color: #54FF54; border: 20px groove #0C00FF;"> 

				<form action = "cOpener.php" method = "post">
				
					<?php
						$dir = "./files";
						if($dh = opendir($dir))
						{
							
							echo "<select id = \"textSelection\" name = \"textSelection\" style = \"width:75%\";>";
							while(($file = readdir($dh)) != false)
							{
								if(is_dir($file) != true)
								{
									$extendo = pathinfo($file, PATHINFO_EXTENSION);
									if(strcmp($extendo, "html") != 0 && strcmp($extendo, "info") != 0)
									{
										echo '<option>'.$file.'</option>';
									}
								}
								
							}
							echo "</select>";
							closedir($dh);
						}
					?>
					
					<div style = "padding: 50px;">
						
						<?php
							$dir = "./files";
							if($dh = opendir($dir))
							{
								while(($file = readdir($dh)) != false)
								{
									if(is_dir($file) != true)
									{
										$extendo = pathinfo($file, PATHINFO_EXTENSION);
										if(strcmp($extendo, "html") != 0 && strcmp($extendo, "info") != 0)
										{
											echo $file . "<br>";
										}
						
									}
							
								}
								closedir($dh);
							}
						?>
					</div>
						
					
					
					</div>
				
					<div style = "text-align: center; border: 2px solid black; font-size: 300%;position: relative;">
						
						<input type = "button" value = "CANCEL" onclick="popVisibility('convertBoxC');" style= "color:red; background-color:#0036FF; font-weight: 900;"></input>
						
						<button type = "submit" name = "cOpen" id = "cOpen" onclick="popVisibility('convertBoxC');" style = "color: #5DFF00; background-color: #0036FF; font-weight: bold;">OK</button>
					
					</div>
				</form>
			</div>
		</div>
	</div>
	
	
	<!--DB STORE BUTTON-->
	<div id="convertBoxDb">
		
		<div class="convertBoxWrapper">
			
			<div class="convertBoxSpecs" style = "position: relative; text-align: center;">
				
				<p><b><font size = "15" color = "black" face = "Impact"><center><u>Convert</u></center></font></b></p>
				
				<div style = "height:60%; overflow:scroll; background-color:#F2F2F2; color: #CE54FF;
				scrollbar-base-color: #54FF54; border: 20px groove #0C00FF;"> 

				<form action = "dbConvert.php" method = "post">
				
					<?php
						$dir = "./files";
						if($dh = opendir($dir))
						{
							
							echo "<select id = \"textSelection\" name = \"textSelection\" style = \"width:75%\";>";
							while(($file = readdir($dh)) != false)
							{
								if(is_dir($file) != true)
								{
									$extendo = pathinfo($file, PATHINFO_EXTENSION);
									if(strcmp($extendo, "html") != 0 && strcmp($extendo, "info") != 0)
									{
										echo '<option>'.$file.'</option>';
									}
								}
								
							}
							echo "</select>";
							closedir($dh);
						}
					?>
					
					<div style = "padding: 50px;">
						
						<?php
							$dir = "./files";
							if($dh = opendir($dir))
							{
								while(($file = readdir($dh)) != false)
								{
									if(is_dir($file) != true)
									{
										$extendo = pathinfo($file, PATHINFO_EXTENSION);
										if(strcmp($extendo, "html") != 0 && strcmp($extendo, "info") != 0)
										{
											echo $file . "<br>";
										}
						
									}
							
								}
								closedir($dh);
							}
						?>
					</div>
						
					
					
					</div>
				
					<div style = "text-align: center; border: 2px solid black; font-size: 300%;position: relative;">
						
						<input type = "button" value = "CANCEL" onclick="popVisibility('convertBoxDb');" style= "color:red; background-color:#0036FF; font-weight: 900;"></input>
						
						<button type = "submit" name = "dbOpen" id = "dbOpen" onclick="popVisibility('convertBoxDb');" style = "color: #5DFF00; background-color: #0036FF; font-weight: bold;">OK</button>
					
					</div>
				</form>
			</div>
		</div>
	</div>


	<div style = "width:100%;height:10%;">
		<!-- convert button -->
		<div style = "height:100%; width:33%; float:left;">
	
			<button onclick = "openPopup();" style = " background-color:#F2F2F2; border: 5px dotted black;width:100%;height:100%;"
		
				<p><b><font size = "5em//15px" color = "black" face = "Impact" align = "relative" >Convert</font></b></p>
	
			</button>
		</div>
	
		<!-- Upload button -->
		<div style = "height:100%; width:33%; float:left;">
	
				<button onclick = "uploadFile();" id="uploadButton" type = "submit" style = "width:100%;background-color:#F2F2F2; border:5px dotted black;height:100%;"
			
					<p><b><font size = "5em//15px" color = "black" face = "Impact">Upload</font></b></p>
		
				</button>
		</div>
	
		<!-- DB Store button -->
		<div style = "height:100%; width:33%; float:left;">
			<button onclick = "openDB();" style = " background-color:#F2F2F2; border: 5px dotted black;width:100%;height:100%;"
		
				<p><b><font size = "5em//15px" color = "black" face = "Impact" align = "relative" >DB Store</font></b></p>
	
			</button>
		</div>
	</div>

	<!-- box containing text files -->
	<div style = "float:left; background-color: black; text-align:center; width:50%; ">
	
		<div style = "border: 10px double white ;">
	
			<font size = "6" color = "white" face = "Comic sans MS"><i>Text Files</i></font>
	
		</div>
	
		<div style = "height:49%; overflow:scroll; background-color:#F2F2F2; color: #CE54FF;
					scrollbar-base-color: #54FF54; border: 20px groove #0C00FF; text-align: left;padding: 3%;">
				
					<?php
						$dir = "./files";
						if($dh = opendir($dir))
						{
							while(($file = readdir($dh)) != false)
							{
								if(is_dir($file) != true)
								{
									$extendo = pathinfo($file, PATHINFO_EXTENSION);
									if(strcmp($extendo, "html") != 0 && strcmp($extendo, "info") != 0)
									{
										print("<a href=./files/" . $file. ">" . $file. "</a><br />\n");
									}
								}
							}
							closedir($dh);
						}
					?>		
		</div>
	</div>

	<!-- box containing html files -->
	<div style = "float:right;background-color: black; text-align:center; width:50%; ">
	
		<div style = "border: 10px double white ;">
	
			<font size = "6" color = "white" face = "Comic sans MS"><i>HTML Files</i></font>
	
		</div>
		
		<div style = "height:49%; overflow:scroll; background-color:#F2F2F2; color: #CE54FF;
					scrollbar-base-color: #54FF54; border: 20px groove #0C00FF;text-align: left; padding: 3%;">
				
					<?php
					
						$servArray = [];
						
						
						$dbArray=[];
						$dbString = shell_exec('./db -fNames');
						$dbArray = explode(' ', $dbString);
						$combinedArray = [];
						
						$dir = "./files";
						if($dh = opendir($dir))
						{
							while(($file = readdir($dh)) != false)
							{
								if(is_dir($file) != true)
								{
									$extendo = pathinfo($file, PATHINFO_EXTENSION);
									if(strcmp($extendo, "html") == 0)
									{
										//$noExt = preg_replace('/\\.[^.\\s]{3,4}$/', '', $file);
										$servArray[] = $file;
										//print("<a href=./files/" . $file. ">" . $file. "</a><br />\n");
									}	
								}	
							}
							closedir($dh);
						}
						
						//how to print out whole array, use this method once combining DB files + server files then
						//alphabetizing them
						$combinedArray = array_merge($servArray, $dbArray);
						natcasesort($combinedArray);
						foreach($combinedArray as &$val)
						{
							if(in_array($val, $servArray))
							{
								if($val != NULL)
								{
									print("<a href=./files/" . $val. ">" . $val. "</a><br />\n");
								}
							}
							if(in_array($val, $dbArray))
							{
								if($val != NULL)
								{
									print("<a href=\"returnHtml.php?filename=".$val. "\">" . $val. ".html</a><br />\n");
									
								}
							}
							
						}
						/*
						foreach($servArray as &$value)
						{
							print("<a href=./files/" . $value. ">" . $value. "</a><br />\n");
						}
						foreach($dbArray as &$value)
						{
							if($value != NULL)
							{
								print("<a href=./files/" . $value. ">" . $value. ".html</a><br />\n");
							}
							
						}*/
					?>
		</div>
	</div>

	<form id = "uploadAct" action = "upload.php" method = "post" enctype = "multipart/form-data">
		
			<input type = "file" name = "fileToUpload" id = "fileToUpload" style = "visibility:hidden;">
		
			<input type = "submit" value = "Upload Image" id = "submitButton" name = "submit" style = "visibility:hidden;">
	</form>

</body>
</html>

