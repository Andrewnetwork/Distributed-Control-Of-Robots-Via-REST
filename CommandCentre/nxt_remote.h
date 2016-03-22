//nxt_remote.h
//header file for nxt_remote.cpp
//V 1.01 (c) 12.2006 by Daniel Berger (daniel.berger@tuebingen.mpg.de)
// MODIFICATIONS BY: Andrew Ribeiro 

#pragma once


class nxt_remote
{
protected:
  int NXT_send(unsigned char *message, int length);
  int NXT_receive(unsigned char *rcbuf, unsigned long length);
  int NXT_close();
  int NXT_open(char *portname);
  int NXT_updateinputtypemode(unsigned char inputnr);
  int NXT_setultrasonic(unsigned char inputnr);
  int NXT_stopultrasonic(unsigned char inputnr);
  int NXT_getultrasonicvalue(unsigned char inputnr);
  int NXT_getultrasonicvaluefast(unsigned char inputnr);
  int NXT_initinput(unsigned char inputnr);
  int NXT_pollinput(unsigned char inputnr);
  int NXT_setoutputstate(unsigned char outputnr, char powersetpoint, unsigned char modebyte, unsigned char regulationmode, unsigned char turnratio, unsigned char runstate, unsigned long tacholimit);
  static DWORD WINAPI NXT_loop(LPVOID lpParameter);
  void initvariables();

  //DCB dcb;
  COMMTIMEOUTS tout;
  HANDLE NXT_port;
  DWORD NXT_thread_id;
  char portname[256];
  //int porttype=0;

  unsigned char sendbuf[256];
  unsigned char recbuf[256];
  unsigned char mess[256];
  OVERLAPPED ovl;

  int i_sensoron[4];
  int i_sensortype[4];
  int i_sensormode[4];

  int i_motoron[3];
  int i_motorval[3];

  int i_ready;

public:
  nxt_remote();
  ~nxt_remote();

  //***** CUSTOM FUNCTIONALITY *******
  void moveFwd(int time, int power);
  void moveBack(int time, int power);
  void pointTurnLeft(int time, int power);
  void pointTurnRight(int time, int power);
  void swingTurnRight(int time, int power);
  void swingTurnLeft(int time, int power);
  void turnOffMotors();
  //****** END CUSTOM FUNCTIONALITY **

  int nxt_internal(); //only for internal usage.

  int startcommunication(char *in_portname);
  int stopcommunication();

  unsigned char nxtname[15];
  unsigned char btaddress[8];

  volatile int NXT_sensoron[4];
  volatile int NXT_sensortype[4];
  volatile int NXT_sensormode[4];

  volatile int NXT_sensorvalraw[4];    //Raw A/D sensor value (UWORD, device dependent)
  volatile int NXT_sensorvalnorm[4];   //Normalized A/D sensor value (UWORD, type dependent; Range: 0-1023)
  volatile int NXT_sensorvalscaled[4]; //Scaled value (SWORD; mode dependent)
  volatile int NXT_sensorvalcalib[4];  //Calibrated value (SWORD; CURRENTLY UNUSED)

  volatile int NXT_motoron[3];   //0 or 1; off or on
  volatile int NXT_motorval[3];  //motor power: -100..100

  volatile int NXT_stop;
  volatile int NXT_error;

};
