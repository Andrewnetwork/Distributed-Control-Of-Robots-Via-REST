/** utilityFunctions.cpp
 * Andrew Ribeiro 
 * November 24, 2009
**/

#include <string>
#include<iostream>
using namespace std; 



bool containsCharicters(string str)
{
	for(int i = 0; i < str.size(); i++)
	{
		if(isalpha(str[i]))
		{
			return true;
		}
	}
	return false;
}

string removeNonNumericCharicters(string number)
{
	for(int i = 0; i < number.size(); i++)
	{
		if(!isalnum(number[i]))
		{
			number.erase(i,1);
		}
	}
	return number;
}

void removeNewLines(string & str)
{
	for(int i = 0; i < str.size(); i++)
	{
		if(str[i] == '\n')
		{
			str.replace(i,1,"");
		}
	}
}

void removeSpaces(string & str)
{ 
	for(int i = 0; i < str.size(); i++)
	{
		if(str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r')
		{
			str.replace(i,1,"");
		}
	}

	// Solves the anomoly 
	if(str.find(' ') != -1)
	{
		removeSpaces(str);
	}
	else
	{
		return;
	}
}

void removeMultiLineComments(string & str)
{
	int floc = str.find("/*"); 
	if(floc == -1)
	{
		// No comments.
		return;
	}
	else
	{
		int sloc = str.find("*/");

		if(sloc != -1)
		{
			str.erase(floc,(sloc - floc+2));
		}
		else
		{
			// PARSE ERROR: missing closing comment tag ('*/')
			return;
		}

		// Keep looking for more comments.
		removeMultiLineComments(str);
	}
}



char * toCString(string str)
{
	char *ns = new char[str.size()];
	
	for(unsigned int i = 0; i < str.size(); i++)
	{
		ns[i] = str[i];
		
	}

	return ns;
}

string lowerCaseString(string str)
{
	string outStr;

	for(unsigned int i = 0; i < str.size(); i++)
	{
		outStr += (char)tolower(str[i]);
	}

	return outStr; 
}
