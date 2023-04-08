/*****************************************************************************
* | File      	:   GUI_BMPfile.h
* | Author      :   Xingtao Zeng
* | Function    :   Hardware underlying interface
* | Info        :   
*****************************************************************************/

#include "GUI_BMPfile.h"
#include "GUI_Paint.h"
#include "Debug.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>	//exit()
#include <string.h> //memset()
#include <math.h> //memset()
#include <stdio.h>

UBYTE GUI_ReadBmp_65K(const char *path, UWORD Xstart, UWORD Ystart)
{
    FILE *fp;                     //Define a file pointer
    BMPFILEHEADER bmpFileHeader;  //Define a bmp file header structure
    BMPINFOHEADER bmpInfoHeader;  //Define a bmp info header structure
    
    // Binary file open
    if((fp = fopen(path, "rb")) == NULL) {
        Debug("Cann't open the file!\n");
        exit(0);
    }

    // Set the file pointer from the beginning
    fseek(fp, 0, SEEK_SET);
    fread(&bmpFileHeader, sizeof(BMPFILEHEADER), 1, fp);    //sizeof(BMPFILEHEADER) must be 14
    fread(&bmpInfoHeader, sizeof(BMPINFOHEADER), 1, fp);    //sizeof(BMPFILEHEADER) must be 50
    printf("pixel = %d * %d\r\n", bmpInfoHeader.biWidth, bmpInfoHeader.biHeight);

    UWORD Image_Width_Byte = bmpInfoHeader.biWidth * 2;
    UWORD Bmp_Width_Byte = bmpInfoHeader.biWidth * 2;
    UBYTE Image[Image_Width_Byte * bmpInfoHeader.biHeight];
    memset(Image, 0xFF, Image_Width_Byte * bmpInfoHeader.biHeight);

    // Determine if it is a monochrome bitmap
    int readbyte = bmpInfoHeader.biBitCount;
    printf("biBitCount = %d\r\n",readbyte);
    if(readbyte != 16){
        Debug("Bmp image is not a 65K-color bitmap!\n");
        exit(0);
    }
    // Read image data into the cache
    UWORD x, y;
    UBYTE Rdata;
    fseek(fp, bmpFileHeader.bOffset, SEEK_SET);
    
    for(y = 0; y < bmpInfoHeader.biHeight; y++) {//Total display column
        for(x = 0; x < Bmp_Width_Byte; x++) {//Show a line in the line
            if(fread((char *)&Rdata, 1, 1, fp) != 1) {
                perror("get bmpdata:\r\n");
                break;
            }
            Image[x + (bmpInfoHeader.biHeight-1 - y)*Image_Width_Byte] =  Rdata;
        }
    }
    fclose(fp);
    
    // Refresh the image to the display buffer based on the displayed orientation
    UWORD color;
    printf("bmpInfoHeader.biWidth = %d\r\n",bmpInfoHeader.biWidth);
    printf("bmpInfoHeader.biHeight = %d\r\n",bmpInfoHeader.biHeight);
    for(y = 0; y < bmpInfoHeader.biHeight; y++) {
        for(x = 0; x < bmpInfoHeader.biWidth; x++) {
            if(x > Paint.Width || y > Paint.Height) {
                break;
            }
			color = 0;
            color |= Image[x*2 + y*bmpInfoHeader.biWidth*2];
			color |= Image[x*2 + y*bmpInfoHeader.biWidth*2 + 1] << 8;
            Paint_SetPixel(Xstart + x, Ystart + y, color);
        }
    }
    return 0;
}

