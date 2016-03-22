/** CommandParsing.cpp
 * Andrew Ribeiro & Jean Silva
 * November 24, 2009
**/
/*
#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <windows.h>

#include "nxt_remote.h"

using namespace std;


namespace comandrewribeiroremoterobot
{
	//****** UTILITY FUNCTIONS *******
	string lowerCaseString(string str);
	char * toCString(string str);
	//***** END UTILITY FUNCTIONS *******

	//****************** START COMMANDS AND ARGUMENTS ************************
	// NOTE: change around to remove repeating functionality (function pointers)
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

		
			nxtr->moveFwd(iUnits,iPower);

			cout<<endl
				<<"  ****************** COMMAND ****************"<<endl
				<<"   ROBOT: move foward for "<<iUnits<<" miliseconds"<<endl
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

			nxtr->moveBack(iUnits,iPower);

			cout<<endl
				<<"  ****************** COMMAND ****************"<<endl
				<<"  ROBOT: move backward for "<<iUnits<<" miliseconds"<<endl
				<<"  ROBOT: with a power of "<<iPower<<endl
				<<"  *******************************************"<<endl;
		}
	}

	void executePointTurnRight(string args,nxt_remote * nxtr)
	{
		// Parse the arguments. 
		string units = args;
		string power = "";

	
		for(unsigned int i = 0; i < args.size(); i++)
		{
			if(args[i] == ',')
			{
				power = args.substr(args.find(",")+1,args.size()); 
			}
		}

		// Finding out what unit the argument is. 
		if(units.find("deg") != -1)
		{
			// Remove the units specifier. 
			units.replace(units.find("deg"),2,"");

			int iUnits = atoi(units.c_str());
			int iPower;


			if(power.size() == NULL)
			{
				iPower = 50;
				nxtr->pointTurnLeft(iUnits,50);
			}
			else
			{
				iPower = atoi(power.c_str());
				nxtr->pointTurnLeft(iUnits,iPower);
			}

			cout<<endl
				<<"  ****************** COMMAND ****************"<<endl
				<<"  ROBOT: point right left "<<iUnits<<" degrees"<<endl
				<<"  ROBOT: with a power of "<<iPower<<endl
				<<"  *******************************************"<<endl;
		}
		else if(units.find("ms") != -1)
		{
			units.replace(units.find("ms"),2,"");

			int iUnits = atoi(units.c_str());
			int iPower;

			if(power.size() == NULL)
			{
				iPower = 50;
				nxtr->pointTurnRight(iUnits,50);
			}
			else
			{
				iPower = atoi(power.c_str());
				nxtr->pointTurnRight(iUnits,iPower);
			}

	
			cout<<endl
				<<"  ****************** COMMAND ****************"<<endl
				<<"   ROBOT: point turn right for "<<iUnits<<" miliseconds"<<endl
				<<"   ROBOT: with a power of "<<iPower<<endl
				<<"  *******************************************"<<endl;
		}
	}

	void executePointTurnLeft(string args,nxt_remote * nxtr)
	{
		// Parse the arguments. 
		string units = args;
		string power = "";

	
		for(unsigned int i = 0; i < args.size(); i++)
		{
			if(args[i] == ',')
			{
				power = args.substr(args.find(",")+1,args.size()); 
			}
		}

		// Finding out what unit the argument is. 
		if(units.find("deg") != -1)
		{
			// Remove the units specifier. 
			units.replace(units.find("deg"),2,"");

			int iUnits = atoi(units.c_str());
			int iPower;


			if(power.size() == NULL)
			{
				iPower = 50;
				nxtr->pointTurnLeft(iUnits,50);
			}
			else
			{
				iPower = atoi(power.c_str());
				nxtr->pointTurnLeft(iUnits,iPower);
			}

			cout<<endl
				<<"  ****************** COMMAND ****************"<<endl
				<<"  ROBOT: point turn left "<<iUnits<<" degrees"<<endl
				<<"  ROBOT: with a power of "<<iPower<<endl
				<<"  *******************************************"<<endl;
		}
		else if(units.find("ms") != -1)
		{
			units.replace(units.find("ms"),2,"");

			int iUnits = atoi(units.c_str());
			int iPower;

			if(power.size() == NULL)
			{
				iPower = 50;
				nxtr->pointTurnLeft(iUnits,50);
			}
			else
			{
				iPower = atoi(power.c_str());
				nxtr->pointTurnLeft(iUnits,iPower);
			}

	
			cout<<endl
				<<"  ****************** COMMAND ****************"<<endl
				<<"   ROBOT: point turn left for "<<iUnits<<" miliseconds"<<endl
				<<"   ROBOT: with a power of "<<iPower<<endl
				<<"  *******************************************"<<endl;
		}
	}

	void executeSwingTurnLeft(string args,nxt_remote * nxtr)
	{
		// Parse the arguments. 
		string units = args;
		string power = "";

	
		for(unsigned int i = 0; i < args.size(); i++)
		{
			if(args[i] == ',')
			{
				power = args.substr(args.find(",")+1,args.size()); 
			}
		}

		// Finding out what unit the argument is. 
		if(units.find("deg") != -1)
		{
			// Remove the units specifier. 
			units.replace(units.find("deg"),2,"");

			int iUnits = atoi(units.c_str());
			int iPower;


			if(power.size() == NULL)
			{
				iPower = 50;
				nxtr->swingTurnLeft(iUnits,50);
			}
			else
			{
				iPower = atoi(power.c_str());
				nxtr->swingTurnLeft(iUnits,iPower);
			}

			cout<<endl
				<<"  ****************** COMMAND ****************"<<endl
				<<"  ROBOT: swing turn left "<<iUnits<<" degrees"<<endl
				<<"  ROBOT: with a power of "<<iPower<<endl
				<<"  *******************************************"<<endl;
		}
		else if(units.find("ms") != -1)
		{
			units.replace(units.find("ms"),2,"");

			int iUnits = atoi(units.c_str());
			int iPower;

			if(power.size() == NULL)
			{
				iPower = 50;
				nxtr->swingTurnLeft(iUnits,50);
			}
			else
			{
				iPower = atoi(power.c_str());
				nxtr->swingTurnLeft(iUnits,iPower);
			}

	
			cout<<endl
				<<"  ****************** COMMAND ****************"<<endl
				<<"   ROBOT: swing turn left for "<<iUnits<<" miliseconds"<<endl
				<<"   ROBOT: with a power of "<<iPower<<endl
				<<"  *******************************************"<<endl;
		}

	}

	void executeSwingTurnRight(string args,nxt_remote * nxtr)
	{
		// Parse the arguments. 
		string units = args;
		string power = "";

	
		for(unsigned int i = 0; i < args.size(); i++)
		{
			if(args[i] == ',')
			{
				power = args.substr(args.find(",")+1,args.size()); 
			}
		}

		// Finding out what unit the argument is. 
		if(units.find("deg") != -1)
		{
			// Remove the units specifier. 
			units.replace(units.find("deg"),2,"");

			int iUnits = atoi(units.c_str());
			int iPower;


			if(power.size() == NULL)
			{
				iPower = 50;
				nxtr->swingTurnRight(iUnits,50);
			}
			else
			{
				iPower = atoi(power.c_str());
				nxtr->swingTurnRight(iUnits,iPower);
			}

			cout<<endl
				<<"  ****************** COMMAND ****************"<<endl
				<<"  ROBOT: swing turn right "<<iUnits<<" degrees"<<endl
				<<"  ROBOT: with a power of "<<iPower<<endl
				<<"  *******************************************"<<endl;
		}
		else if(units.find("ms") != -1)
		{
			units.replace(units.find("ms"),2,"");

			int iUnits = atoi(units.c_str());
			int iPower;

			if(power.size() == NULL)
			{
				iPower = 50;
				nxtr->swingTurnRight(iUnits,50);
			}
			else
			{
				iPower = atoi(power.c_str());
				nxtr->swingTurnRight(iUnits,iPower);
			}

	
			cout<<endl
				<<"  ****************** COMMAND ****************"<<endl
				<<"   ROBOT: swing turn right for "<<iUnits<<" miliseconds"<<endl
				<<"   ROBOT: with a power of "<<iPower<<endl
				<<"  *******************************************"<<endl;
		}
	}



	//****************** END COMMANDS AND ARGUMENTS ************************



	// Process individual commands
	void processCommand(string command,string args,nxt_remote * nxtr)
	{

		// Make the arguments case-insensitive 
		args = lowerCaseString(args);

		// Execute the commands.
		if(command.compare("moveforward") == 0)
		{
			executeMoveFoward(args,nxtr);
		}
		else if(command.compare("moveback") == 0)
		{
			executeMoveBack(args, nxtr);
		}
		else if(command.compare("pturnleft") == 0)
		{
			executePointTurnRight(args, nxtr);
		}
		else if(command.compare("pturnright") == 0)
		{
			executePointTurnLeft(args, nxtr);
		}
		else if(command.compare("sturnleft") == 0 || command.compare("turnleft") == 0)
		{
			executeSwingTurnLeft(args,nxtr);
		}
		else if(command.compare("sturnright") == 0 || command.compare("turnright") == 0)
		{
			executeSwingTurnRight(args,nxtr);
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
		// The actual command.
		string command = line.substr(0,line.find("(")); 
		
		// Arguments of the function.. dont include the parenthisis
		string args = line.substr(line.find("(")+1,(line.find(")") - line.find("("))-1 );

		// Process the individual commands.
		processCommand(command,args,nxtr);
	}

	
}

*/