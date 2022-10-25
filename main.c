/*
 * Copyright (C) Torrey.
 *
 * Author: Eriberto Romero
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the PG_ORGANIZATION nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY	THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS-IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include "./app_input.h"
unsigned char Printbuffer[128];

char countSend=0;
int main(void)
{
	int x=0;
	FILE *fp;
	puts("Firmware Version D21PRINTR1904"); /* prints Hello World */

	fp = fopen("/usr/src/Ticket","r");
	puts("start\r\n"); /* prints Hello World */	   
 //vAppSetLabelToPrint();
    int sizeofpacket =14;
			  fread(Printbuffer,sizeof(char),sizeofpacket,fp);               
					 vAppPrintLine(Printbuffer,sizeofpacket);
	     	      x+=sizeofpacket;
				  
				  SerialRead(iInputSerialPort,(char *)&reportemcu,sizeof(strreportemcu));
                  //printf("0cresumen=%d,fPosicionE1=%f,fPosicionE2=%f\n",reportemcu.cresumen,reportemcu.fPosicionE1, reportemcu.fPosicionE2);
 sizeofpacket=57;
		for(int a=0;a<800;a++){
		fread(Printbuffer,sizeof(char),sizeofpacket,fp);      
		vAppPrintLine(Printbuffer,sizeofpacket);
	    x+=sizeofpacket;
		SerialRead(iInputSerialPort,(char *)&reportemcu,1);
		//printf("0cresumen=%d,fPosicionE1=%f,fPosicionE2=%f\n",reportemcu.cresumen,reportemcu.fPosicionE1, reportemcu.fPosicionE2);
		} 
 //vAppOutLabel();
 //sleep(3);
 fclose(fp);
 puts("End print"); 	    
 /* while(1){
	iAppReadSensors();
	printf("cresumen=%d,fPosicionE1=%f,fPosicionE2=%f\n",reportemcu.cresumen,reportemcu.fPosicionE1, reportemcu.fPosicionE2);
	usleep(100000);
  }  */  
  return 0;
}