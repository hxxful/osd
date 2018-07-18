#include <stdint.h>
#include "sys_api.h"
#include "sys_delay.h"
#include "sys_protocol.h"

#include "drv_led.h"
#include "drv_clock.h"
#include "drv_w25qxx.h"
#include "drv_max7456.h"

void (*delay_us)(uint32_t);
void (*delay_ms)(uint16_t);

int8_t (*led_write)(uint8_t n, uint8_t cmd);
int8_t (*led_read)(uint8_t);

void (*dev_max7456_init)(void);
void (*max7456_connect)(void);
void (*max7456_disconnect)(void);
int8_t (*max7456_write)(uint8_t);
uint8_t (*max7456_read)(void);


void (*w25qxx_connect)(void);
void (*w25qxx_disconnect)(void);
uint8_t (*w25qxx_read)(void);
uint8_t (*w25qxx_write)(uint8_t);


int8_t (*frame_read)(uint8_t*, uint8_t, uint8_t);
int8_t (*frame_write)(uint8_t*, uint8_t, uint8_t);



void sys_api_init(void)
{
	delay_us = sys_delay_us;
	delay_ms = sys_delay_ms;
    frame_read = sys_frame_read;
	frame_write = sys_frame_write;	

	max7456_connect = drv_max7456_connect;
	max7456_disconnect = drv_max7456_disconnect;	
	max7456_read = drv_max7456_read;
	max7456_write = drv_max7456_write;
    
    led_read = drv_led_read;
    led_write = drv_led_write;

//	w25qxx_connect = drv_w25qxx_connect;
//	w25qxx_disconnect = drv_w25qxx_disconnect;
//	w25qxx_read = drv_w25qxx_read;
//	w25qxx_write = drv_w25qxx_write;

	
}
