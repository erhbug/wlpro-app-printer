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
#include "printer.h"

#define PRINT 10
str_Printer printer;
strEtiqueta Etiqueta;
unsigned char Printbuffer[BYTES_PER_ROW];
char countSend=0;

void receiveSensorsValuesFromMCU(void){
	SerialRead(iInputSerialPort,(char *)&reportemcu,2);

	printer.cPaper=reportemcu.cresumen&0x03;         reportemcu.cresumen>>2; //b0 b1
	printer.bDoor =(bool)(reportemcu.cresumen&0x01); reportemcu.cresumen>>1; //b2
	printer.bTemp =(bool)(reportemcu.cresumen&0x01); reportemcu.cresumen>>1; //b3
	printer.cCMD  =reportemcu.cresumen&0x03;         reportemcu.cresumen>>2; //b4 b5 
}

char imprimir(void){
    FILE *fp;
	int sizeofpacket;
	char CMD=PRINT;
	char crcSoM;

	fp = fopen("./Ticket","r");
	puts("start\r\n"); /* prints Hello World */	   
	
	sizeofpacket = 14;
	fread(Printbuffer,sizeof(char),sizeofpacket,fp);               
	vAppPrintLine(Printbuffer,sizeofpacket);			  
	SerialRead(iInputSerialPort,(char *)&reportemcu,2);

	sizeofpacket=57;
	for(int a=0;a<800;a++){
		fread(Printbuffer,sizeof(char),sizeofpacket,fp);      
		Printbuffer[56]=23;
		crcSoM=vAppPrintLine(Printbuffer,sizeofpacket);
		receiveSensorsValuesFromMCU();
		if(crcSoM!=reportemcu.crc)
			printf("line=%d, crc_pc=%d, crc_mcu=%d\n",a,(int)crcSoM,(int)reportemcu.crc);
	} 
	fclose(fp);
	puts("End print"); 	  
	CMD=0; 

	return EXIT_SUCCESS;
}