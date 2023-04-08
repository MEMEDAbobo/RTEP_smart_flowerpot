/*****************************************************************************
* | File      	:   light.c
* | Author      :   xingtao Zeng
* | Function    :   Drive light module 
* | Info        :
******************************************************************************/

#include "light.h"
#include "test.h"
int readDigitalValue() {
    int value = digitalRead(DIGITAL_PIN);   // 读取数字输出引脚的值
    return value;
}

int readAnalogValue() {
    int value = analogRead(ANALOG_PIN);     // 读取模拟输出引脚的值
    return value;
}
