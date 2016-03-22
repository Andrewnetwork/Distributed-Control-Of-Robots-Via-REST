// functions.js
// Andrew Ribeiro 
// November 18, 2009




function clearText(textElementId)
{
	document.getElementById(textElementId).value = "";
}
function submitCode(formLayerID)
{
	$("codeForm").fadeOut("slow");
	
	/*
	codeFormHTML = document.getElementById(formLayerID).innerHTML;
	document.getElementById(formLayerID).innerHTML = "";
	
	document.getElementById(formLayerID).innerHTML = '<div style="text-align:center; margin-top:20%"><img src="_images/LoadingGif.gif" alt="Loading Code " /><div>';*/
}