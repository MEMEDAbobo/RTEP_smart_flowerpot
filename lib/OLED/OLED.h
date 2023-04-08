#ifndef __OLED_1IN5_RGB_H
#define __OLED_1IN5_RGB_H		


#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <time.h>
#include <wiringPi.h>
#include "DEV_Config.h"

#define OLED_WIDTH  128//OLED width
#define OLED_HEIGHT 128 //OLED height

/********************************************************************************
function:	
		Define the full screen height length of the display
********************************************************************************/

int CheckInternetConnection(void);
int OLED_show(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_Display(UBYTE *Image);
void OLED_Display(UBYTE *Image, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

typedef struct {
	float temperature;
	float humidity;
	float light_intensity;
	} pSTATUS;
extern pSTATUS pstatus;




#endif  