<div style="background-color:#FFFFFF">
<center>
<h2>CS240 Project: Remote Command Execution on NXT Robots</h2>
<h3>BY: Andrew Ribeiro and Jean Silva</h3>
</center>
<center>
<a href="<?php echo DROOT; ?>/index.php">HOME</a> | <a href="<?php echo DROOT; ?>NSSTUTORIAL/index.html">NSS TUTORIAL</a> | <a href="<?php echo DROOT; ?>/Videos">VIDEOS</a> | <a href="<?php echo DROOT; ?>/Downloads">DOWNLOADS</a> 

<?php

if(isset($_SESSION["isIndividualOwner"]) == true)
{
	echo "| <a href = '".DROOT."/RealtimeRemote/ui.php'>REMOTE CONTROL</a>";
}

if(isset($_SESSION["username"]) == true)
{
	echo "| <a href = '".DROOT."/UI'>CONTROL CENTRE</a>";
	echo "| <a href = '".DROOT."logout.php'>LOGOUT</a>";
}



?>

</center>
</div>
<hr/>