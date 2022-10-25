/*-----------------------------------------------------------------------------*
 * serial.c                													   *
 * 		       	            FABRICANTES DE BÁSCULAS TORREY        			   *
 *		                        BASCULA W-LABEL-PRO               			   *
 *----------------------------------------------------------------------------*/

/*******************************************************************************
*                                INCLUDE FILES
*******************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <termios.h> 
#include "./serial.h"
#include "./app_input.h"

/*******************************************************************************
*                               GLOBAL VARIABLES                               *
*******************************************************************************/

/*------------------------------------------------------------------------------
SerialOpen
------------------------------------------------------------------------------*/
int SerialOpen(char *port,int flag){    
    return open(port,flag);;
}

/*------------------------------------------------------------------------------
SerialClose
------------------------------------------------------------------------------*/
int SerialClose(int port){
    if(port!=DEF_NULL)close(port);    
    return DEF_OK;
}

/*------------------------------------------------------------------------------
SerialFlush
------------------------------------------------------------------------------*/
int SerialFlush(int port,int flags){
  if(tcflush(port,flags)==-1){
    printf( "TCIOFLUSH error\n" );
    return DEF_FAIL;
  }
  return DEF_OK;
}

/*------------------------------------------------------------------------------
SerialSetting
------------------------------------------------------------------------------*/
int SerialSetting(int port,int speed,int timeout){
  struct termios tty;
  tty.c_cflag = CBAUD | CS8 | CLOCAL | CREAD;
  tty.c_iflag = IGNPAR;
  tty.c_oflag = 0;
  tty.c_lflag = 0;
  tty.c_cc[VMIN] =1;
  tty.c_cc[VTIME] = timeout;

  cfsetospeed(&tty,speed);
  cfsetispeed(&tty,speed);
  if(SerialFlush(port,TCIOFLUSH)==DEF_FAIL) return DEF_FAIL;
  if(tcsetattr(port,TCSANOW,&tty)==-1) return DEF_FAIL;
  return DEF_OK;
}

/*------------------------------------------------------------------------------
SerialWrite
------------------------------------------------------------------------------*/
int SerialWrite(int port,char *buffer,int bytes){    

  return write(port,buffer,bytes);
}

/*------------------------------------------------------------------------------
SerialRead
------------------------------------------------------------------------------*/
int SerialRead(int port,char *buffer,int bytes){    
    return read(port,buffer,bytes);
}

/*end code*/