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
#include <stdbool.h>
#include <string.h>
// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()
#include <pthread.h>
#include "./app_input.h"
#include "../wlpro-app-message-queue/mq_manager.h"
bool MsgPrintStart=0;



void complete(MQ_Message message) 
{

	char payload[MQ_STRING_SIZE];

	switch (message.type)
	{
		case MQ_TYPE_PRINT:

			printf("--------------------------------------------------------------------\n");
			sprintf(payload, "Payload -> %s\n", message.payload);
			printf(payload);
			MsgPrintStart=1;
			printf("--------------------------------------------------------------------\n");

		break;
		case MQ_TYPE_READ_SENSORS:

			printf("--------------------------------------------------------------------\n");
			printf("Getting all sensors status.\n");
			printf("--------------------------------------------------------------------\n");

			MQ_Message message;
			message.type = MQ_TYPE_SEND_SENSORS;
			sprintf(payload, "1,1,1,1");
			strcpy(message.payload, payload);

			MQ_sendMessage(message, MQ_KEY_PRINTER );

			printf("--------------------------------------------------------------------\n");
			printf("All sensors status sent.\n");
			printf("--------------------------------------------------------------------\n");

		break;
		case MQ_TYPE_FEED:

			printf("--------------------------------------------------------------------\n");
			printf("Feeding.\n");
			printf("--------------------------------------------------------------------\n");

		break;
		
		default:
		printf("No valid argument.");
		break;
	}

}

void *print()
{
     while (true) 
     {
        MQ_reciveMessage((long) MQ_TYPE_PRINT, MQ_KEY_OPERATION, complete);
     }
}

void *readSensors()
{
     while (true) 
     {
        MQ_reciveMessage((long) MQ_TYPE_READ_SENSORS, MQ_KEY_OPERATION, complete);
     }
}

void *printerApplication()
{
     while (true) 
     {
		if(MsgPrintStart==1){
	 		MsgPrintStart=0;
			imprimir();	
		}
     }
}

void *Feed()
{
     while (true) 
     {
		MQ_reciveMessage((long) MQ_TYPE_FEED, MQ_KEY_OPERATION, complete);              
     }
}

int main(void)
{
	pthread_t threadToPrint;
	pthread_t threadToReadSensors;
	pthread_t threadToPrinterApplication;
	pthread_t threadToFeed;

	puts("Firmware Version D21PRINTR1904"); /* prints Hello World */

	pthread_create( &threadToPrinterApplication, NULL, printerApplication, NULL);
	pthread_create( &threadToPrint, NULL, print, NULL);
	pthread_create( &threadToReadSensors, NULL, readSensors, NULL);
	pthread_create( &threadToFeed, NULL, Feed, NULL);
	
	pthread_join( threadToPrinterApplication, NULL);
  	pthread_join( threadToPrint, NULL);
	pthread_join( threadToReadSensors, NULL);
	pthread_join( threadToFeed, NULL);

  	return 0;
}