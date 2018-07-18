#include "sys.h"
#include "sys_delay.h"
#include "drv_systick.h"

void sys_delay_init(void)
{
    drv_systick_init();
}

void sys_delay_us(uint32_t nus)
{
	drv_systick_delay_us(nus);
}


void sys_delay_ms(uint16_t nms)
{
	drv_systick_delay_ms(nms);
}
