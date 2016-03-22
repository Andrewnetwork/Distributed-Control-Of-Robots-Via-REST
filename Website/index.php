<?php 

session_start();

 ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<title>CS 240: Controling robots via the web| By Andrew Ribeiro & Jean Silva| Home</title>
<script language="javascript" type="text/javascript" src="_javascript/frontPage.js"></script>

<style type="text/css">
<!--
body {
	background-image: url(_images/kubrickbgcolor.jpg);
	margin-bottom:1em;
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
#Layer1 {
	position:absolute;
	left:764px;
	top:635px;
	width:179px;
	height:99px;
	z-index:1;
	background-color:#FFCC33;
	border:medium #999999 solid;
	padding:5px;
	visibility:hidden;
	text-align:left;
	overflow:auto;
}
#Layer2 {
	position:absolute;
	left:664px;
	top:618px;
	width:179px;
	height:115px;
	z-index:2;
	background-color:#FFCC33;
	border:medium #999999 solid;
	padding:5px;
	visibility:hidden;
	text-align:left;
	overflow:auto;
}
}
-->
</style></head>

<body >

<!-- Help Boxes -->
<div id="Layer1">
	<div style="float:right; padding:3px; background-color:#FF0000; cursor:pointer" onclick="hideThis('Layer1')">Close</div>
	You must have a ustream account if you would like to register a robot. If you already have a ustream account, click <a href="http://helpcenter.ustream.tv/content/can-i-embed-my-broadcast-my-own-site">here</a> for more information on how to get this ustream embedded code. If you dont have a ustream account, create one <a href="http://www.ustream.tv">here</a>
</div>
<div id="Layer2">
<div style="float:right; padding:3px; background-color:#FF0000;cursor:pointer" onclick="hideThis('Layer2')">Close</div>
If you have a robot that you would like to control it exclusively, than select yes. If you do not have a robot of your own and would like to use the group robot, select No.
</div>
<!-- End Help Boxes -->

<!-- Header -->

<?php 
    require("globals.php"); 
	require("header.php"); 
?>
<!-- End Header -->

<div style="margin-bottom:2em; padding:5px">

<div style="float:left; margin-right: 1.6em; margin-bottom:1em; border:thin #000000 solid">
   <img src="_images/diagram.jpg" alt="System Diagram" width="495" height="328" />
</div>

<div style="background-color:#FFFFFF; padding-bottom:5px">
  <center><span style="font-size:18px">About</span></center>
  For our final project in CS 240 Computer Organization and Software, we decided to make a system that allows users to control a LEGO NXT robot from across the internet. Here is a list of components our system uses:
<ul>
  <li><b>USTREAM.COM</b>: this streaming video service allows us to provide users with a live view of their robot performing the tasks they      issued. </li>
<li><b>MySql Database</b>: we use MySql to keep track of commands issued and users that are connected to the system.</li>
<li><b>REST Interface</b>: we expose database information through a REST interface so our desktop program can access it easily.</li> 
<li><b>Desktop Client</b>: we have created a desktop client that is located in the proximity of the NXT robot, which issues commands to the robot that it fetches from the REST web service.</li>
<li><b>Custom Language Processing</b>: we developed a scripting language for the robot control so any novice can use it.</li>  
</ul>
We hope you enjoy using this application and viewing the source code.
</div>
</div>



<div style="width:45%; float:left; text-align:center; background-color:#FFFFFF; padding-bottom:5px; clear:left; margin-top:1em; margin-bottom:1em">
    <b>Login</b>
	<hr />
  	<form action="loginHandler.php" method="post">
	  <label>Username: </label><input name="username" type="text" maxlength="29" /><br/>
	  <label>Password: </label><input name="password" type="password" maxlength="29" /><br /><br />
	  <input name="action" type="submit" value="Login"/>
	</form>
</div>

<div style="width:45%; float:left; text-align:center; margin-left:2em; background-color:#FFFFFF; padding-bottom:5px;margin-top:1em; margin-bottom: 1em; min-width:400px">
    <b>Signup</b>
	<hr />
  	<form action="loginHandler.php" method="post">
	  <div style="text-align:left; margin:0 auto; width:80%">
	  <label>Username: </label><input name="username" type="text" maxlength="29" /><br/><br/>
	  <label>Password: </label><input name="password" type="password" maxlength="29" /><br /><br/>
	  <label>Register a robot(<span onclick="showHelp('Layer2')" style="color:#FF0000; text-decoration:underline">?</span>): </label> 
	  <label>Yes</label><input onclick="registerRobot('ustream')" name="robotRegister" type="radio" value="yes" />
	  <label>No</label><input onclick="dontRegisterRobot('ustream')" name="robotRegister" type="radio" value="no" checked="checked" />
	  <br/><br/>
	  
	  <label>Ustream Embedded Code(<span onclick="showHelp('Layer1')" style="color:#FF0000; text-decoration:underline">?</span>):</label>
	  <br />
	  <textarea id="ustream" name="ustream" cols="40" rows="7" disabled="disabled"></textarea>
	  <br />
	  <br />
	  <input name="action" type="submit" value="Create Account"/>
	  </div>
	</form>
</div>
</div>
<br />
<p>&nbsp;</p>
</body>
</html>
