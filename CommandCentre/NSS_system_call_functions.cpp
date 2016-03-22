/** NSS_system_call_functions.cpp
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


	//****************** START SYSTEM MOVEMENT FUNCTIONS ********************
	// NOTE: change around to remove repeating functionality.
	void NSS::executeMoveFoward(string args)
	{
		try
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

			
				this->getRemoteControl()->moveFwd(iUnits,iPower);

				cout<<endl
					<<"  ****************** COMMAND ****************"<<endl
					<<"   ROBOT: move foward for "<<iUnits<<" miliseconds"<<endl
					<<"   ROBOT: with a power of "<<iPower<<endl
					<<"  *******************************************"<<endl;
			}
		}
		catch(...)
		{
			cout<<"  SYSTEM: problem with arguments sent to the move forward command"<<endl;
		}

	}

	void NSS::executeMoveBack(string args)
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

			this->getRemoteControl()->moveBack(iUnits,iPower);

			cout<<endl
				<<"  ****************** COMMAND ****************"<<endl
				<<"  ROBOT: move backward for "<<iUnits<<" miliseconds"<<endl
				<<"  ROBOT: with a power of "<<iPower<<endl
				<<"  *******************************************"<<endl;
		}
	}
	void NSS::executePointTurnRight(string args)
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
				this->remoteControl->pointTurnLeft(iUnits,50);
			}
			else
			{
				iPower = atoi(power.c_str());
				this->remoteControl->pointTurnLeft(iUnits,iPower);
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
				this->remoteControl->pointTurnRight(iUnits,50);
			}
			else
			{
				iPower = atoi(power.c_str());
				this->remoteControl->pointTurnRight(iUnits,iPower);
			}

	
			cout<<endl
				<<"  ****************** COMMAND ****************"<<endl
				<<"   ROBOT: point turn right for "<<iUnits<<" miliseconds"<<endl
				<<"   ROBOT: with a power of "<<iPower<<endl
				<<"  *******************************************"<<endl;
		}
	}

	void NSS::executePointTurnLeft(string args)
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
				this->remoteControl->pointTurnLeft(iUnits,50);
			}
			else
			{
				iPower = atoi(power.c_str());
				this->remoteControl->pointTurnLeft(iUnits,iPower);
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
				this->remoteControl->pointTurnLeft(iUnits,50);
			}
			else
			{
				iPower = atoi(power.c_str());
				this->remoteControl->pointTurnLeft(iUnits,iPower);
			}

	
			cout<<endl
				<<"  ****************** COMMAND ****************"<<endl
				<<"   ROBOT: point turn left for "<<iUnits<<" miliseconds"<<endl
				<<"   ROBOT: with a power of "<<iPower<<endl
				<<"  *******************************************"<<endl;
		}
	}

	void NSS::executeSwingTurnLeft(string args)
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
				this->remoteControl->swingTurnLeft(iUnits,50);
			}
			else
			{
				iPower = atoi(power.c_str());
				this->remoteControl->swingTurnLeft(iUnits,iPower);
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
				this->remoteControl->swingTurnLeft(iUnits,50);
			}
			else
			{
				iPower = atoi(power.c_str());
				this->remoteControl->swingTurnLeft(iUnits,iPower);
			}

	
			cout<<endl
				<<"  ****************** COMMAND ****************"<<endl
				<<"   ROBOT: swing turn left for "<<iUnits<<" miliseconds"<<endl
				<<"   ROBOT: with a power of "<<iPower<<endl
				<<"  *******************************************"<<endl;
		}

	}

	void NSS::executeSwingTurnRight(string args)
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
				this->remoteControl->swingTurnRight(iUnits,50);
			}
			else
			{
				iPower = atoi(power.c_str());
				this->remoteControl->swingTurnRight(iUnits,iPower);
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
				this->remoteControl->swingTurnRight(iUnits,50);
			}
			else
			{
				iPower = atoi(power.c_str());
				this->remoteControl->swingTurnRight(iUnits,iPower);
			}

	
			cout<<endl
				<<"  ****************** COMMAND ****************"<<endl
				<<"   ROBOT: swing turn right for "<<iUnits<<" miliseconds"<<endl
				<<"   ROBOT: with a power of "<<iPower<<endl
				<<"  *******************************************"<<endl;
		}
	}




	void NSS::executeSleep(string args)
	{
		try
		{
			Sleep(atoi(args.c_str()));
		}
		catch(...)
		{
			cout<<"  SYSTEM: problem while executing Sleep/Wait command."<<endl;
		}
	}
	//****************** END SYSTEM MOVEMENT FUNCTIONS *********************

	// Process individual commands
	void NSS::processCommand(string command,string args)
	{
		// Execute the commands.
		if(command.compare("moveforward") == 0)
		{
			executeMoveFoward(args);
		}
		else if(command.compare("moveback") == 0)
		{
			executeMoveBack(args);
		}
		else if(command.compare("pturnleft") == 0)
		{
			executePointTurnRight(args);
		}
		else if(command.compare("pturnright") == 0)
		{
			executePointTurnLeft(args);
		}
		else if(command.compare("sturnleft") == 0 || command.compare("turnleft") == 0)
		{
			executeSwingTurnLeft(args);
		}
		else if(command.compare("sturnright") == 0 || command.compare("turnright") == 0)
		{
			executeSwingTurnRight(args);
		}
		else if(command.compare("sleep") == 0 || command.compare("wait") == 0)
		{
			executeSleep(args);
		}
		else
		{
			cout<<"  SYSTEM: user tried to execute an invalid system command."<<endl;
			cout<<"  SYSTEM: "<<command<<endl;
		}
	}

	void NSS::systemCallParsing(string & line)
	{
		// The actual command.

		int leftBracket = line.find("("), rightBracket = line.find(")");

		// Check if it is a function call. 
		if(leftBracket != string::npos && rightBracket != string::npos)
		{
			string command = line.substr(0,leftBracket); 
			
			// Arguments of the function.. dont include the parenthisis
			string args = line.substr(leftBracket+1,(rightBracket - (leftBracket-1) ));

			// Process the individual commands.
			processCommand(command,args);
		}
		
	}
}