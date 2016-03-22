
#include <windows.h>
#include <conio.h>
#include "nxt_remote.h"

nxt_remote *nxtr;

//Time functions
	void moveFwd(int time, int power);
	void moveBack(int time, int power);

	void pointTurnLeft(int time, int power);
	void pointTurnRight(int time, int power);

	void swingTurnLeft(int time, int power);
	void swingTurnRight(int time, int power);
//END TIME FUNCTIONS

int main(int argc, char* argv[]){
  nxtr=new nxt_remote(); //this is our interface with the NXT

  _cprintf("Starting NXT communication on port COM6... ");
  if (nxtr->startcommunication("COM8")==0){ //initialize interface and check if initialization failed
    _cprintf("NXT communication failed.");
    while (!_kbhit()); //wait for keypress
    return(0);
  }

  //set sensor types, switch on used sensors and motors
  //nxtr->NXT_sensortype[0]=0x01; //switch
  //nxtr->NXT_sensoron[0]=1;             
  //nxtr->NXT_motoron[0]=1;
  //nxtr->NXT_motoron[2]=1;

	moveFwd(1000, 70);
	Sleep(1000);
	pointTurnLeft(300, 30);
	Sleep(1000);
	moveFwd(1000, 70);
	Sleep(1000);
	swingTurnRight(100, 30);
	Sleep(1000);

  nxtr->stopcommunication();   //stop interfacing. This also stops the motors.
	return 0;
}

//move forward for specific time
void moveFwd(int time, int power){
	//Turning motors on
	nxtr->NXT_motoron[0]=1;
	nxtr->NXT_motoron[2]=1;

	//Setting the motors power/velocity
	nxtr->NXT_motorval[0] = power;
	nxtr->NXT_motorval[2] = power;

	Sleep(time);
}

//move forward for specific time
void moveBack(int time, int power){
	//Turning motors on
	nxtr->NXT_motoron[0]=1;
	nxtr->NXT_motoron[2]=1;

	//Setting the motors power/velocity
	nxtr->NXT_motorval[0] = -power;
	nxtr->NXT_motorval[2] = -power;

	Sleep(time);
}


void pointTurnLeft(int time, int power){
	//Turning motors on
	nxtr->NXT_motoron[0]=1;
	nxtr->NXT_motoron[2]=0;

	//Setting the motors power/velocity
	nxtr->NXT_motorval[0] = power;

	Sleep(time);
}

void pointTurnRight(int time, int power){
	//Turning motors on
	nxtr->NXT_motoron[0]=0;
	nxtr->NXT_motoron[2]=1;

	//Setting the motors power/velocity
	nxtr->NXT_motorval[2] = power;

	Sleep(time);
}

void swingTurnRight(int time, int power){
	//Turning motors on
	nxtr->NXT_motoron[0]=1;
	nxtr->NXT_motoron[2]=1;

	//Setting the motors power/velocity
	nxtr->NXT_motorval[0] = -power;
	nxtr->NXT_motorval[2] = power;

	Sleep(time);
}
void swingTurnLeft(int time, int power){
	//Turning motors on
	nxtr->NXT_motoron[0]=1;
	nxtr->NXT_motoron[2]=1;

	//Setting the motors power/velocity
	nxtr->NXT_motorval[0] = power;
	nxtr->NXT_motorval[2] = -power;

	Sleep(time);
}
