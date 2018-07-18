#ifndef SYS_H
#define SYS_H

#include <stdint.h>
#include "sys_api.h"

#define SPEED_NUM	5
#define TASK_NUM	3

extern volatile uint32_t sys_tick;
extern volatile uint8_t sys_speed_flag[];
extern void sys_init(void);
extern void start_task(void);
extern void task_null(void);

#endif
