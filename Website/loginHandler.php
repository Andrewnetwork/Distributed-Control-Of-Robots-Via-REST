<? 

session_start(); 
session_destroy();
session_start(); 

?>
<?php

function usernameExists($MySqlConnection, $username)
{
  $query = 'SELECT username FROM user where username = "'.$username.'"';
  
  $result = $MySqlConnection->query($query);
  
  if ($result->num_rows > 0) 
  {
    return true; 		
  }
  else
  {
    return false;
  }
}

// If all values are set.
if(strlen($_POST["username"]) != NULL && strlen($_POST["password"]) != NULL  && strlen($_POST["action"]) != NULL)
{
	// Get post values
	$username = addslashes($_POST["username"]);
	$password = addslashes($_POST["password"]);
	$action = addslashes($_POST["action"]); 

	
	$message = "Invalid Page Request";
	
	$mysqli = new mysqli("97.74.218.45", "MiscAndrew", "Csisfun1234", "MiscAndrew");
	
	if (mysqli_connect_errno()) {
		printf("Connect failed: %s\n", mysqli_connect_error());
		exit();
	}
	
	if(strcmp($action ,"Login") == 0)
	{
	    $query = 'SELECT uid FROM user where username = "'.$username.'" and password = "'.$password.'"';
		
		$result = $mysqli->query($query);
		
		if ($result->num_rows > 0) 
		{
		   
		    // Authenticate as basic group user
		    $row = $result->fetch_assoc();
			
			$_SESSION["username"] = $username;
			$_SESSION["uid"] = $row["uid"];
			$_SESSION["password"] = $password; 
			
			$result->close();
			
			// Authenticate as individual owner. 
			$query = 'SELECT uid,ustream_embeded_code '
       		   . ' FROM individual_owner'
               . ' WHERE uid IN (SELECT uid '
                             . ' FROM user '
                             . ' WHERE username = "'.$username.'" AND password = "'.$password.'");'; 
		
			$result =$mysqli->query($query);
			
			if ($result->num_rows > 0) 
			{
				$row = $result->fetch_assoc();
				
				$_SESSION["playerCode"] = $row['ustream_embeded_code'];
				
				$_SESSION["isIndividualOwner"] = 1; 
			}
			
			$result->close();
			
			header("Location:UI/index.php");			
		}
		else
		{
			// No password match
			$message = "No matching passwords";
		}
	}
	else if(strcmp($action,"Create Account") == 0)
	{	
		// Create account and login. 
		
	    if(usernameExists($mysqli,$username) == false)
		{
			$robotRegister = $_POST['robotRegister'];
			$ustreamCode = $_POST['ustream']; 
			$robotRegister = $_POST['robotRegister']; 
			
			
			// Username does not exist, create it.
			$query = 'INSERT INTO `MiscAndrew`.`user` (`uid`, `username`, `password`) VALUES (\'\', \''.$username.'\', \''.$password.'\');';
			$mysqli->query($query);
			
			$_SESSION["username"] = $username;
			$_SESSION["password"] = $password; 
			$_SESSION["uid"] = $mysqli->insert_id;
			
			// Check if the user would like to register a robot. 
			
			if(strcmp($robotRegister,"yes") == 0)
			{
				// User would like to register a robot
				
				
				if(strlen($ustreamCode) > 50 && strripos($ustreamCode,'http://www.ustream.tv',0) != false)
				{
					// User has a valid ustream embeded code
					$query = 'INSERT INTO `MiscAndrew`.`individual_owner` (`uid`, `ustream_embeded_code`)' 
					     . 'VALUES (\''.$_SESSION["uid"].'\', \''.$ustreamCode.'\');'; 
						 
					$mysqli->query($query);
					
					// Set appropriate session variables
					$_SESSION["isIndividualOwner"] = 1; 
					$_SESSION["playerCode"] = $ustreamCode; 
					
					$mysqli->close();
					header("Location:UI/index.php");
					
				}
				else
				{
					// Invalid ustream code 
					$message = "Invalid ustream code";			
				}
			}
			else
			{
				$mysqli->close();
				header("Location:UI/index.php");	
			}
			
		}
		else
		{
			// Username exists.
			$message = "Username already exists";
		}
	}
	
	$mysqli->close();
}

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html>
<head>
<title>CS 240: Controling robots via the web| By Andrew Ribeiro & Jean Silva| Invalid Login</title>

<script type="text/javascript">

 function redirect()
 {
 	window.location="index.php";
 }
 
</script>

</head>
<body onLoad="setTimeout('redirect()', 3000)" style="background-image:url(_images/kubrickbgcolor.jpg)">

<div style="background-color:#FFFFFF; padding:1em; width:400px; text-align:center; margin:0 auto; margin-bottom:1em; font-size:36px">
Login Error
</div>

<div style="background-color:#FFFFFF; padding:1em;">
<? echo $message ?>
<br />
Redirecting you back to the login page...
</div>

</body>
</html>
