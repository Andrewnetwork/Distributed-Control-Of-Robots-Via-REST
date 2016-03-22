<?php session_start(); ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
<title>Untitled Document</title>
<script type="text/javascript" src="_JavaScript/jquery.js"></script>
<script type="text/javascript">

	
function process(xml)
{
	var user = $("username",xml).text(); 
	if(user.length > 0)
	{
		$("#currentUser").html(">Current command user: "+user+"<br />");
	}
	else
	{
		$("#currentUser").html(">The robot command queue is empty.<br />");
	}
	
}

function update()
{	
		$.post
		(
			"../REST/ROBOTREST.php", 
		{ 
			username: "<?php echo $_SESSION['username']; ?>", 
			password: "<?php echo $_SESSION['password']; ?>", 
			fn: "current_command_user" 
		},
  			function(xml)
			{
				process(xml);
			}
		);

}

$(document).ready(function() 
{
	
	setInterval("update()", 1000);

});

</script>

</head>

<body>
<div style="font-size:12px; font-family:Verdana, Arial, Helvetica, sans-serif" id="outputPane">
 <div>>Welcome <?php echo $_SESSION['username']; ?></div>
 <div id="currentUser"></div>
 
</div>
</body>
</html>
