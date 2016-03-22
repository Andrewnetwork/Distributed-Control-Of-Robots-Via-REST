<?php
// RemoteREST.php
// Andrew Ribeiro 
// December 5, 2009

/****** ERROR CODES ******
 * ERROR01: could not connect to the database, database down. 
 * ERROR02: user credentials invalid or user is not an individual owner. 
 * ERROR03: user tried to use admin functions, but is not an admin.
 * ERROR04: unimplemented method error. 
 * ERROR05: missing username 
 * ERROR06: missing password
 *************************/
 
 /**** Commands *****
 * pop_command_list
 * submit_command
 * get_raw_command
 *******************/

require("../../globals.php");

class RemoteREST
{
	// Data members
    private $db;
	private $username;
	private $uid;
	private $commandID; 
	
	function __construct($username,$password) 
	{
		// Connect to server
	    $this->db = new mysqli(SERVER_ADDR, USER_NAME,PASSWORD,DATABASE);

		if (mysqli_connect_errno()) 
		{
			echo "ERROR01";
			exit();
		}
		
		// Authenticate
		$this->authenticate($username,$password);
	
    }
	private function authenticate($username,$password)
	{
		// Make sure they are a user and an individual owner. 
		$query = 'SELECT uid '
       		   . ' FROM individual_owner'
               . ' WHERE uid IN (SELECT uid '
                             . ' FROM user '
                             . ' WHERE username = "'.$username.'" AND password = "'.$password.'");'; 
		
		$result = $this->db->query($query);
		
		if ($result->num_rows > 0) 
		{
		    // User has an account
		    $row = $result->fetch_assoc();
			
			$this->username = $username;
			$this->uid = $row["uid"];
		
			
			$result->close();
					
		}
		else
		{
			// No password match
			echo "ERROR02";
			$result->close();
			exit();
		}
	}
	
	// General user functions 
	public function submitJob($commandText)
	{
		// Submits code to be processed
		// Returns the Job ID
		 $sql = 'INSERT INTO `MiscAndrew`.`realtime_remote_commands` (`id`, `uid`, `commandID`) VALUES (NULL, \''.$this->uid.'\', \''.$commandText.'\');'; 
		 
		 $this->db->query($sql);
	}
	
	// Run function 
	public function run($token,$arg1 = NULL)
	{
		if(strcmp($token,"pop_command_list") == 0)
		{
			// Remove pending command
			$this->removePendingCommand();
		}
		else if(strcmp($token,"submit_command") == 0)
		{
			// Submits a command.
			$this->submitJob($arg1);
		}
		else if(strcmp($token,"get_raw_command") == 0)
		{
			$this->getRawCommand();
		}
		else
		{
			echo "ERROR04";
		}
	}
	public function removePendingCommand()
	{
		// Delete the command from the command queue 
		$sql = 'SELECT `id`'
        . ' FROM realtime_remote_commands'
        . ' WHERE uid = '.$this->uid
        . ' LIMIT 0,1;'; 
			
		$result = $this->db->query($sql);
		
		if ($result->num_rows > 0) 
		{
			$row = $result->fetch_assoc();
			
			// Delete the commands
			$sql = 'DELETE FROM realtime_remote_commands'
        		 . ' WHERE `id` = '.$row['id']; 
	 
			$this->db->query($sql);
		}
		else
		{
			// No command to remove
		}
	}
	
	public function getRawCommand()
	{
	
		// Get the command code.
		$sql = 'SELECT `commandID`'
			 . ' FROM realtime_remote_commands'
			 . ' WHERE `uid` = '.$this->uid
			 . ' LIMIT 0,1'; 
		
	
		$result = $this->db->query($sql);
		
		if ($result->num_rows > 0) 
		{
			$row = $result->fetch_assoc();
			echo $row['commandID'];
		}
		
	}	
}
?>