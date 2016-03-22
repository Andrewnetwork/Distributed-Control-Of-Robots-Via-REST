<?php 

session_start();

 ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<title>CS 240: Controling robots via the web| By Andrew Ribeiro & Jean Silva| Videos</title><style type="text/css">
<!--
body {
	background-image: url(../_images/kubrickbgcolor.jpg);
}
a:link {
	color: #999999;
	text-decoration: underline;
}
a:visited {
	text-decoration: underline;
	color: #333333;
}
a:hover {
	text-decoration: none;
}
a:active {
	text-decoration: underline;
}
-->
</style></head>

<body >

<!-- Header -->
<?php 
	require('../globals.php'); 
	require("../header.php");
 ?>
<!-- End Header -->

<div style="background-color:#FFFFFF; padding:6px; border: thin #999999 dashed ">
  <div style=" text-align:center">
    <object width="425" height="344">
      <param name="movie" value="http://www.youtube.com/v/wiwXnVkPLZw&hl=en_US&fs=1&" />
      <param name="allowFullScreen" value="true" />
      <param name="allowscriptaccess" value="always" />
      <embed src="http://www.youtube.com/v/wiwXnVkPLZw&hl=en_US&fs=1&" 
			   type="application/x-shockwave-flash" 
			   allowscriptaccess="always" 
			   allowfullscreen="true" 
			   width="425" 
			   height="344"> </embed>
    </object>
	&nbsp;
	</div>
    
	<div>
	 <center>
  	 <b>Introduction</b>
	 </center>
	 We developed a system to controll NXT robots from across the internet. Our system consists of six main components:
		 <ol>
	  <li><b>USTREAM.COM</b>: this streaming video service allows us to provide users with a live view of their robot performing the tasks they      issued. </li>
	<li><b>MySql Database</b>: we use MySql to keep track of commands issued and users that are connected to the system.</li>
	<li><b>REST Interface</b>: we expose database information through a REST interface so our desktop program can access it easily.</li> 
	<li><b>Desktop Client</b>: we have created a desktop client that is located in the proximity of the NXT robot, which issues commands to the robot that it fetches from the REST web service.</li>
	<li><b>NXT Robot</b>: the robot we control</li>  
	<li><b>Web interface</b>: a command interface accessible from the web</li>  
	
	</ol><br/>
	<b>Notes:</b>
	<ul>
	<li>The desktop client and NXT robot must be within close proximity to eachother</li>
	<li>The web user does not need to be near the NXT robot or Desktop client</li>
	<li>The web user is unaware of the desktop client, and does not directly access it</li>
	<li>The desktop client was writen in C++</li>
	<li>The REST interface was writen in PHP</li>
	<li>The web interface was writen in: XHTML and JavaScript.</li>
	</ul>
    </div>
</div>
<hr />
<div style="background-color:#FFFFFF; padding:6px; border: thin #999999 dashed ">
  <div style=" text-align:center"><object width="425" height="344"><param name="movie" value="http://www.youtube.com/v/D7e9ITAol2I&hl=en_US&fs=1&rel=0"></param><param name="allowFullScreen" value="true"></param><param name="allowscriptaccess" value="always"></param><embed src="http://www.youtube.com/v/D7e9ITAol2I&hl=en_US&fs=1&rel=0" type="application/x-shockwave-flash" allowscriptaccess="always" allowfullscreen="true" width="425" height="344"></embed></object>&nbsp;	</div>
    
	<div>
	 <center>
  	 <b>System Demonstration</b>
	 </center>
	 A short demonstration of how our system works.
    </div>
</div>
</body>
</html>
