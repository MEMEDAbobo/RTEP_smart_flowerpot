#include "test.h"


void  Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:exit\r\n");
    DEV_ModuleExit();

    exit(0);
}



int main()
{
	signal(SIGINT, Handler);
    OLED_show();
	
}
