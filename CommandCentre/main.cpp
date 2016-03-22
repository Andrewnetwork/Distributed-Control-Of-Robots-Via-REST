/** Main.cpp
 * Andrew Ribeiro 
 * November 21, 2009
**/

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
using namespace comandrewribeiroremoterobot;

int main() 
{
	cout<<"******* REMOTE ROBOT COMMAND CENTERE ***********"<<endl
		<<"* Welcome to the command centere. Here is where*"<<endl
		<<"* bluetooth commands are issued to a NXT robot.*"<<endl
		<<"* This particular version is built for use on  *"<<endl
		<<"* a windows based PC, however the architecture *"<<endl
		<<"* supports manny client types... enjoy         *"<<endl
		<<"*                                              *"<<endl
		<<"* Created by: Andrew Ribeiro & Jean Silva      *"<<endl
		<<"************************************************"<<endl<<endl;

	bool loopCondition = true;
	RobotAPI sysAPI;

	while(loopCondition)
	{
		string username,password;
		char ch;

		cout<<"********* API Connection ************"<<endl
			<<"* Username: ";

		getline(cin,username);

		cout<<"* Password: ";
		
		ch = _getch();

		// While the user does not press enter. 
		while(ch != 13)
		{
		   password.push_back(ch);
		   cout << '*';
		   ch = _getch();
		}

		cout<<endl<<"*************************************"<<endl;

		RobotAPI api(username,password);

		// If it is not a valid client, ask for password again.
		if(api.isValidClient())
		{
			// Client is valid, go to menu.
			loopCondition = false;
			sysAPI = api;
		}
	}
	
	do
	{
		int choice;

		cout<<endl
			<<endl
			<<"*************** MAIN MENU **************"<<endl
			<<" 1.) Start command processing"<<endl
			<<" 2.) View system log"<<endl
			<<" 3.) View connected users"<<endl
			<<" 4.) View system status"<<endl
			<<" 5.) Clear last command"<<endl
			<<" Choice(1,2,3,4,5): ";

		cin>>choice;

		if(choice == 1)
		{
			sysAPI.startProcessing();
		}
		else if(choice == 5)
		{
			sysAPI.popCommand();
			cout<<"  SYSTEM: first command in queue was killed."<<endl;
		}
		
	}while(true);


	return 0;
}
