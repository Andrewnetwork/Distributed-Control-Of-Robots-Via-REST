#include <string>
#include <iostream>
#include <map>
using namespace std;


// To be used before remove newlines or remove spaces. 
void removeSingleLineComments(string & str)
{
	int floc = str.find("//");

	if(floc == -1)
	{
		// No comments.
		return;
	}
	else
	{
		// Comments
	    int sloc = str.find('\n');
		str.erase(floc,(sloc - floc));
	}

	removeSingleLineComments(str);

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

void countSpaces(string str)
{
	int count = 0;
	for(int i = 0; i < str.size(); i++)
	{
		if(str[i] == ' ')
		{
			count++;
		}
	}
	cout<<endl<<count<<" space charicters!"<<endl;
}


void countNewLines(string str)
{
	int count = 0;
	for(int i = 0; i < str.size(); i++)
	{
		if(str[i] == '\n')
		{
			count++;
		}
	}
	cout<<endl<<count<<" newline charicters!"<<endl;
}

// String should be lower case.
// No spaces assumed. 
// Newlines assumed. 

void main()
{
	string commands;

	map<string,int> variables;
	//variables.insert(pair<string,int>
	
	commands+="/* This project is cool \n";
	commands+="and is fun */";
	commands+="moveFoward(4in,4)";
	commands+="moveFoward(4in,4)";
	commands+="in a = 40;       ";
	commands+="in b = a + 2;    ";


	removeMultiLineComments(commands);
	removeNewLines(commands);
	removeSpaces(commands);


	cout<<commands<<endl;


}