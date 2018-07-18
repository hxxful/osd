#include "sys.h"
#include "sys_api.h"
#include "sys_clock.h"
#include "sys_delay.h"

#include "drv_led.h"
#include "drv_usart_hardware.h"
#include "drv_timers.h"
#include "drv_w25qxx.h"
#include "drv_max7456.h"
#include "drv_dma.h"

/*系统时基 2ms*/
volatile uint32_t sys_tick = 0;
volatile uint8_t sys_speed_flag[SPEED_NUM] = {0};

void sys_init(void)
{
    sys_clock_init();
    sys_api_init();
	sys_delay_init();	
    drv_timer2_init();
	drv_usart1_hardware_init(115200);
    drv_led_init();
    drv_max7456_init();
	//drv_w25qxx_init();	
}

void task_null(void)
{

}



