<? 

session_start(); 

// Checking if the user is authenticated/has logged in. 
if(strlen($_SESSION["username"]) == 0)
{
	header("Location:../");
}

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<title>CS 240: Controling robots via the web| By Andrew Ribeiro & Jean Silva| Comand Centre</title>
<style type="text/css">
<!--
body {
	background-image: url(../_images/kubrickbgcolor.jpg);
}

-->
</style>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<script type="text/javascript" src="_JavaScript/jquery.js"></script>

<script type="text/javascript">
var formContents;

 $(document).ready(function() {
      
	  
  	  $("#run").click(function(){
	  	/*
	     $("#form1").fadeOut("slow");
		 $("#codeForm").html('<br /><img src="_images/LoadingGif.gif" alt="Loading Commands" width="140" height="100" />');
		 */
			$.post("../REST/ROBOTREST.php", 
			{ 
				username: "<?php echo $_SESSION['username']; ?>", 
				password: "<?php echo $_SESSION['password']; ?>", 
				fn: "submit_command",
				arg:$("#code").val()
			});
			
			alert("Script Submited");
		   
		 });
		 
		 
	  $("#clear").click(function(){
	    $("#code").val("");
		});
	  
 });

</script>

<title>CS 240: Controling robots via the web| By Andrew Ribeiro & Jean Silvia| Comand Centre</title>
<style type="text/css">
<!--gththethetheth
body {
	background-color: #9BD7FF;
}
body {
	background-color: #9BBCFF;
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

<body id="mainBody" style="margin:0">

<!-- Header -->
<?php 
	require('../globals.php'); 
	require("../header.php");
 ?>
<!-- End Header -->

<div style="width:50%; float:left; margin-top:40px">
<center><div style="background-color:#FFFFFF"><b>Enter your commands here</b></div></center>
<center>
 <div id="codeForm" style="padding:5px">
  <form id="form1" name="form1" method="post" action="" style="text-align:center">
    <textarea id="code" name="code" cols="100" rows="30" style="width:100%"></textarea>
    <input type="button" name="button" id="run" value="Run" />
	<input type="button" name="button" id="clear" value="Clear" />
	<input name="fn" type="hidden" value="submit_command" />
  </form>
  </div>
</center>


</div>

<div style="width:50%; float:left; text-align:center">
 <img src="../_images/liveView.png" />
  <p>
  <div>
    <object classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000" width="400" height="320" id="utv844608">
      <param name="flashvars" value="autoplay=false&amp;brand=embed&amp;cid=1957912"/><param name="allowfullscreen" value="true"/><param name="allowscriptaccess" value="always"/><param name="movie" value="http://www.ustream.tv/flash/live/1/1957912"/>
      <embed flashvars="autoplay=false&amp;brand=embed&amp;cid=1957912" width="400" height="320" allowfullscreen="true" allowscriptaccess="always" id="utv844608" name="utv_n_321387" src="http://www.ustream.tv/flash/live/1/1957912" type="application/x-shockwave-flash" />  
    </object>
  </p>
  </div>
  
  
  <div style="background-color:#0099FF;width:90%; margin:0 auto">
	<div style="text-align:center; border:thin solid #000000; background-color:#CCCCCC; padding-top:5px; padding-bottom:5px">
		<b>
		  System Log
		</b>
	</div>
	
	<div>
		<iframe src="systemLog.php" style="border:0px; background-color:#999999";  width="100%" height="100px"></iframe>
	</div>
</div>


</div>




</body>
</html>
