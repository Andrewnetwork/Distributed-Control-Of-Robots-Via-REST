/** NSS.h
 * Andrew Ribeiro
 * November 24, 2009
**/

#include <map>
#include <string>
#include <vector>
#include <windows.h>
#include <iostream>
#include "nxt_remote.h"

using namespace std;

#pragma once

namespace comandrewribeiroremoterobot
{
	class NSS 
	{
	private:
		//*** START DATA MEMBERS ****
		map<string,int> variables;
		map<string,int> constants; 
		map<string,int> trigers; 
		string script;
		vector<string> commandLines; 
		nxt_remote * remoteControl; 
		//*** END DATA MEMBERS ****

	public:

		//****** START ACESSOR AND MUTATOR FUNCTIONS ********
		map<string,int> & getVariables(){return this->variables;}
		map<string,int> & getConstants(){return this->constants;}
		nxt_remote * getRemoteControl(){return this->remoteControl;}
		//****** END ACESSOR AND MUTATOR FUNCTIONS **********

		//****** START UTILITY FUNCTIONS ********
		void variableDump();
		//****** END UTILITY FUNCTIONS ********


		//****** START GENERAL PARSING FUNCTIONS *******
		void beginParsing();
		void arithmeticAndVariableParse(string & line);
		void parseCommandLine(string line);
		//****** END GENERAL PARSING FUNCTIONS *********

		//****** START ARITHMETIC PARSING FUNCTIONS ******
		int solveSingleExpression(string & line,string arithOperator);
		void resolveArithmeticExpressions(string & line);
		//****** END ARITHMETIC PARSING FUNCTIONS ********

		//****** START VARIABLE PARSING FUNCTIONS ******
		void createVariables(string line);
		void resolveVariableCalls(string & line);

		void resolveBinaryVariableMutations(string & line);
		void resolveUnaryVariableMutations(string & line);
		//****** END VARIABLE PARSING FUNCTIONS ******

		//****** START SYSTEM CALL PARSING FUNCTIONS *****

		void executeMoveFoward(string args);
		void executeMoveBack(string args);
		void executePointTurnRight(string args);
		void executePointTurnLeft(string args);
		void executeSwingTurnLeft(string args);
		void executeSwingTurnRight(string args);
		void executeSleep(string args);

		void processCommand(string command,string args);
		void systemCallParsing(string & line);
		//****** END SYSTEM CALL PARSING FUNCTIONS *******

		//****** START CONSTRUCTOR ************
		NSS(string script,nxt_remote * remote);
		//****** END CONSTRUCTOR **************

	};
}
