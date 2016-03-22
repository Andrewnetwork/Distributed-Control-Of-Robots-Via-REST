//nxt_remote.cpp
//a class for remote-controlling the Lego NXT via Bluetooth
//V 1.01 (c) 12.2006 by Daniel Berger
// MODIFICATIONS BY: Andrew Ribeiro 

#include <windows.h>
#include <iostream>
using namespace std;
#include "nxt_remote.h"


/////// PRIVATE ROUTINES

int nxt_remote::NXT_send(unsigned char *message, int length)
{
  //sends a message to the RCX
  //returns 1 if write succeeded, 0 if failed
  //maximal length of message is 125 bytes
  int i;
  unsigned long res; //,ptr;
  //int s=0;

  res=0;
  ovl.Offset=0;
  ovl.OffsetHigh=0;
  ovl.hEvent=NULL;
  if(!WriteFile(NXT_port,message,length,&res,&ovl)){
    if (GetLastError()==ERROR_IO_PENDING){
      i=0;
      do{
        Sleep(10);
        i++;
      } while ((!HasOverlappedIoCompleted(&ovl))&&(i<50));
      if (i<50){
        return(1); //completed.
      } else {
        CancelIo(NXT_port); //cancel transmission.
        return(0); //not completed.
      }
    } else { //some error occured
      CancelIo(NXT_port); //cancel transmission.
      return(0);
    }
  }
  return(1);
}
int nxt_remote::NXT_receive(unsigned char *rcbuf, unsigned long length){
  //attempts to read a message of specified length from the NXT via bluetooth
  //returns number of bytes read, 0 if error
  unsigned long res=0;
  int i;

  ovl.Offset=0;
  ovl.OffsetHigh=0;
  ovl.hEvent=NULL;
  if (!ReadFile(NXT_port,rcbuf,length,&res,&ovl)){
    //return(0);
    if (GetLastError()==ERROR_IO_PENDING){
      i=0;
      do{
        Sleep(10);
        i++;
      } while ((!HasOverlappedIoCompleted(&ovl))&&(i<50));
      if (i<50){
        GetOverlappedResult(NXT_port,&ovl,&res,FALSE);
        return(res); //completed.
      } else {
        CancelIo(NXT_port); //cancel transmission.
        return(0); //not completed.
      }
    } else { //some error occured
      CancelIo(NXT_port); //cancel transmission.
      return(0);
    }
  }
  return(res); //return number of bytes read

  //return(1);
}

int nxt_remote::NXT_close(){
  return(CloseHandle(NXT_port));
};

int nxt_remote::NXT_open(char *portname){
  int i,res;

  for (int i=0; i<256; i++) mess[i]=0;

  //initialize serial connection
  NXT_port = CreateFile(portname, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_FLAG_WRITE_THROUGH | FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING, 0);
  if (NXT_port == INVALID_HANDLE_VALUE) return(0);

  //GetCommTimeouts(NXT_port,&tout);
  //tout.ReadIntervalTimeout=250;
  //tout.ReadTotalTimeoutConstant=10;
  //tout.ReadTotalTimeoutMultiplier=10;
  //tout.WriteTotalTimeoutConstant=10;
  //tout.WriteTotalTimeoutMultiplier=10;
  //SetCommTimeouts(NXT_port,&tout);

  //Sleep(100);

  //attempt to communicate with NXT: get device info
  mess[0]=2; //two bytes follow
  mess[1]=0;
  mess[2]=0x01;
  mess[3]=0x9B;
  res=NXT_send(mess,4);
  if (!res){
    NXT_close();
    return(0);
  }
  Sleep(500); //wait 100ms
  res=NXT_receive(mess,33+2);
  if ((res!=35)||(mess[2]!=0x02)||(mess[3]!=0x9b)||(mess[4]!=0x00)){ //correct response?
    NXT_close();
    return(0);
  }

  //store device info
  for (i=0; i<15; i++) nxtname[i]=mess[i+5];
  for (i=0; i<7; i++) btaddress[i]=mess[i+20];

  return(1); 
}

int nxt_remote::NXT_updateinputtypemode(unsigned char inputnr){ //, unsigned char type, unsigned char mode){
  //sets current sensor type and sensor mode of specified input to specified values
  //use NXT_pollinput to read these values back, to see if the NXT accepted them
  //returns 0 if failed and 1 if success
  //communication with NXT needs to be successfully initiated BEFORE calling this routine!
  int ret;

  if ((i_sensortype[inputnr]==NXT_sensortype[inputnr])&&(i_sensormode[inputnr]==NXT_sensormode[inputnr])) 
    return(1); //do nothing

  if (i_sensortype[inputnr]==0x0B){ //was ultrasonic, de-init
    ret=NXT_stopultrasonic(inputnr);
    if (ret==0) return(0); //return if de-init failed
  }

  if (NXT_sensortype[inputnr]==0x0B){ //set sensor to ultrasound
    ret=NXT_setultrasonic(inputnr);
  } else { //other sensors
    mess[0]=5; //five bytes follow
    mess[1]=0;
    mess[2]=0x80; //no response
    mess[3]=0x05;
    mess[4]=inputnr;
    mess[5]=NXT_sensortype[inputnr];
    mess[6]=NXT_sensormode[inputnr];
    ret=NXT_send(mess,7);
  }
  i_sensortype[inputnr]=NXT_sensortype[inputnr];
  i_sensormode[inputnr]=NXT_sensormode[inputnr];
  return(ret);
}

int nxt_remote::NXT_setultrasonic(unsigned char inputnr){
  //special initialization routine for the ultrasonic sensor
  int res;

  if (inputnr>3) return(0); //only ports 0..3

  //set sensor to "digital" mode
  mess[0]=5; //five bytes follow
  mess[1]=0;
  mess[2]=0x00; //0x80; //no response
  mess[3]=0x05; //setinputmode
  mess[4]=inputnr;
  mess[5]=0x0b; //lowspeed_9v type
  mess[6]=0x00; //rawmode mode
  res=NXT_send(mess,7);
  if (res==0) return(0);

  //Sleep(50);

  res=NXT_receive(mess,5);
  if ((res!=5)||(mess[4]!=0)) return(0);

  Sleep(20); //Sleep(50);

  //configure sensor: 00 02 41 02 via lswrite
  mess[0]=0x08; //message length without first two bytes
  mess[1]=0x00;
  mess[2]=0x00; //0x80; //no response please
  mess[3]=0x0F; //LS Write
  mess[4]=inputnr; //port number 0..3
  mess[5]=0x03; //Tx Data length
  mess[6]=0x00; //Rx Data length (no reply expected)
  mess[7]=0x02; //Data: "set sensor to send sonar pings continuously"
  mess[8]=0x41;
  mess[9]=0x02;
  res=NXT_send(mess,10);
  if (res==0) return(0);

  //Sleep(50);

  res=NXT_receive(mess,5);
  if ((res!=5)||(mess[4]!=0)) return(0);

  return(1);
}

int nxt_remote::NXT_stopultrasonic(unsigned char inputnr){
  //stops and de-initializes the ultrasonic sensor at the given input
  //returns 0 if failed, 1 if success
  int res;

  mess[0]=0x08; //message length without first two bytes
  mess[1]=0x00;
  mess[2]=0x00; //0x80; //no response please
  mess[3]=0x0F; //LS Write
  mess[4]=inputnr; //port number 0..3
  mess[5]=0x03; //Tx Data length
  mess[6]=0x00; //Rx Data length (no reply expected)
  mess[7]=0x02; //Data: "set sensor to off"
  mess[8]=0x41;
  mess[9]=0x00;
  res=NXT_send(mess,10);
  if (res==0) return(0);

  //Sleep(50);

  res=NXT_receive(mess,5);
  if ((res!=5)||(mess[4]!=0)) return(0);

  return(1);
}

int nxt_remote::NXT_getultrasonicvalue(unsigned char inputnr){
  //attempts to read an ultrasonic measurement value from an ultrasonic sensor
  //returns 0 if failed, 1 if success
  int res;

  //NXT_sensorvalraw[inputnr]=-10;

  //check for pending reply bytes in the NXT buffers: send 'read bytes', retrieve garbage reply bytes.
  //LSRead out all remaining data
  mess[0]=0x03; //message length without first two bytes
  mess[1]=0x00;
  mess[2]=0x00; //response please
  mess[3]=0x10; //LSRead
  mess[4]=inputnr; //port number 0..3
  res=NXT_send(mess,5);
  if (res==0){
    NXT_sensorvalraw[inputnr]=-2;
    return(0);
  }

  Sleep(50); //Sleep(10);
  res=NXT_receive(mess,20+2);
  if ((res!=22)||(mess[4]!=0)){
    NXT_sensorvalraw[inputnr]=-3;
    return(0);
  }
  Sleep(50);

  //send 0x01 0x02 0x42, to retrieve 0x01 bytes from read a continuous measurement distance (0x42) from address 0x02
  mess[0]=0x07; //message length without first two bytes
  mess[1]=0x00;
  mess[2]=0x00; //0x80; //no response please (to LS write)
  mess[3]=0x0F; //LSWrite
  mess[4]=inputnr; //port number 0..3
  mess[5]=0x02; //Tx Data length (two bytes sent - 02 42)
  mess[6]=0x01; //Rx Data length (1 byte reply expected)
  mess[7]=0x02; //address for "read sonar"
  mess[8]=0x42; //read distance
  res=NXT_send(mess,9);
  if (res==0){
    NXT_sensorvalraw[inputnr]=-4;
    return(0);
  }

  Sleep(50); //Sleep(10);

  res=NXT_receive(mess,5);
  if ((res!=5)||(mess[4]!=0)){
    NXT_sensorvalraw[inputnr]=-5;
    return(0);
  }

  Sleep(50);

  //check status of I2C message channel until idle, timeout or error
  //LSGetStatus: 0x00 0x0E port; return: 0x02 0x0E statusbyte nrofbytesready
  //statusbyte: 0 success, else error
  mess[0]=0x03; //message length without first two bytes
  mess[1]=0x00;
  mess[2]=0x00; //response please
  mess[3]=0x0E; //LSGetStatus
  mess[4]=inputnr; //port number 0..3
  res=NXT_send(mess,5);

  if (res==0){
    NXT_sensorvalraw[inputnr]=-6;
    return(0);
  }

  Sleep(50);

  //if 'idle', send "read 1 I2C reply byte" and read response
  res=NXT_receive(mess,4+2);
  if (res!=6){
    NXT_sensorvalraw[inputnr]=-7;
    return(0);
  }

  if ((mess[4]==0)&&(mess[5]>0)){ //status OK and bytes available for reading?

    mess[0]=0x03; //message length without first two bytes
    mess[1]=0x00;
    mess[2]=0x00; //response please
    mess[3]=0x10; //LSRead
    mess[4]=inputnr; //port number 0..3
    res=NXT_send(mess,5);

    Sleep(50);

    res=NXT_receive(mess,20+2);
    NXT_sensorvalraw[inputnr]=mess[6]; //(int)mess[10]+((int)mess[11]<<8);
    return(1);
  }

  NXT_sensorvalraw[inputnr]=-8;
  return(0);
}

int nxt_remote::NXT_getultrasonicvaluefast(unsigned char inputnr){
  //attempts to read an ultrasonic measurement value from an ultrasonic sensor
  //returns 0 if failed, 1 if success
  int res;

  //NXT_sensorvalraw[inputnr]=-10;

  //check for pending reply bytes in the NXT buffers: send 'read bytes', retrieve garbage reply bytes.
  //LSRead out all remaining data
  
  //mess[0]=0x03; //message length without first two bytes
  //mess[1]=0x00;
  //mess[2]=0x00; //response please
  //mess[3]=0x10; //LSRead
  //mess[4]=inputnr; //port number 0..3
  //res=NXT_send(mess,5);
  //if (res==0){
  //  NXT_sensorvalraw[inputnr]=-2;
  //  return(0);
  //}

  //Sleep(50); //Sleep(10);
  //res=NXT_receive(mess,20+2);
  //if ((res!=22)||(mess[4]!=0)){
  //  NXT_sensorvalraw[inputnr]=-3;
  //  return(0);
  //}
  ////Sleep(50);

  //send 0x01 0x02 0x42, to retrieve 0x01 bytes from read a continuous measurement distance (0x42) from address 0x02
  mess[0]=0x07; //message length without first two bytes
  mess[1]=0x00;
  mess[2]=0x80; //no response please (to LS write)
  mess[3]=0x0F; //LSWrite
  mess[4]=inputnr; //port number 0..3
  mess[5]=0x02; //Tx Data length (two bytes sent - 02 42)
  mess[6]=0x01; //Rx Data length (1 byte reply expected)
  mess[7]=0x02; //address for "read sonar"
  mess[8]=0x42; //read distance
  res=NXT_send(mess,9);
  if (res==0){
    NXT_sensorvalraw[inputnr]=-1;
    return(0);
  }

  Sleep(20); //this is needed so that the command can finish before LSGetStatus is sent (10 ms is not enough)

  //Sleep(50); //Sleep(10);
  //res=NXT_receive(mess,5);
  //if ((res!=5)||(mess[4]!=0)){
  //  NXT_sensorvalraw[inputnr]=-5;
  //  return(0);
  //}
  //Sleep(50);

  //check status of I2C message channel until idle, timeout or error
  //LSGetStatus: 0x00 0x0E port; return: 0x02 0x0E statusbyte nrofbytesready
  //statusbyte: 0 success, else error
  mess[0]=0x03; //message length without first two bytes
  mess[1]=0x00;
  mess[2]=0x00; //response please
  mess[3]=0x0E; //LSGetStatus
  mess[4]=inputnr; //port number 0..3
  res=NXT_send(mess,5);

  if (res==0){
    NXT_sensorvalraw[inputnr]=-2;
    return(0);
  }

  //Sleep(20);

  //if 'idle', send "read 1 I2C reply byte" and read response
  res=NXT_receive(mess,4+2);
  if (res!=6){
    NXT_sensorvalraw[inputnr]=-3;
    return(0);
  }

  if ((mess[4]==0)&&(mess[5]>0)){ //status OK and bytes available for reading?
    mess[0]=0x03; //message length without first two bytes
    mess[1]=0x00;
    mess[2]=0x00; //response please
    mess[3]=0x10; //LSRead
    mess[4]=inputnr; //port number 0..3
    res=NXT_send(mess,5);

    if (res==0){
      NXT_sensorvalraw[inputnr]=-4;
      return(0);
    }

    //Sleep(20);

    res=NXT_receive(mess,20+2);
    NXT_sensorvalraw[inputnr]=mess[6]; //(int)mess[10]+((int)mess[11]<<8);
    return(1);
  }

//  NXT_sensorvalraw[inputnr]=-8;
  return(0);
}

int nxt_remote::NXT_initinput(unsigned char inputnr){
  //returns 0 if communication failed and 1 if success (NXT_error might still be set even then)
  //communication with NXT needs to be successfully initiated BEFORE calling this routine!
  int res;

  mess[0]=3; //three bytes follow
  mess[1]=0;
  mess[2]=0x00; //request response
  mess[3]=0x07; //GETINPUTVALUES
  mess[4]=inputnr; //from port 0 (1 on the brick)
  if(!NXT_send(mess,5)){
    NXT_error=-1; //communication error
    return(0);
  }
  Sleep(60); //wait 60ms for response
  res=NXT_receive(mess,16+2);
  if ((res==18)&&(mess[2]==0x02)&&(mess[3]==0x07)){
    //correct return message received
    if(mess[4]!=0){ //error
      NXT_error=mess[4];
    } else { //received 'no error'
      if (mess[5]==inputnr){ //correct input
        NXT_sensortype[inputnr]=mess[8]; i_sensortype[inputnr]=mess[8]; //read current sensor type back
        NXT_sensormode[inputnr]=mess[9]; i_sensormode[inputnr]=mess[9]; //read current sensor mode back
        if(mess[6]==1){ //new data is valid
          NXT_sensorvalraw[inputnr]=(int)mess[10]+((int)mess[11]<<8);
          NXT_sensorvalnorm[inputnr]=(int)mess[12]+((int)mess[13]<<8);
          NXT_sensorvalscaled[inputnr]=(int)((short)((int)mess[12]||((int)mess[13]<<8)));
          NXT_sensorvalcalib[inputnr]=(int)((short)((int)mess[14]||((int)mess[15]<<8)));
        }
      }
    }
  } else {
    return(0);
  }
  return(1);

}

int nxt_remote::NXT_pollinput(unsigned char inputnr){
  //returns 0 if communication failed and 1 if success (NXT_error might still be set even then)
  //communication with NXT needs to be successfully initiated BEFORE calling this routine!
  int res;

  if (i_sensortype[inputnr]==0x0B){ //special care for the ultrasound sensor
    NXT_getultrasonicvaluefast(inputnr);
  } else {
    mess[0]=3; //three bytes follow
    mess[1]=0;
    mess[2]=0x00; //request response
    mess[3]=0x07; //GETINPUTVALUES
    mess[4]=inputnr; //from port 0 (1 on the brick)
    if(!NXT_send(mess,5)){
      NXT_error=-1; //communication error
      return(0);
    }
    //Sleep(60); //wait 60ms for response
    res=NXT_receive(mess,16+2);
    if ((res==18)&&(mess[2]==0x02)&&(mess[3]==0x07)){
      //correct return message received
      if(mess[4]!=0){ //error
        NXT_error=mess[4];
      } else { //received 'no error'
        if (mess[5]==inputnr){ //correct input
          //NXT_sensortype[inputnr]=mess[8]; i_sensortype[inputnr]=mess[8]; //read current sensor type back
          //NXT_sensormode[inputnr]=mess[9]; i_sensormode[inputnr]=mess[9]; //read current sensor mode back
          i_sensortype[inputnr]=mess[8]; //read current sensor type back (NOT into NXT_sensortype/mode, since that would cancel the to-be-set-value!!)
          i_sensormode[inputnr]=mess[9]; //read current sensor mode back
          if(mess[6]==1){ //new data is valid
            NXT_sensorvalraw[inputnr]=(int)mess[10]+((int)mess[11]<<8);
            NXT_sensorvalnorm[inputnr]=(int)mess[12]+((int)mess[13]<<8);
            NXT_sensorvalscaled[inputnr]=(int)((short)((int)mess[12]||((int)mess[13]<<8)));
            NXT_sensorvalcalib[inputnr]=(int)((short)((int)mess[14]||((int)mess[15]<<8)));
          }
        }
      }
    } else {
      return(0);
    }
    return(1);
  }
  return(1);
}


int nxt_remote::NXT_setoutputstate(unsigned char outputnr, char powersetpoint, unsigned char modebyte, unsigned char regulationmode, unsigned char turnratio, unsigned char runstate, unsigned long tacholimit){
  int res;

  if ((outputnr<0)||(outputnr>2)) return(0);

  mess[0]=0x0C; //message length without first two bytes: 13 bytes follow (0x0c)
  mess[1]=0x00; 
  mess[2]=0x80; //no response please
  mess[3]=0x04; //SETOUTPUTSTATE
  mess[4]=outputnr; //port number 0..2
  mess[5]=(unsigned char)powersetpoint;
  mess[6]=modebyte;
  mess[7]=regulationmode;
  mess[8]=turnratio;
  mess[9]=runstate;
  mess[10]=(unsigned char)(tacholimit&0xff); //unsigned long tacholimit -not sure if the byte order is correct
  mess[11]=(unsigned char)((tacholimit>>8)&0xff);
  mess[12]=(unsigned char)((tacholimit>>16)&0xff);
  mess[13]=(unsigned char)(tacholimit>>24);
  res=NXT_send(mess,14);
  if (res==0) return(0);

  /*res=NXT_receive(mess,3+2);
  if ((res!=5)||(mess[4]!=0)) return(0);*/
  
  return(1);
}

int nxt_remote::nxt_internal(){
  //this is called from the static function NXT_loop and does the actual innerloop
  //users of the class should NEVER call this directly, or their program will hang!
  int len,i; //,res;

  //if (porttype==1){chunksize=16;} else {chunksize=7;} //serial and usb send different amounts of data
  //RCX_finished=0;
  NXT_error=0;

  //open port to lego infrared tower
  if (!NXT_open(portname)){
    NXT_stop=-1;
    NXT_error=-1;
    return(0);
  }

  //initialize correct sensor mode settings
  for (i=0; i<4; i++) NXT_initinput(i);

  NXT_stop=0;

  while(!NXT_stop){  
    //this loop handles the interface-NXT communication 
    //in parallel with the main program, since it runs in an extra task

    //Set new sensortype and sensormode, if changed
    for (i=0; i<4; i++){
      if ((NXT_sensortype[i]!=i_sensortype[i])||(NXT_sensormode[i]!=i_sensormode[i])){
        //i_sensortype[i]=NXT_sensortype[i];
        //i_sensormode[i]=NXT_sensormode[i];
        NXT_updateinputtypemode(i); //NXT_setinputtypemode(i,NXT_sensortype[i],NXT_sensormode[i]);
        Sleep(60);
        NXT_initinput(i);
      }
    }

    //Transfer changes of sensor switching on/off
    for (i=0; i<4; i++) i_sensoron[i]=NXT_sensoron[i];

    //Poll inputs
    for (i=0; i<4; i++){
      if (i_sensoron[i]) NXT_pollinput(i);
    }

    //Set motor output values, if changed
    for (i=0; i<3; i++){
      if ((NXT_motoron[i]!=i_motoron[i])||(NXT_motorval[i]!=i_motorval[i])){
        i_motoron[i]=NXT_motoron[i];
        i_motorval[i]=NXT_motorval[i];
        if (i_motoron[i]<0){i_motoron[i]=0; NXT_motoron[i]=0;}
        if (i_motoron[i]>1){i_motoron[i]=1; NXT_motoron[i]=1;}
        if (i_motorval[i]<-100){i_motorval[i]=-100; NXT_motorval[i]=-100;}
        if (i_motorval[i]>100){i_motorval[i]=100; NXT_motorval[i]=100;}
        if (i_motoron[i]){ //motor on
          NXT_setoutputstate(i,i_motorval[i],5,0x01,0x00,0x20,0);
        } else { //motor off
          NXT_setoutputstate(i,i_motorval[i],0,0x00,0x00,0x00,0);
        }
      }
    }
    
    i_ready=1; //after first execution, signal startcommunication() that init finished
  }

  //make sure all motors are off before finishing
  for (i=0; i<3; i++){
    NXT_setoutputstate(i,0,0,0x00,0x00,0x00,0);
  }

  len=NXT_close();
  NXT_stop=0;
  i_ready=0;
  return(1);
}


DWORD WINAPI nxt_remote::NXT_loop(LPVOID lpParameter){
  nxt_remote *nr= (nxt_remote *) lpParameter;
  return(nr->nxt_internal());
}

void nxt_remote::initvariables(){
  int i;

  NXT_port=0;
  for (i=0; i<15; i++) nxtname[i]=0;
  for (i=0; i<8; i++) btaddress[i]=0;
  for (i=0; i<4; i++) i_sensoron[i]=0;     //all off
  for (i=0; i<4; i++) NXT_sensoron[i]=0;   //all off
  for (i=0; i<4; i++) i_sensortype[i]=0;   //NO_SENSOR
  for (i=0; i<4; i++) NXT_sensortype[i]=0; //NO_SENSOR
  for (i=0; i<4; i++) i_sensormode[i]=0;   //RAWMODE
  for (i=0; i<4; i++) NXT_sensormode[i]=0; //RAWMODE
  for (i=0; i<3; i++) i_motoron[i]=0;      //all motors off
  for (i=0; i<3; i++) NXT_motoron[i]=0;    //all motors off
  for (i=0; i<3; i++) i_motorval[i]=0;      //all motors power 0
  for (i=0; i<3; i++) NXT_motorval[i]=0;    //all motors power 0
  i_ready=0;
  NXT_error=0;
  NXT_stop=-1;
}

/////// PUBLIC ROUTINES


//************* CUSTOM ROUTINES ***************

//move forward for specific time
void nxt_remote::moveFwd(int time, int power)
{
	//Turning motors on
	cout<<"MOVE FOWARD"<<endl;
	this->NXT_motoron[0]=1;
	this->NXT_motoron[2]=1;

	//Setting the motors power/velocity
	this->NXT_motorval[0] = power;
	this->NXT_motorval[2] = power;

	Sleep(time);
}

//move forward for specific time
void nxt_remote::moveBack(int time, int power)
{
	//Turning motors on
	this->NXT_motoron[0]=1;
	this->NXT_motoron[2]=1;

	//Setting the motors power/velocity
	this->NXT_motorval[0] = -power;
	this->NXT_motorval[2] = -power;

	Sleep(time);
}




void nxt_remote::pointTurnLeft(int time, int power)
{
	//Turning motors on
	this->NXT_motoron[0]=1;
	this->NXT_motoron[2]=0;

	//Setting the motors power/velocity
	this->NXT_motorval[0] = power;

	Sleep(time);
}


void nxt_remote::pointTurnRight(int time, int power)
{
	//Turning motors on
	this->NXT_motoron[0]=0;
	this->NXT_motoron[2]=1;

	//Setting the motors power/velocity
	this->NXT_motorval[2] = power;

	Sleep(time);
}

void nxt_remote::swingTurnRight(int time, int power)
{
	//Turning motors on
	this->NXT_motoron[0]=1;
	this->NXT_motoron[2]=1;

	//Setting the motors power/velocity
	this->NXT_motorval[0] = -power;
	this->NXT_motorval[2] = power;

	Sleep(time);
}
void nxt_remote::swingTurnLeft(int time, int power)
{
	//Turning motors on
	this->NXT_motoron[0]=1;
	this->NXT_motoron[2]=1;

	//Setting the motors power/velocity
	this->NXT_motorval[0] = power;
	this->NXT_motorval[2] = -power;

	Sleep(time);
}

void nxt_remote::turnOffMotors()
{
	this->NXT_motoron[0]= 0;
	this->NXT_motoron[2]= 0;
}


//************* END CUSTOM ROUTINES ***********

nxt_remote::nxt_remote(){
  //int i;

  initvariables();
}

nxt_remote::~nxt_remote(){
}

  
int nxt_remote::startcommunication(char *in_portname){
  int i=0;
  while(in_portname[i]!=0){
    portname[i]=in_portname[i];
    i++;
  }
  portname[i]=0;
  //porttype=type;
  NXT_stop=1;
  CreateThread(NULL,0,&NXT_loop,this,0,&NXT_thread_id); //fork thread
  while(NXT_stop==1) Sleep(10); //wait until thread has been initialized
  if (NXT_stop==-1) return(0); //error during initialisation?
  while (i_ready==0) Sleep(10); //wait until end of first loop
  return(1);
}

int nxt_remote::stopcommunication(){
  int i;

  if (NXT_stop==-1) return(1); //no stopping necessary (either not initialized or initialization failed)
  NXT_stop=1; 
  i=0;
  while ((i<1000)&&(NXT_stop)){
    Sleep(10);  //wait until interface task has finished
    i++;
  }
  if (i==1000) return(0); //timeout after 10 sec
	return(1);
}
