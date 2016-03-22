/** NSS.cpp
 * Andrew Ribeiro
 * November 24, 2009
**/

#include "NSS.h"

#include <map>
#include <string>
#include <vector>
#include <iostream>
using namespace std; 


const int MAX_VARIABLE_LENGTH = 30;

//**************** START FUNCTION PROTOTYPES *************
bool containsCharicters(string str);
string removeNonNumericCharicters(string number);
void removeNewLines(string & str);
void removeSpaces(string & str);
void removeMultiLineComments(string & str);
char * toCString(string str);
string lowerCaseString(string str);
//**************** END FUNCTION PROTOTYPES ***************


//****************** START UTILITY FUNCTIONS *************
void NSS::variableDump()
{
	map<string,int>::reverse_iterator rit;

	cout<<endl<<"*** VARIABLE DUMP ***"<<endl;
	cout<<"* Nvars: "<<this->variables.size()<<endl<<endl;

	for ( rit = this->variables.rbegin() ; rit != this->variables.rend(); rit++ )
	{
		cout << rit->first << " => " << rit->second << endl;
	}
}
//****************** END UTILITY FUNCTIONS *************


//*********************** START PARSING FUNCTIONS *****************
bool NSS::solveSingleExpression(string & line,string arithOperator)
{
	// If the operator exists. 
	if(line.find(arithOperator) != -1)
	{
		unsigned int leftStart,rightEnd,leftValue,rightValue,operatorLocation = line.find(arithOperator); 

		// Left of operator
		for(leftStart =operatorLocation-1; leftStart > 0 && (isalnum(line[leftStart]) || isalpha(line[leftStart])); leftStart--);

		// Right of operator 
		for(rightEnd = operatorLocation+1; rightEnd < line.size() && (isalnum(line[rightEnd+1]) || isalpha(line[rightEnd])) ; rightEnd++);

		// Get the two numbers.
		string leftSubstring = line.substr(leftStart+1,(operatorLocation) - (leftStart + 1) );
		string rightSubstring = line.substr(operatorLocation+1, (operatorLocation) - (rightEnd));

		// Perform computation 

		char buff[MAX_VARIABLE_LENGTH];

		
		if(arithOperator.compare("+") == 0)
		{
			itoa( atoi(leftSubstring.c_str()) + atoi(rightSubstring.c_str()),buff,10 );
		}
		else if(arithOperator.compare("*") == 0)
		{
			itoa((atoi(leftSubstring.c_str()) * atoi(rightSubstring.c_str())),buff,10 );
		}
		else if(arithOperator.compare("-") == 0)
		{
			itoa( atoi(leftSubstring.c_str()) - atoi(rightSubstring.c_str()),buff,10 );
		}
		else if(arithOperator.compare("/") == 0)
		{
			itoa( atoi(leftSubstring.c_str()) / atoi(rightSubstring.c_str()),buff,10 );
		}
		else if(arithOperator.compare("%") == 0)
		{
			itoa( atoi(leftSubstring.c_str()) % atoi(rightSubstring.c_str()),buff,10 );
		}
		else
		{
			return false;
		}

		string result(buff);

		// Put the sum back in line. 
		line = (line.substr(0,leftStart+1) + result + line.substr(rightEnd+1,(line.size()-1) - rightEnd ));

		return true;
	}
	else
	{
		// Invalid call.
		return false;
	}
}


void NSS::resolveArithmeticExpressions(string & line)
{
	// Assumes no spaces. 
	// If an binary arithmetic charicter is found. 
	try
	{
		bool condition = true; 

		while(condition)
		{
			if(line.find('+') != string::npos)
			{
				// If it cannot be solved. 
				if(!solveSingleExpression( line , "+"))
				{
					condition = false; 
				}
			}
			else if(line.find('-') != string::npos)
			{
				if(!solveSingleExpression( line , "-"))
				{
					condition = false; 
				}
			}
			else if(line.find('*') != string::npos)
			{
				if(!solveSingleExpression( line , "*"))
				{
					condition = false; 
				}
			}
			else if(line.find('%') != string::npos)
			{
				if(!solveSingleExpression( line , "%"))
				{
					condition = false; 
				}
			}
			else if(line.find('/') != string::npos)
			{
				if(!solveSingleExpression( line , "/"))
				{
					condition = false; 
				}
			}
			else if(line.find('++') != string::npos)
			{

				//resolveArithmeticExpressions(line,sys);
			}
			else if(line.find('--') != string::npos)
			{

				//resolveArithmeticExpressions(line,sys);
			}
			else if(line.find('#') != string::npos)
			{

				//resolveArithmeticExpressions(line,sys);
			}
			else
			{
				// No more arithmetic expressions.
				condition = false;
			}
		}
	}
	catch(...)
	{
		cout<<"  SYSTEM: Error performing arithmetic expression"; 
	}
}


void NSS::createVariables(string line)
{
	try
	{
		// Handling variables.
		if(line.find("var") != -1 && line.find("var") == 0)
		{
			int value;
			string key;

			// Assignment and creation or just varible creation 
			if(line.find('=') != -1)
			{
				//If it is an assignment
				key = line.substr(line.find("var")+3,line.find('=')-3);
				value = atoi(removeNonNumericCharicters(line.substr(line.find('=')+1,line.size())).c_str());
				
			}
			else
			{
				// Just a creation
				key = line.substr(line.find("var")+3,line.size());
				value = 0; 
			}

			this->variables.insert(pair<string,int>(key,value));
		}
	}
	catch(...)
	{
		cout<<"  SYSTEM: Error handling variables"; 
	}
}


void NSS::resolveVariableCalls(string & line)
{
	// Function replaces variables with their respective values. 
	// Precondition: Assumes no spaces.

	map<string,int>::reverse_iterator rit;

	for ( rit = this->variables.rbegin() ; rit != this->variables.rend(); rit++ )
	{
		if(line.find(rit->first) != -1)
		{
			// Found the varible, replace it with its value. 
			string left = line.substr(0,line.find(rit->first));
			string right = line.substr(line.find(rit->first)+rit->first.size(),line.size());
			
			char buffer[MAX_VARIABLE_LENGTH];
			itoa(rit->second,buffer,10);

			string value(buffer);

			line = left + value + right; 
		}
	}
}

// Assumes no spaces or newlines.

void NSS::arithmeticAndVariableParse(string & line)
{
	// 1.) Change the variables called to meaningfull values.
	this->resolveVariableCalls( line );

	// 2.) Solve arithmetic expressions.
	this->resolveArithmeticExpressions( line );

	// 3.) Create varibles. 
	this->createVariables( line );
}



void NSS::parseCommandLine(string line)
{
	// 1.) Handle arithmetic and variable parsing. 
	this->arithmeticAndVariableParse( line );

	// 2.) Handle function parsing. 

}

void NSS::beginParsing()
{
	// Tokenizing 
	char * nCommandString = toCString( this->script );

	char * pch;

	// Get the command lines. 
	pch = strtok (nCommandString,";");

	while (pch != NULL)
	{
		this->commandLines.push_back(pch);
		pch = strtok (NULL, ";");
	}

	// Parse each command line.
	for(unsigned int i = 0; i < commandLines.size()-1; i++)
	{
		parseCommandLine(this->commandLines[i]);
	}
}
//*********************** END PARSING FUNCTIONS *****************

//*********************** START CONSTRUCTOR ************
NSS::NSS(string script)
{
	removeSpaces(script);
	this->script = script; 
}

//*********************** END CONSTRUCTOR **************
