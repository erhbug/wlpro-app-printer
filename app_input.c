/*-----------------------------------------------------------------------------*
 * serial.c                													   *
 * 		       	            FABRICANTES DE BÁSCULAS TORREY        			   *
 *		                        BASCULA W-LABEL-PRO               			   *
 *----------------------------------------------------------------------------*/

/*******************************************************************************
*                                INCLUDE FILES
*******************************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h> 
#include <pthread.h>
#include "app_input.h"
#include "./serial.h"

/*******************************************************************************
*                               GLOBAL VARIABLES                               *
*******************************************************************************/
pthread_mutex_t Mutex_Inputs;
strsensor sensor;

/*------------------------------------------------------------------------------
vAppOutLabel
------------------------------------------------------------------------------*/
void vAppOutLabel(void){
  char txt[]="#CMD03";   
  if(iInputSerialPort==0)vAppInputsOpen();
  pthread_mutex_lock(&Mutex_Inputs);
  SerialFlush(iInputSerialPort,TCIOFLUSH);
  for(int x=0;x<6;x++)
      SerialWrite(iInputSerialPort,&txt[x],1);
  SerialRead(iInputSerialPort,txt,1);
  pthread_mutex_unlock(&Mutex_Inputs);
  return txt[0];
}

/*******************************************************************************
*                               GLOBAL VARIABLES                               *
*******************************************************************************/
pthread_mutex_t Mutex_Inputs;
strsensor sensor;
strreportemcu reportemcu;

/*------------------------------------------------------------------------------
vAppOutLabel
------------------------------------------------------------------------------*/
void vAppSetLabelToPrint(void){
  char txt[]="#CMD04"; 
  char *ptr=&reportemcu;
  
  if(iInputSerialPort==0)vAppInputsOpen();
  pthread_mutex_lock(&Mutex_Inputs);
  SerialFlush(iInputSerialPort,TCIOFLUSH);
  for(int x=0;x<6;x++)
      SerialWrite(iInputSerialPort,&txt[x],1);
  //SerialRead(iInputSerialPort,txt,1);
  SerialRead(iInputSerialPort,ptr,sizeof(reportemcu));
  pthread_mutex_unlock(&Mutex_Inputs);
  return txt[0];
}


/*------------------------------------------------------------------------------
vAppFeedmm
------------------------------------------------------------------------------*/
void vAppFeedmm(int mm){
  char txt[]="#CMD010000"; 
  char *ptr= (char *)&mm;
  //char *ptr= (char *)&sensor;

  txt[6]=*(ptr++);
  txt[7]=*(ptr++);
  txt[8]=*(ptr++);
  txt[9]=*(ptr++);

  if(iInputSerialPort==0)vAppInputsOpen();
  pthread_mutex_lock(&Mutex_Inputs);
  SerialFlush(iInputSerialPort,TCIOFLUSH);

for(int x=0;x<10;x++)
  SerialWrite(iInputSerialPort,&txt[x],1);

  pthread_mutex_unlock(&Mutex_Inputs);
}

/*------------------------------------------------------------------------------
vAppPrintLine
------------------------------------------------------------------------------*/
char vAppPrintLine0(unsigned char *ptr, int lenght){
  if(iInputSerialPort==0)vAppInputsOpen();
  pthread_mutex_lock(&Mutex_Inputs);
  //sprintf(cmd,"Bp");
  SerialFlush(iInputSerialPort,TCIOFLUSH);
  //SerialWrite(iInputSerialPort,ptr,lenght);

  for(char x=0;x<lenght;x++){
    SerialWrite(iInputSerialPort,ptr++,1);
    //usleep(1);
  }
  pthread_mutex_unlock(&Mutex_Inputs);
  return 0;
}

char vAppPrintLine(unsigned char *ptr, int lenght){
  char crc=0;
  if(iInputSerialPort==0)vAppInputsOpen();
  pthread_mutex_lock(&Mutex_Inputs);
  SerialFlush(iInputSerialPort,TCIOFLUSH);  

  for(char x=0;x<lenght;x++){
     if(x<lenght-1){
      crc ^=  *ptr;
      SerialWrite(iInputSerialPort,ptr++,1);
     }
     else{
      crc=~crc;
      *ptr=crc;
      SerialWrite(iInputSerialPort,ptr,1);
     }
  }
  

  pthread_mutex_unlock(&Mutex_Inputs);
  return *ptr;
}
/*------------------------------------------------------------------------------
iAppInputFlgPrinted
------------------------------------------------------------------------------*/
int iAppPrintFlag(void){
  char data[8];
  int val = 0;
  if(iInputSerialPort==0)vAppInputsOpen();
  pthread_mutex_lock(&Mutex_Inputs);
  //SerialFlush(iInputSerialPort,TCIOFLUSH);
  //SerialWrite(iInputSerialPort,"fl\0",3);
  SerialRead(iInputSerialPort,&data[0],1);
  //if(SerialRead(iInputSerialPort,&data[0],1)>0){
    //val = data[0];
  //}
  pthread_mutex_unlock(&Mutex_Inputs);
  return val;
}

/*------------------------------------------------------------------------------
iAppInputFlgPrinted
------------------------------------------------------------------------------*/
int iAppReadSensors(void){
  char *ptr=(char*)&reportemcu;
  int val = 0;
  if(iInputSerialPort==0)vAppInputsOpen();
  pthread_mutex_lock(&Mutex_Inputs);
  SerialFlush(iInputSerialPort,TCIOFLUSH);
  SerialWrite(iInputSerialPort,"#CMD02",6);
  SerialRead(iInputSerialPort,ptr,sizeof(reportemcu));
  pthread_mutex_unlock(&Mutex_Inputs);
  return val;
}

/*------------------------------------------------------------------------------
vAppInputsInit
------------------------------------------------------------------------------*/
void vAppInputsOpen(void){
  //abrir puerto serial para inputs
  if(iInputSerialPort!=0)return;
  iInputSerialPort = SerialOpen(INPUT_PORT, O_RDWR | O_NOCTTY);
  if (iInputSerialPort < 0) printf( "%s open\n",INPUT_PORT);
  SerialSetting(iInputSerialPort,B1152000,0);//B921600//B1152000
  pthread_mutex_init(&Mutex_Inputs,NULL);
  usleep(10000);
}

/*------------------------------------------------------------------------------
vAppInputsClose
------------------------------------------------------------------------------*/
void vAppInputsClose(void){
  iInputSerialPort = 0;
  SerialClose(iInputSerialPort);
  pthread_mutex_destroy(&Mutex_Inputs);
}

/*------------------------------------------------------------------------------
end code
------------------------------------------------------------------------------*/
