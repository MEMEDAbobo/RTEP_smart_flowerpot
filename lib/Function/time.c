/*****************************************************************************
* | File      	:   OLED_show.c
* | Author      :   xingtao Zeng
* | Function    :   Display of plant status information, humidity, temperature, light intensity
* | Info        :
******************************************************************************/
#include "test.h"
#include "time.h"


/*******************************************************************************
function:
            Get local time
*******************************************************************************/
void GetLocalTime(PAINT_TIME *time) {
    time_t now;
    struct tm *local;

    time(&now);
    local = localtime(&now);

    // 提取需要的时间信息
    time->Hour = local->tm_hour;
    time->Min = local->tm_min;
	time->Sec = local->tm_sec;
}
