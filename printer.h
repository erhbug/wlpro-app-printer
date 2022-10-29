#ifndef _PRINTER_H
#define _PRINTER_H    1

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

#define CMD_NULL 0
#define CMD_PRINT 1
#define CMD_FEED 2

#define FORDWARD 1
#define REVERSE 0

#define DOOR_CLOSE 0
#define DOOR_OPEN 1

//Estados de Sensor de papel
#define SIN_PAPEL 0
#define PAPEL_RESPALDO 1
#define PAPEL_ETIQUETA 2

#define BYTES_PER_ROW 56

typedef struct{
	bool bmode;//0 ticket 1 etiqueta
	char cCMD;
	bool bTemp;
	bool bDoor;
	char cPaper;
}str_Printer;
extern str_Printer printer;

typedef struct strEtiqueta{
	float flargo;//largo en mm
	float fgap;	//gap entre etiquetas en mm
	float fDistanciaSensorToSalida;//Distancia del Sensor a la salida de la etiqueta,  sugerido: 41 mm 
	float fDistanciaSensorToCabezal;//Distancia del sensor al cabezal, sugerido 29mm
}strEtiqueta;
extern strEtiqueta Etiqueta;

char imprimir(void);

#endif //_PRINTER_H
