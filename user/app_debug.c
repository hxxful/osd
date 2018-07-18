#include <stdio.h>
#include "sys.h"
#include "app_debug.h"
#include "app_max7456.h"
#include "sys_protocol.h"

void max7456_debug_read_frame(void)
{
    static uint8_t start_cnt = 0;
    if(0 == start_cnt) {
        printf("flytime   heading   pitch     roll      power     speed     altitude  rss\n");
        printf("**************************************************************************\n");
        start_cnt++;
    }
    if(0 < start_cnt) {
        printf("0x%04X    0x%04X    0x%04X    0x%04X    0x%04X    0x%04X    0x%02X      0x%02X\n", \
        max7456_frame.drone_flytime, \
        max7456_frame.drone_heading, \
        max7456_frame.drone_pitch, \
        max7456_frame.drone_roll, \
        max7456_frame.drone_power, \
        max7456_frame.drone_speed, \
        max7456_frame.drone_altitude, \
        max7456_frame.drone_rss
        );
        
        start_cnt++;
        if(12 == start_cnt) {
            start_cnt = 0;
            printf("\n\n");
        }

    }
}

void max7456_debug_write_frame(void)
{
	uint16_t i = 0;
	
	max7456_frame.drone_flytime = 120;
	max7456_frame.drone_altitude = 200;
	max7456_frame.drone_heading = 156;
	max7456_frame.drone_pitch = 50;
	max7456_frame.drone_roll = 50;
	max7456_frame.drone_power = 756;
	
	frame_write((uint8_t*)&max7456_frame, 0x01, sizeof(max7456_frame));
	for(i = 0; i < sizeof(max7456_frame) + 8; i++) {
		printf("%02X", frame_send_buf[i]);
	}
	printf("\n");
	
}

void max7456_debug(void)
{
	//max7456_debug_write_frame();
	max7456_debug_read_frame();
	
}

void task_debug(void)
{
	max7456_debug();
    //printf("debug_data:%d\n", debug_data);
   
}
