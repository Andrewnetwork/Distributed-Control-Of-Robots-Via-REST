/** NSS.h
 * Andrew Ribeiro
 * November 24, 2009
**/

#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

#pragma once

class NSS 
{
private:
	//*** START DATA MEMBERS ****
	map<string,int> variables;
	map<string,int> constants; 
	map<string,int> trigers; 
	string script;
	vector<string> commandLines; 
	//*** END DATA MEMBERS ****

public:

	//****** START ACESSOR AND MUTATOR FUNCTIONS ********
	map<string,int> & getVariables(){return this->variables;}
	map<string,int> & getConstants(){return this->constants;}
	//****** END ACESSOR AND MUTATOR FUNCTIONS **********

	//****** START UTILITY FUNCTIONS ********
	void variableDump();
	//****** END UTILITY FUNCTIONS ********

	//****** START PARSING FUNCTIONS ******
	bool solveSingleExpression(string & line,string arithOperator);
	void resolveArithmeticExpressions(string & line);
	void createVariables(string line);
	void resolveVariableCalls(string & line);
	void parseCommandLine(string line);
	void arithmeticAndVariableParse(string & line);
	void beginParsing();
	//****** END PARSING FUNCTIONS ********

	//****** START CONSTRUCTOR ************
	NSS(string script);
	//****** END CONSTRUCTOR **************



};
