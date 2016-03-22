/** variables.cpp
 * Andrew Ribeiro 
 * November 24, 2009
 * Description: this program demonstraits how we create and interact with varibles. 
**/

/*** NOTES
 * > If a varible name is used in another varible 
**/
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <ctype.h>
#include "NSS.h"
using namespace std; 

const int MAX_VARIABLE_LENGTH = 30;

/*
		bool rChars = containsCharicters(rightSubstring), lChars = containsCharicters(leftSubstring);

			// If the left and right substring contain charicters, they are variables. 
			if(rChars && lChars)
			{
				// Both are variables

			}
			else if(rChars)
			{
				// Only the right is a variable


			}
			else if(lChars)
			{
				// Only the left is a varible 

			}
			else
			{
			*/


void main()
{
	string commandString;
	
	commandString += "var andrew = 433;";
	commandString += "var agamenon = andrew;";
	commandString += "var hellow = 20;";
	commandString += "var b = (hellow * 2 * 2 * 2);";
	commandString += "var c = (b + 50);";

	NSS parsingSystem(commandString);

	parsingSystem.beginParsing();

	parsingSystem.variableDump();
}

