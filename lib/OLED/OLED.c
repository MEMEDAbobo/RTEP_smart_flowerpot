/*****************************************************************************
* | File      	:   OLED.c
* | Function    :    OLED Module Drive function
* | Info        :
* -----------------------------------------------------------------------------

#include "OLED.h"
#include "stdio.h"

/*******************************************************************************
function:
            Hardware reset
*******************************************************************************/
static void OLED_Reset(void)
{
    OLED_RST_1;
    DEV_Delay_ms(100);
    OLED_RST_0;
    DEV_Delay_ms(100);
    OLED_RST_1;
    DEV_Delay_ms(100);
}

/*******************************************************************************
function:
            Write register address and data
*******************************************************************************/
static void OLED_WriteReg(uint8_t Reg)
{
#if USE_SPI
    OLED_DC_0;
    DEV_SPI_WriteByte(Reg);
#endif
}

static void OLED_WriteData(uint8_t Data)
{   
#if USE_SPI
    OLED_DC_1;
    DEV_SPI_WriteByte(Data);
#endif
}

/*******************************************************************************
function:
        Common register initialization
*******************************************************************************/
static void OLED_InitReg(void)
{
    OLED_WriteReg(0xfd);  // command lock
    OLED_WriteData(0x12);
    OLED_WriteReg(0xfd);  // command lock
    OLED_WriteData(0xB1);

    OLED_WriteReg(0xae);  // display off
    OLED_WriteReg(0xa4);  // Normal Display mode

    OLED_WriteReg(0x15);  //set column address
    OLED_WriteData(0x00);     //column address start 00
    OLED_WriteData(0x7f);     //column address end 95
    OLED_WriteReg(0x75);  //set row address
    OLED_WriteData(0x00);     //row address start 00
    OLED_WriteData(0x7f);     //row address end 63    

    OLED_WriteReg(0xB3);
    OLED_WriteData(0xF1);

    OLED_WriteReg(0xCA);  
    OLED_WriteData(0x7F);

    OLED_WriteReg(0xa0);  //set re-map & data format
    OLED_WriteData(0x74);     //Horizontal address increment

    OLED_WriteReg(0xa1);  //set display start line
    OLED_WriteData(0x00);     //start 00 line

    OLED_WriteReg(0xa2);  //set display offset
    OLED_WriteData(0x00);

    OLED_WriteReg(0xAB);  
    OLED_WriteReg(0x01);  

    OLED_WriteReg(0xB4);  
    OLED_WriteData(0xA0);   
    OLED_WriteData(0xB5);  
    OLED_WriteData(0x55);    

    OLED_WriteReg(0xC1);  
    OLED_WriteData(0xC8); 
    OLED_WriteData(0x80);
    OLED_WriteData(0xC0);

    OLED_WriteReg(0xC7);  
    OLED_WriteData(0x0F);

    OLED_WriteReg(0xB1);  
    OLED_WriteData(0x32);

    OLED_WriteReg(0xB2);  
    OLED_WriteData(0xA4);
    OLED_WriteData(0x00);
    OLED_WriteData(0x00);

    OLED_WriteReg(0xBB);  
    OLED_WriteData(0x17);

    OLED_WriteReg(0xB6);
    OLED_WriteData(0x01);

    OLED_WriteReg(0xBE);
    OLED_WriteData(0x05);

    OLED_WriteReg(0xA6);
}

/********************************************************************************
function:
            initialization
********************************************************************************/
void OLED_Init(void)
{
    //Hardware reset
    OLED_Reset();

    //Set the initialization register
    OLED_InitReg();
    DEV_Delay_ms(200);

    //Turn on the OLED display
    OLED_WriteReg(0xAF);
}

/********************************************************************************
function:
            Clear screen
********************************************************************************/
void OLED_Clear(void)
{
    UWORD i;

    OLED_WriteReg(0x15);
    OLED_WriteData(0);
    OLED_WriteData(127);
    OLED_WriteReg(0x75);
    OLED_WriteData(0);
    OLED_WriteData(127);
    // fill!
    OLED_WriteReg(0x5C);

    for(i=0; i<OLED_WIDTH*OLED_HEIGHT*2; i++){
        OLED_WriteData(0x00);
    }
}

/********************************************************************************
function:   Set the drawing area
********************************************************************************/
void OLED_SetWindow(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
    // 设置列地址范围
    OLED_WriteReg(0x15); // column address set
    OLED_WriteData(x1);    // start column
    OLED_WriteData(x2);    // end column

    // 设置行地址范围
    OLED_WriteReg(0x75);  // page address set
    OLED_WriteData(y1);    // start page
    OLED_WriteData(y2);    // end page
}

/********************************************************************************
function:   Update all memory to OLED
********************************************************************************/
void OLED_Display(UBYTE *Image)
{
    UWORD i, j, temp;

    OLED_WriteReg(0x15);
    OLED_WriteData(0);
    OLED_WriteData(127);
    OLED_WriteReg(0x75);
    OLED_WriteData(0);
    OLED_WriteData(127);
    // fill!
    OLED_WriteReg(0x5C);   
     
    for(i=0; i<OLED_HEIGHT; i++)
        for(j=0; j<OLED_WIDTH*2; j++)
        {
            temp = Image[j + i*256];
            OLED_WriteData(temp);
        }
}
/********************************************************************************
function:   Updates memory to OLED based on Function OLED_SetWindow
********************************************************************************/
void OLED_SetWindow_Display(UBYTE *Image, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
	{
		UWORD i, j, temp;
		UWORD width = x2 - x1;
		UWORD height = y2 - y1;
		UWORD start_index = x1 + y1 * OLED_WIDTH;
		UWORD end_index = x2 + y2 * OLED_WIDTH;
		// 设置列地址范围
		OLED_WriteReg(0x15); // column address set
		OLED_WriteData(x1);    // start column
		OLED_WriteData(x2);    // end column

		// 设置行地址范围
		OLED_WriteReg(0x75);  // page address set
		OLED_WriteData(y1);    // start page
		OLED_WriteData(y2);    // end page
		// fill!
		OLED_WriteReg(0x5C);   
		 
		for (i = start_index; i < end_index; i++) {
			if (i >= start_index + width && (i - start_index) % OLED_WIDTH == 0) {
				i = i + OLED_WIDTH - width;
			}

			if (i >= start_index && i < end_index) {
				temp = Image[i];
				OLED_WriteData(temp);
			}
		}
	}

