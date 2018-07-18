#ifndef SYS_API_H
#define SYS_API_H

#include <stdint.h>
extern void (*delay_us)(uint32_t);
extern void (*delay_ms)(uint16_t);

extern int8_t (*led_write)(uint8_t, uint8_t);
extern int8_t (*led_read)(uint8_t);

extern uint8_t (*spi1_write)(uint8_t);
extern uint8_t (*spi1_read)(void);

extern void (*w25qxx_connect)(void);
extern void (*w25qxx_disconnect)(void);
extern uint8_t (*w25qxx_read)(void);
extern uint8_t (*w25qxx_write)(uint8_t);

extern void (*max7456_connect)(void);
extern void (*max7456_disconnect)(void);
extern int8_t (*max7456_write)(uint8_t);
extern uint8_t (*max7456_read)(void);

extern int8_t (*frame_read)(uint8_t*, uint8_t, uint8_t);
extern int8_t (*frame_write)(uint8_t*, uint8_t, uint8_t);

extern void sys_api_init(void);


#endif
