#include "sys.h"
#include "app_speedgroup.h"
#include "app_max7456.h"


void app_init(void)
{
    max7456_init();
}

int main(void)
{   
    sys_init();
    app_init();
    while(1){
		start_task();
    }
}











