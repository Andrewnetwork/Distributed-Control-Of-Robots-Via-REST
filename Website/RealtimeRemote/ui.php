<? session_start(); ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<title>CS 240: Controling robots via the web| By Andrew Ribeiro & Jean Silva| Remote Control</title>
<style type="text/css">
<!--
body {
background-image:url(../_images/kubrickbgcolor.jpg)
}
-->
</style></head>

<body>
	<!-- Header -->
	<?php 
		require('../globals.php'); 
		require("../header.php");
	 ?>
	<!-- End Header -->
	<div style="text-align:center; font-size:40px; margin-bottom:10px; background-color:#FFFFFF">Robot Remote</div>
	<div style="margin:0 auto; width:500px; border: thick #000000 solid; text-align:center; padding:2em; background-color:#FFCC33">
		<div style="margin:0px auto;border: thick #000000 solid; width:398px">
			<?php
				
				if(isset($_SESSION["playerCode"]) == true)
				{
					echo $_SESSION["playerCode"];
				}
				else
				{
					echo '<img src="_images/missingVideo.png" width = "398" height="315" alt="Missing Video" />';
				}
			
			?>
		</div>
		<div style="margin-top:1em">
			<object classid="clsid:D27CDB6E-AE6D-11cf-96B8-444553540000" 
				codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=7,0,19,0" 
					width="200" height="200">
	 		 <param name="movie" value="_media/controll.swf" />
	 		 <param name="quality" value="high" />
			 <PARAM NAME="FlashVars" VALUE="username=<?php echo $_SESSION["username"] ?>&password=<?php echo $_SESSION["password"] ?>">
			 <param name="wmode" value="transparent" />
	  		 <embed src="_media/controll.swf" 
			 	FlashVars="username=<?php echo $_SESSION["username"] ?>&password=<?php echo $_SESSION["password"] ?>" 
               quality="high" wmode="transparent" pluginspage="http://www.macromedia.com/go/getflashplayer" 
			  	type="application/x-shockwave-flash" width="200" height="200"></embed>
			</object>
		</div>

	</div>
</body>
</html>
