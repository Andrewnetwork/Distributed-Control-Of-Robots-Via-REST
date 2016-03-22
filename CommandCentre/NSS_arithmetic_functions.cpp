/** NSS_arithmetic_functions.cpp
 * Andrew Ribeiro
 * November 24, 2009
**/

#include "NSS.h"
#include "constants.h"

#include <map>
#include <string>
#include <vector>
#include <iostream>
using namespace std; 

namespace comandrewribeiroremoterobot
{
	//**************** START FUNCTION PROTOTYPES *************
	bool containsCharicters(string str);
	string removeNonNumericCharicters(string number);
	void removeNewLines(string & str);
	void removeSpaces(string & str);
	void removeMultiLineComments(string & str);
	char * toCString(string str);
	string lowerCaseString(string str);
	//**************** END FUNCTION PROTOTYPES ***************

	int NSS::solveSingleExpression(string & line,string arithOperator)
	{
		try
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
		catch(...)
		{
			cout<<"  SYSTEM: error while performing arithmetic operations"<<endl;
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




	void NSS::resolveBinaryVariableMutations(string & line)
	{
		// Ex: variable += 3 || ++variable || ~variable
		try
		{

			// Check for mutable operands. 
			if(line.find("+=") != string::npos)
			{

			}
			else if(line.find("-=") != string::npos)
			{

			}
			else if(line.find("*=") != string::npos)
			{

			}
			else if(line.find("/=") != string::npos)
			{

			}
			else if(line.find("%=") != string::npos)
			{

			}
			else if(line.find("++") != string::npos)
			{

			}
			else if(line.find("--") != string::npos)
			{

			}
			else if(line.find("~") != string::npos)
			{

			}	
			else
			{
				// It is not being mutated... leave it to be replaced with its value. 
				return;
			}
		}
		catch(...)
		{
			cout<<"  SYSTEM: Error changing the value of a variable."<<endl;
		}

	}


	void NSS::resolveUnaryVariableMutations(string & line)
	{
		// Resolve all unary mutations. 

		bool noUnaryMutation = false;

		// While there is not a lack of unary mutation operators. 
		while(!noUnaryMutation)
		{
			map<string,int>::reverse_iterator rit;

			// No unary mutation found yet. 
			noUnaryMutation = true; 

			for ( rit = this->variables.rbegin() ; rit != this->variables.rend(); rit++ )
			{
				if(line.find(rit->first) != string::npos)
				{
					// Variable is in this line. 
					// Check if it is the one near the unary operator 
					// ++variable 
					// 1234
					// varible is found at 3, ++ is found at 1, 3-2 ==1
					if(line.find("++") != string::npos && line.find("++") == (line.find(rit->first)-2))
					{
						// Found the variable that is being incremented. 
						// Increment the variable.
						++rit->second;

						// Remove the operator.
						line.erase(line.find("++"),2);

						// A unary operation was found... continue to look for more. 
						noUnaryMutation = false;
						break;
					}
					else if(line.find("--") != string::npos  && line.find("--") == (line.find(rit->first)-2))
					{
						--rit->second;
						line.erase(line.find("--"),2);

						noUnaryMutation = false;
						break;
					}
					else if(line.find("~") != string::npos  && line.find("~") == (line.find(rit->first)-1))
					{
						// SET TO ZERO OPERATOR 
						rit->second = 0;
						line.erase(line.find("~"),1);

						noUnaryMutation = false;
						break;
					}	
				}
			}
		}
	}


	void NSS::resolveVariableCalls(string & line)
	{
		// Function replaces variables with their respective values. 
		// Precondition: Assumes no spaces.

		map<string,int>::reverse_iterator rit;

		for ( rit = this->variables.rbegin() ; rit != this->variables.rend(); rit++ )
		{
			// Replace all uccurences in the line. 
			// Start from right to left 
			while(line.find(rit->first) != string::npos)
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

	void NSS::arithmeticAndVariableParse(string & line)
	{
		try
		{
			// 1.) Resolve unary variable mutations 
			this->resolveUnaryVariableMutations( line );

			// 2.) Change the variables called to meaningfull values.
			this->resolveVariableCalls( line );

			// 3.) Solve arithmetic expressions.
			this->resolveArithmeticExpressions( line );

			// 4.) Create varibles. 
			this->createVariables( line );
		}
		catch(...)
		{
			cout<<"  SYSTEM: error while performing arithmetic or variable operations"<<endl;
		}
	}

}