#ifndef APP_MAX7456_H
#define APP_MAX7456_H

#include <stdint.h>

typedef struct {
	uint16_t drone_flytime;
	uint16_t drone_heading;
    uint16_t drone_pitch;
    uint16_t drone_roll;
	uint16_t drone_power;
	uint16_t drone_speed; 
    uint8_t drone_altitude;  
    uint8_t drone_rss;
} MAX7456_DATA;

extern MAX7456_DATA max7456_frame;

void max7456_offset(int8_t x, int8_t y);
void max7456_learn_fonts(void);
void max7456_draw_skyline(uint8_t x, uint8_t y, uint16_t roll, uint16_t pitch);
void max7456_draw_allchar(void);
void max7456_init(void);
void task_max7456_draw_osd(void);
extern uint8_t debug_data;

#endif
