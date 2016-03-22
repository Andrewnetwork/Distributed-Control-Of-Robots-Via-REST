#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>

#include "nxt_remote.h"

using namespace std;


namespace comandrewribeiroremoterobot
{
	//****** UTILITY FUNCTIONS *******
	char * toCString(string str)
	{
		char *ns = new char[str.size()];
		
		for(int i = 0; i < str.size(); i++)
		{
			ns[i] = str[i];
			
		}

		return ns;
	}

	string lowerCaseString(string str)
	{
		string outStr;

		for(int i = 0; i < str.size(); i++)
		{
			outStr += (char)tolower(str[i]);
		}

		return outStr; 
	}

	void removeNewlineChar(string &line)
	{
	
		if(line[0] == '\n')
		{
			line = line.substr(1,line.size()-1);
		}
		
	}

	//***** END UTILITY FUNCTIONS *******

	//****************** START COMMANDS AND ARGUMENTS ************************
	void executeMoveFoward(string args,nxt_remote * nxtr)
	{
		// Parse the arguments. 
		string units = args.substr(0,args.find(","));
		string power = args.substr(args.find(",")+1,args.size()); 

		// Finding out what unit the argument is. 
		if(units.find("in") != -1)
		{
			// Remove the units specifier. 
			units.replace(units.find("in"),2,"");

			int iUnits = atoi(units.c_str());
			int iPower = atoi(power.c_str());


			cout<<endl
				<<"  ****************** COMMAND ****************"<<endl
				<<"  ROBOT: move foward "<<iUnits<<" inches"<<endl
				<<"  ROBOT: with a power of "<<iPower<<endl
				<<"  *******************************************"<<endl;
		}
		else if(units.find("ms") != -1)
		{
			units.replace(units.find("ms"),2,"");

			int iUnits = atoi(units.c_str());
			int iPower = atoi(power.c_str());

		

			cout<<endl
				<<"  ****************** COMMAND ****************"<<endl
				<<"   ROBOT: move backward for "<<iUnits<<" miliseconds"<<endl
				<<"   ROBOT: with a power of "<<iPower<<endl
				<<"  *******************************************"<<endl;
		}

	}

	void executeMoveBack(string args,nxt_remote * nxtr)
	{

		// Parse the arguments. 
		string units = args.substr(0,args.find(","));
		string power = args.substr(args.find(",")+1,args.size()); 

		// Finding out what unit the argument is. 
		if(units.find("in") != -1)
		{
			// Remove the units specifier. 
			units.replace(units.find("in"),2,"");

			int iUnits = atoi(units.c_str());
			int iPower = atoi(power.c_str());

			cout<<endl
				<<"  ****************** COMMAND ****************"<<endl
				<<"  ROBOT: move backward "<<iUnits<<" inches"<<endl
				<<"  ROBOT: with a power of "<<iPower<<endl
				<<"  *******************************************"<<endl;
		}
		else if(units.find("ms") != -1)
		{
			units.replace(units.find("ms"),2,"");

			int iUnits = atoi(units.c_str());
			int iPower = atoi(power.c_str());

			cout<<endl
				<<"  ****************** COMMAND ****************"<<endl
				<<"  ROBOT: move backward for "<<iUnits<<" miliseconds"<<endl
				<<"  ROBOT: with a power of "<<iPower<<endl
				<<"  *******************************************"<<endl;
		}
	}
	//****************** END COMMANDS AND ARGUMENTS ************************



	// Process individual commands
	void processCommand(string command,string args,nxt_remote * nxtr)
	{
		// Execute the commands.

		if(lowerCaseString(command).compare("movefoward") == 0)
		{
			executeMoveFoward(args);
		}
		else if(lowerCaseString(command).compare("moveback") == 0)
		{
			executeMoveBack(args);
		}
		else
		{
			cout<<"  SYSTEM: user tried to execute an invalid command."<<endl;
			cout<<"  SYSTEM: "<<command<<endl;
		}
	}

	
	// Convert script into command.
	void parseCommandLine(string line,nxt_remote * nxtr)
	{

		removeNewlineChar(line);

		// The actual command.
		string command = line.substr(0,line.find("(")); 
		
		// Arguments of the function.. dont include the parenthisis
		string args = line.substr(line.find("(")+1,(line.find(")") - line.find("("))-1 );

		// Process the individual commands.
		processCommand(command,args);
	}

	
}