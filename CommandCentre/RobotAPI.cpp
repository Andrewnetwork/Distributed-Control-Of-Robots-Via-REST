/** RobotAPI.cpp
 * Andrew Ribeiro 
 * November 21, 2009
**/

#pragma once

#include <string>
#include <vector>
#include <iostream>
using namespace std;

#include <windows.h>
#include <wininet.h>
#include <conio.h>

#include "web.h"
using namespace openutils;

#include "RobotAPI.h"
#include "constants.h"
#include "ErrorCodes.h"



namespace comandrewribeiroremoterobot
{
	//************************ FUNCTION PROTOTYPES **********************
	void executeScript(string script, nxt_remote * nxtr);
	void swingTurnLeft(int time, int power, nxt_remote * nxtr);
	//********************************************************************

	//************************** START ROBOT COMMANDS ********************
	void RobotAPI::connectToRobot()
	{
		// This is our interface with the NXT
		this->robotControl = new nxt_remote(); 

		// CHANGE THIS
		_cprintf("  SYSTEM: Starting NXT communication on port COM4... ");

		//initialize interface and check if initialization failed
	    if (this->robotControl->startcommunication("COM4")==0)
		{ 
			_cprintf("  SYSTEM: NXT communication failed.");

			//wait for keypress
			while (!_kbhit()); 
			return;
	    }
	}

	//********************************************************************

	//************************** START API COMMANDS *******************
	string RobotAPI::currentCommand()
	{
		try 
		{	
			WebForm wf;
			// the web server name is set
			wf.setHost(REST_ROOT_URL.c_str());
			// the script to be executed on the web server...
			wf.setScriptFile(REST_API_URL.c_str());

			// form variables are added to the request object
			wf.putVariable("username",this->username.c_str());
			wf.putVariable("password",this->password.c_str());
			wf.putVariable("fn","get_raw_command");
			
			cout<<endl<<"  SYSTEM: Retreving next script from database"<<endl;
			wf.sendRequest();

			string response;

			if(wf.getResponse(response,COMMAND_MAX_SIZE)) 
			{
				// If no error 
				if(response.find("Error") == -1)
				{
					// The command has finished running. 
					if(response.size() > 0)
					{
						cout<<endl<<"  SYSTEM: Retreved script from database"<<endl;
						return response;
					}
					else
					{
						cout<<endl<<"  SYSTEM: Script queue is empty"<<endl;
						return "";
					}
				}
				else
				{
					// Recieved error code.
					if(response.compare(ErrorCodes::DB_ERROR) == 0)
					{
						cout<<endl<<"  SYSTEM: "<<ErrorCodes::getDiscription(ErrorCodes::DB_ERROR)<<endl;
					}
					else
					{
						cout<<"  SYSTEM: Unknown error"<<endl;
					}
					return "  SYSTEM: ERROR";
				}
			}
			else 
			{
				cout << "  SYSTEM: No response from server" << endl;
				return "ERROR";
			}	

		}
		catch(WebFormException ex) 
		{
			cout << ex.getMessage() << endl;
		}

		return "ERROR";
	}


	void RobotAPI::popCommand()
	{
		try 
		{	
			WebForm wf;
			// the web server name is set
			wf.setHost(REST_ROOT_URL.c_str());
			// the script to be executed on the web server...
			wf.setScriptFile(REST_API_URL.c_str());

			// form variables are added to the request object
			wf.putVariable("username",this->username.c_str());
			wf.putVariable("password",this->password.c_str());
			wf.putVariable("fn","pop_command_list");
			cout<<endl<<"  SYSTEM: Clearing current script from list"<<endl;
		
			wf.sendRequest();

			string response;

			if(wf.getResponse(response,50)) 
			{
				if(response.size() == 0)
				{
					// The command has finished running. 
					cout<<endl<<"  SYSTEM: Script succesfully ended"<<endl;
				}
				else
				{
					// Recieved error code.
					if(response.compare(ErrorCodes::DB_ERROR) == 0)
					{
						cout<<endl<<"  SYSTEM: "<<ErrorCodes::getDiscription(ErrorCodes::DB_ERROR)<<endl;
					}
					else
					{
						cout<<"  SYSTEM: Unknown error"<<endl;
					}
				}
			}
			else 
			{
				cout << "  SYSTEM: No response from server" << endl;
			}	

		}
		catch(WebFormException ex) 
		{
			cout << ex.getMessage() << endl;
		}


	}



	//************************** END API COMMANDS *******************

	//********************* START THREADS **********************
	DWORD WINAPI stopProcessingCommands(LPVOID hndle)
	{
		HANDLE * processCommandHandle = (HANDLE *)hndle;

		while(true)
		{

			// If user presses q stop processing commands.
			if(_getch() == 113)
			{
				// Kill the processing thread.
				TerminateThread(processCommandHandle,0); 
				cout<<endl<<"  SYSTEM: this command centre is now offline."<<endl;
				break;
			}
		}

		return 0;
	}

	DWORD WINAPI processCommands(LPVOID api)
	{
		RobotAPI * connection = (RobotAPI *)api;

		while(true)
		{
			string clientCommand;

			// While no command is found, check for one. 
			while(true)
			{
				clientCommand = connection->currentCommand();
				//cout<<endl<<clientCommand<<endl;

				// If there is a command, execute it. 
				if(clientCommand.size() != 0)
				{
					break;
				}
				Sleep(5000);
			}

			// Process the current commands.
			executeScript(clientCommand,connection->getRobotControl());
			connection->popCommand();
		}
		

	}

	//********************* END THREADS ************************


	//************************** START CLIENT FUNCTIONALITY **************
	void RobotAPI::startProcessing()
	{
		cout<<endl<<"  SYSTEM: Starting to process commands."<<endl;

		this->connectToRobot();

		cout<<endl
			<<"*************** SYSTEM LOG *******************"<<endl
			<<"* Press q to stop processing commands        *"<<endl;
		
		HANDLE listenForCommands,listenForQuit;
		DWORD dwGenericThread;

		// Keep fetching data from a database and making the robot move
		listenForCommands = CreateThread(NULL,0,processCommands,this,0,&dwGenericThread);

		// If the thread was not created.
		if(listenForCommands == NULL)
		{
			DWORD dwError = GetLastError();
			cout<<"  SYSTEM: "<<dwError<<endl ;
			return;
		}

		// Listen if the user wants to quit. 
		listenForQuit = CreateThread(NULL,0,stopProcessingCommands,listenForCommands,0,&dwGenericThread);

		// If the thread was not created.
		if(listenForQuit == NULL)
		{
			DWORD dwError = GetLastError();
			cout<<"  SYSTEM: "<<dwError<<endl ;
			return;
		}


		const HANDLE threads[] = {listenForCommands,listenForQuit}; 

		// Wait untill all threads have finished.
		WaitForMultipleObjects(2,threads,true,INFINITE);
	}



	//************************** END CLIENT FUNCTIONALITY **************

	//********************** START CONSTRUCTORS *************************
	RobotAPI::RobotAPI(string username, string password)
	{
		this->username = username;
		this->password = password;

		try 
		{	
			WebForm wf;
			// the web server name is set
			wf.setHost(REST_ROOT_URL.c_str());
			// the script to be executed on the web server...
			wf.setScriptFile(REST_API_URL.c_str());
			cout<<endl<<"  SYSTEM: Connecting to " << wf.getHost() << "..." << endl;

			// form variables are added to the request object
			wf.putVariable("username",username.c_str());
			wf.putVariable("password",password.c_str());
		
			cout << "  SYSTEM: Checking user credentials..." << endl;
			// data is encoded and send to the server script
			// for processing
			wf.sendRequest();

			// reading back any response	
			string response;

			if(wf.getResponse(response,50)) 
			{
				if(response.size() == 0)
				{
					// User credentials are good.
					cout<<"  SYSTEM: Login credentials confirmed"<<endl
						<<"  SYSTEM: This system is now a Command Centere"<<endl<<endl;
					validLogin = true;
				}
				else
				{
					validLogin = false;
					if(response.compare(ErrorCodes::INVALID_LOGIN) == 0)
					{
						cout<<endl<<"  SYSTEM: "<<ErrorCodes::getDiscription(ErrorCodes::INVALID_LOGIN)<<endl;
					}
					else
					{
						cout<<"  SYSTEM: Unknown error"<<endl;
					}
				}
			}
			else 
			{
				cout << "  SYSTEM: No response from server" << endl;
			}	

		}
		catch(WebFormException ex) 
		{
			cout << ex.getMessage() << endl;
		}

	}


	RobotAPI::RobotAPI(){}
	//********************** END CONSTRUCTORS ***************************
}