/** NSS.cpp
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

	//**************** START GENERAL PARSING FUNCTIONS *************
	void NSS::parseCommandLine(string line)
	{
		// 1.) Handle arithmetic and variable parsing. 
		this->arithmeticAndVariableParse( line );

		// 2.) Handle system call parsing. 
		this->systemCallParsing( line );

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
		
		this->getRemoteControl()->turnOffMotors();
	}


	//**************** END GENERAL PARSING FUNCTIONS *************
	
	//*********************** START CONSTRUCTOR ************
	NSS::NSS(string script, nxt_remote * remote)
	{
		this->remoteControl = remote; 

		script = lowerCaseString( script );

		removeMultiLineComments( script );

		removeSpaces( script );

		removeNewLines( script );

		removeSpaces( script );
		
		this->script = script; 
	}

	//*********************** END CONSTRUCTOR **************
}