/** RobotAPI.h
 * Andrew Ribeiro 
 * November 21, 2009
**/

#pragma once

#include <string>
#include <windows.h>
#include "nxt_remote.h"
using std::string;

namespace comandrewribeiroremoterobot
{
	class RobotAPI
	{
	private:
		string username;
		string password;
		bool validLogin;
		nxt_remote * robotControl;

		void connectToRobot();

	public:
		RobotAPI(string username,string password);
		
		RobotAPI();

		nxt_remote * getRobotControl(){ return this->robotControl; }
		
		string currentCommand();

		void popCommand();

		void startProcessing();

		bool isValidClient(){ return this->validLogin;}

		
	};
}