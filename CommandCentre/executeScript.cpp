/** executeScript.cpp
 * Andrew Ribeiro 
 * November 21, 2009
**/

#include <string>
#include <iostream>
#include <string>

using std::endl;
using std::cout;

#include "NSS.h"
#include "nxt_remote.h"


namespace comandrewribeiroremoterobot
{
	void executeScript(string script, nxt_remote * nxtr)
	{
		
		try
		{
			cout<<endl<<"  SYSTEM: Executing client script"<<endl;
		
			NSS interpreter(script,nxtr);

			interpreter.beginParsing();
		}
		catch(...)
		{
			cout<<"  SYSTEM: problem while parsing the script."<<endl;
		}

	}

}