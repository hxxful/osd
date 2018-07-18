#ifndef SYS_PROTOCOL_H
#define SYS_PROTOCOL_H

#include <stdint.h>
extern uint8_t frame_size;
extern uint8_t frame_type;

#define FRAME_DRONE 0x01
#define FRAME_OTHER 0x02

extern uint8_t frame_recv_buf[];
extern uint8_t frame_send_buf[];

void sys_frame_parse(uint8_t ch);
void sys_frame_pack(uint8_t* buf, uint8_t type, uint8_t size);
int8_t sys_frame_read(uint8_t* buf, uint8_t type, uint8_t size);
int8_t sys_frame_write(uint8_t* buf, uint8_t type, uint8_t size);

#endif
