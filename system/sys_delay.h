#ifndef SYS_DELAY_H
#define SYS_DELAY_H

#include <stdint.h>
void sys_delay_init(void);
void sys_delay_us(uint32_t nus);
void sys_delay_ms(uint16_t nms);

#endif

