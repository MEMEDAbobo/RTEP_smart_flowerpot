/*****************************************************************************
* | File      	:   OLED_show.c
* | Author      :   xingtao Zeng
* | Function    :   Display of plant status information, humidity, temperature, light intensity
* | Info        :
******************************************************************************/
#include "test.h"
#include "OLED.h"

/*******************************************************************************
function:
            Check internet connection
*******************************************************************************/
int CheckInternetConnection(void) {
    struct addrinfo hints;
    struct addrinfo *res;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int status = getaddrinfo("www.google.com", NULL, &hints, &res);
    if(status != 0) {
        return 0;
    }
    freeaddrinfo(res);
    return 1;
}

int OLED_show(void)
{
	printf("OLED showing\n");
	if(DEV_ModuleInit() != 0) {
		return -1;
	}
	
	if(USE_IIC) {
		printf("Only USE_SPI, Please revise DEV_Config.h !!!\r\n");
		return -1;
	}
	
	printf("OLED Init...\r\n");
	OLED_Init();
	DEV_Delay_ms(500);	
	// Create a new image cache
	UBYTE *BlackImage;
	UWORD Imagesize = (OLED_WIDTH*2) * OLED_HEIGHT;
	if((BlackImage = (UBYTE *)malloc(Imagesize + 300)) == NULL) {
			printf("Failed to apply for black memory...\r\n");
			return -1;
	}
	printf("Paint_NewImage\r\n");
	Paint_NewImage(BlackImage, OLED_WIDTH, OLED_HEIGHT, 0, BLACK);	
	Paint_SetScale(65);
	printf("Drawing\r\n");
	//
	Paint_SelectImage(BlackImage);
	DEV_Delay_ms(500);
	Paint_Clear(BLACK);
	// initialise the whole display
	//GUI_ReadBmp_65K("./pic/OLED.bmp", 0, 0);
	// Show image on page
	//OLED_Display(BlackImage);
	//DEV_Delay_ms(500);
	//Paint_Clear(BLACK);
	Paint_DrawString_EN(5, 16, "Temperature:", &Font16, WHITE, BLACK);
	Paint_DrawString_EN(5, 32, "Humidity:", &Font16, WHITE, BLACK);
	Paint_DrawString_EN(5, 48, "Light intensity:", &Font16, WHITE, BLACK);
	OLED_Display(BlackImage);
	DEV_Delay_ms(500);
	while(1) {
		PAINT_TIME local_time;
		pSTATUS plant_status;
		getPlantStatus(&plant_status);
		// display of time
		GetLocalTime(&local_time);
		Paint_DrawTime(0, 0, local_time, &Font12, BLACK, TIME_COLOR);
		OLED_SetWindow_Display(BlackImage,0, 0, 111, 15);
		
		//display of internet statu
		CheckInternetConnection()? GUI_ReadBmp_65K("./pic/internet_up.bmp", 0, 0): GUI_ReadBmp_65K("./pic/internet_down.bmp", 0, 0);
		OLED_SetWindow_Display(BlackImage,111, 0, 127, 15);
		DEV_Delay_ms(500);
		
		//display of plant information
		Paint_DrawNum(69, 16, plant_status->temperature, &Font16, 4, WHITE, BLACK);
		OLED_SetWindow_Display(BlackImage,69, 16, 127, 31);
		
		Paint_DrawNum(69, 32, plant_status->humidity, &Font16, 4, WHITE, BLACK);
		OLED_SetWindow_Display(BlackImage,69, 32, 127, 47);
		
		Paint_DrawNum(69, 48, plant_status->light_intensity, &Font16, 4, WHITE, BLACK);
		OLED_SetWindow_Display(BlackImage,69, 48, 127, 63);
		
		//display of the plant emoji
			
		
		
		
		OLED_1in5_rgb_Clear();
		
		
	}