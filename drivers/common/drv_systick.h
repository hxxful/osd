#ifndef DRV_SYSTICK_H
#define DRV_SYSTICK_H

#include <stdint.h>
void drv_systick_init(void);
void drv_systick_delay_us(uint32_t nus);
void drv_systick_delay_ms(uint16_t nms);

#endif
