#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <pthread.h>
#include "app_input.h"
//#include "../wlpro-app-message-queue/mq_manager.h"
#define PRINT 10
unsigned char Printbuffer[128];
char countSend=0;

char imprimir(void){
    FILE *fp;
	int sizeofpacket;
	char CMD=PRINT;
	char crc;

	fp = fopen("./Ticket","r");
	puts("start\r\n"); /* prints Hello World */	   
	
	sizeofpacket =14;
	fread(Printbuffer,sizeof(char),sizeofpacket,fp);               
	vAppPrintLine(Printbuffer,sizeofpacket);			  
	SerialRead(iInputSerialPort,(char *)&reportemcu,2);

	sizeofpacket=57;
	for(int a=0;a<800;a++){
		fread(Printbuffer,sizeof(char),sizeofpacket,fp);      
		Printbuffer[56]=23;
		crc=vAppPrintLine(Printbuffer,sizeofpacket);
		SerialRead(iInputSerialPort,(char *)&reportemcu,2);
		if(crc!=reportemcu.crc)
			printf("line=%d, crc_pc=%d, crc_mcu=%d\n",a,(int)crc,(int)reportemcu.crc);
	} 
	fclose(fp);
	puts("End print"); 	  
	CMD=0; 

}