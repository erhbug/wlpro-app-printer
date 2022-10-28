/*--------------------------------------------------------------------------------------*
 * app_input.h     					        			                                              *
 * 		       	            FABRICANTES DE BÁSCULAS TORREY                                *
 *      	    			      BASCULA W-LABEL-PRO	                                          *
 *--------------------------------------------------------------------------------------*/
#ifndef _API_INPUT_H
#define _API_INPUT_H    1

#define KEY_RECEIVE_BUFFER_SIZE 128


//#include "../app.h"

/****************************************************************************************
*                                              CONSTANTS
*****************************************************************************************/
//#define INPUT_PORT        SERIAL_7                        //  "/dev/ttymxc6"  MICRO STMicro teclado
#define INPUT_PORT      SERIAL_5                        //  "/dev/ttymxc4"  MICRO STMicro impresor
#define BACKLIGHT_ON      1
#define BACKLIGHT_OFF     0

#define DEF_OK 1
#define DEF_FAIL 0
#define DEF_NULL 0

int  iInputSerialPort;

typedef struct strsensor{
   char flgTemp;//Bandera que indica si la temp esta ok(0) alta temperatura(1)
	 char flgPaper;//Bander que indica el estado del papel; 0 Sin papel,  1 RESPALDO,         2 ETIQUETA	
   char flgDoor;//B3    Cabezal;       0 Cerrado,    1 abierto.		
   char status;

	
	float TemperatureLevelAlarm;//nivel al que se dispara la alarma de temperatura, recomendado 65°C
	int  nivelRespaldo;//180   1
	int  nivelEtiqueta;//13    2	
	
  float tempthermistor;//Temperatura de sensor
	int val_papersensor;//Valor del sensor de papel
}strsensor;
extern strsensor sensor;

typedef struct strreportemcu{
   char cresumen;	
   char crc;
  float fPosicionE1;//posicion de la etiqueta 1
  float fPosicionE2;//posicion de la etiqueta 1
}strreportemcu;
extern strreportemcu reportemcu;




int iAppReadSensors(void);
char vAppPrintLine(unsigned char *ptr, int lenght);
int iAppPrintFlag(void);
void vAppFeedmm(int mm);

void vAppInputsOpen(void);
void vAppInputsClose(void);
void vAppInputs(void);
void vAppSetLabelToPrint(void);

#endif //_API_INPUT_H
