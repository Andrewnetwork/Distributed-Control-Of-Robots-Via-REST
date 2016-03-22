<?php
// REST.php
// Andrew Ribeiro 
// November 19, 2009

/****** ERROR CODES ******
 * ERROR01: could not connect to the database, database down. 
 * ERROR02: user credentials invalid.
 * ERROR03: user tried to use admin functions, but is not an admin.
 * ERROR04: unimplemented method error. 
 * ERROR05: missing username 
 * ERROR06: missing password
 *************************/
 
 /**** Commands *****
 * current_command_user
 * pop_command_list
 * submit_command
 * process_command
 * last_command_user
 * get_raw_command
 *******************/


require("../globals.php");

class REST
{
	// Data members
    private $db;
	private $isAdmin; 
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
	
	private function authenticateAsAdmin($uid)
	{
		$query = 'SELECT uid FROM admin where uid = "'.$uid.'"';
		
		$result = $this->db->query($query);
		
		if ($result->num_rows > 0) 
		{
			// User is an admin, grant administrative rights. 
			$this->isAdmin = true;
		}
		else
		{
			$this->isAdmin = false;
		}
		
	}
	
	private function authenticate($username,$password)
	{
		$query = 'SELECT uid FROM user where username = "'.$username.'" and password = "'.$password.'"';
		
		$result = $this->db->query($query);
		
		if ($result->num_rows > 0) 
		{
		    // User has an account
		    $row = $result->fetch_assoc();
			
			$this->username = $username;
			$this->uid = $row["uid"];
		
			$this->authenticateAsAdmin($this->uid);
			
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
	public function getLastRecentlyUsedEntry()
	{
		// Get's the last usage from the entry log.
		$sql = 'SELECT username '
        . ' FROM user '
        . ' WHERE `uid` IN( SELECT `userID`'
        . ' FROM last_use); LIMIT 0, 30 '; 
		
		$result = $this->db->query($sql);
		
		if ($result->num_rows > 0) 
		{
			echo XML_HEADER;
			echo "<responce>";
			echo "<username>".$row['username']."</username>";
			echo "</responce>";
		}
	}
	
	
	public function getFirstPendingOwner()
	{
		// Get's the job that is currently being worked on. 
		$sql = 'SELECT * FROM current_command_user'; 
		
		$result = $this->db->query($sql);
		
		if ($result->num_rows > 0) 
		{
			$row = $result->fetch_assoc();
			
			echo XML_HEADER;
			echo "<responce>";
			echo "<username>".$row['username']."</username>";
			echo "</responce>";
		}
	}
	
	private function updateUseLog($commandSubmitted)
	{
		// Updates the usage log
		$sql = 'INSERT INTO `'.DATABASE.'`.`use` (`userID`, `time`, `commandID`)'
		      .'VALUES (\''.$this->uid.'\', CURRENT_TIMESTAMP, \''.$commandSubmitted.'\');'; 
			  
		$this->db->query($sql);
	}
	
	public function submitJob($commandText)
	{
		// Submits code to be processed
		// Returns the Job ID
		 $sql = 'INSERT INTO `'.DATABASE.'`.`command` (`commandID`, `commandText`) VALUES (NULL, \''.$commandText.'\')';
		 
		 $this->db->query($sql);
		 
		 $this->commandID = $this->db->insert_id;
		 
		 $this->updateUseLog($this->commandID);
	}
	
	// Run function 
	public function run($token,$arg1 = NULL)
	{
		if(strcmp($token,"current_command_user") == 0)
		{
			// Return the current user that is runing a program on the robot. 
			$this->getFirstPendingOwner();
		}
		else if(strcmp($token,"pop_command_list") == 0)
		{
			// Remove pending command
			$this->removePendingCommand();
		}
		else if(strcmp($token,"submit_command") == 0)
		{
			// Submits a command.
			$this->submitJob($arg1);
		}
		else if(strcmp($token,"process_command") == 0)
		{
			// Get the command text..
			$this->processPendingCommand();
		}
		else if(strcmp($token,"last_command_user") == 0)
		{
			// Get the name of the user that last finished a command. 
			$this->getLastRecentlyUsedEntry();
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
	
	// Admin functions 
	public function removePendingCommand()
	{
		// Removes jobs completed from the job queue 
		if($this->isAdmin)
		{
			// Write in the use log that the command was completed. 
			
			$sql = 'UPDATE `'.DATABASE.'`.`use` '
				. ' SET `completed` = 1'
				. ' WHERE `commandID` = (SELECT MAX(`commandID`)) and'
				. ' userID = '.$this->uid;
				 
			$this->db->query($sql);
			
			// Delete the command from the command queue 
			$sql = 'DELETE FROM command'
        		. ' WHERE commandID IN (SELECT command '
      		  	. ' FROM recent_command);'; 
				
			$this->db->query($sql);
		}
		else
		{
			echo "ERROR03";
		}
	}
	
	public function processPendingCommand()
	{
		if($this->isAdmin)
		{
			// Get the command code.
			$sql = 'SELECT `commandText` from recent_command LIMIT 1'; 
			
			$result = $this->db->query($sql);
			
			if ($result->num_rows > 0) 
			{
				$row = $result->fetch_assoc();
				
				echo XML_HEADER;
				echo "<responce>";
				echo "<commandText>".$row['commandText']."</commandText>";
				echo "</responce>";
			}
		}
		else
		{
			echo "ERROR03";
		}	
	}
	
	
	public function getRawCommand()
	{
		if($this->isAdmin)
		{
			// Get the command code.
			$sql = 'SELECT `commandText` from recent_command LIMIT 1'; 
			
			$result = $this->db->query($sql);
			
			if ($result->num_rows > 0) 
			{
				$row = $result->fetch_assoc();
				echo $row['commandText'];
			}
		}
		else
		{
			echo "ERROR03";
		}	
	}	
}
?>