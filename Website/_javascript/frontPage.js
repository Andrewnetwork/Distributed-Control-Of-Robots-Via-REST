// frontPage.js
// Andrew Ribeiro
// December 6, 2009


function registerRobot(textFeildID)
{
	document.getElementById(textFeildID).disabled = false;
}

function dontRegisterRobot(textFeildID)
{
	document.getElementById(textFeildID).disabled = true;
}

function showHelp(layer)
{
	document.getElementById(layer).style.visibility = "visible"; 
}

function hideThis(divID)
{
	document.getElementById(divID).style.visibility = "hidden";
}