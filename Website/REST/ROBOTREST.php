<?php
// ROBOTREST.php
// Andrew Ribeiro
// November 19, 2009
// Implements the REST CLASS

/**** Commands *****
 * current_command_user
 * pop_command_list
 * submit_command
 * process_command
 * last_command_user
 * get_raw_command
 *******************/
require("REST.php");

// Get prarameters 
$username = NULL;
$password = NULL;
$function = NULL;
$arg1 = NULL;

if(isset($_POST["username"]) == true)
{
	// POST
	$username = $_POST["username"];
	$password = $_POST["password"];
	$function = $_POST["fn"];
	$arg1 = $_POST["arg"];
}
else
{
	// GET
	$username = $_GET["username"];
	$password = $_GET["password"];
	$function = $_GET["fn"];
	$arg1 = $_GET["arg"];
}

if(strlen($username) == 0)
{
	echo "ERROR05";
	exit();
}

if(strlen($password) == 0)
{
	echo "ERROR06";
	exit();
}

// Connect to the REST interface. 
$api = new REST($username,$password);

// Carry out operations
if(strlen($function) != 0)
{
	if(strlen($arg1) == 0)
	{
		// api call without args.
		$api->run($function);
	}
	else
	{
		// api call with args.
		$api->run($function,addslashes($arg1));
	}
}


?>