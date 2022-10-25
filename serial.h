/*--------------------------------------------------------------------------------------*
 * serial.h        					        			                                              *
 * 		       	            FABRICANTES DE BÁSCULAS TORREY                                *
 *      	    			BASCULA W-LABEL-PRO			                                            *
 *--------------------------------------------------------------------------------------*/
#ifndef _SERIAL_H
#define _SERIAL_H    1

/****************************************************************************************
*                                              CONSTANTS
*****************************************************************************************/

/* Canales */
#define SERIAL_1    "/dev/ttymxc0"
#define SERIAL_2    "/dev/ttymxc1"
#define SERIAL_3    "/dev/ttymxc2"
#define SERIAL_4    "/dev/ttymxc3"
#define SERIAL_5    "/dev/ttymxc4"
#define SERIAL_6    "/dev/ttymxc5"
#define SERIAL_7    "/dev/ttymxc6"
#define SERIAL_8    "/dev/ttymxc7"

#define NONE        0x80
#define EVEN        0x01

int SerialOpen(char*,int);
int SerialClose(int);
int SerialFlush(int,int);
int SerialSetting(int,int,int);
int SerialWrite(int,char*,int);
int SerialRead(int,char*,int);


#endif //_SERIAL_H
