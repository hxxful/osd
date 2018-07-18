#include <string.h>
#include "sys.h"
#include "sys_protocol.h"

#define FRAME_MAX_SIZE  50

#define FRAME_HEAD0 0XFC
#define FRAME_HEAD1 0XFC
#define FRAME_HEAD2 0XFC
#define FRAME_HEAD3 0XFC

uint8_t frame_recv_buf[FRAME_MAX_SIZE] = {0};
uint8_t frame_send_buf[FRAME_MAX_SIZE] = {0};
uint8_t frame_head_pointer = 0;
uint8_t frame_body_pointer = 0;
uint8_t frame_valid_flag = 0;
uint8_t frame_size = 0;
uint8_t frame_type = 0;
uint16_t frame_check = 0;
uint16_t frame_calcu = 0;


static void sys_frame_parse_head(uint8_t ch)
{
    if(0 == frame_head_pointer) {
        if(FRAME_HEAD0 == ch) {
            frame_head_pointer++;
            return;
        } else {
            frame_head_pointer = 0;
            return;
        }    
    }
    
    if(1 == frame_head_pointer) {
        if(FRAME_HEAD1 == ch) {
            frame_head_pointer++;
            return;
        } else {
            frame_head_pointer = 0;
            return;
        }
    }
    
    if(2 == frame_head_pointer) {
        if(FRAME_HEAD2 == ch) {
            frame_head_pointer++;
            return;
        } else {
            frame_head_pointer = 0;
            return;
        }
    }
    
    if(3 == frame_head_pointer) {
        if(FRAME_HEAD3 == ch) {
            frame_head_pointer++;
            frame_body_pointer++;
            return;
        } else {
            frame_head_pointer = 0;
            return;
        }
    }
}

static void sys_frame_pasre_body(uint8_t ch)
{    
    if(1 == frame_body_pointer) {
        frame_type = ch;        
        frame_recv_buf[frame_body_pointer - 1] = ch;
        frame_body_pointer++;
        return;
    }
    
    if(2 == frame_body_pointer) {
        frame_size = ch;
        frame_recv_buf[frame_body_pointer - 1] = ch;
        frame_body_pointer++;
        return;
    }
    
    if((3 <= frame_body_pointer) && (FRAME_MAX_SIZE >= frame_body_pointer)) {
        frame_recv_buf[frame_body_pointer - 1] = ch;              
        if(frame_size >= (frame_body_pointer - 2)) {
            frame_calcu += ch;
        } else if(frame_size == (frame_body_pointer - 4)){
            frame_check = frame_recv_buf[frame_body_pointer - 1] << 8;
            frame_check |= frame_recv_buf[frame_body_pointer - 2];
            if(frame_calcu == frame_check) {
                frame_valid_flag = 1;
            } else {
                frame_valid_flag = 0;                
            }
            frame_head_pointer = 0;
            frame_body_pointer = 0;
            frame_calcu = 0;
            frame_check = 0;
            return;
        }
        frame_body_pointer++; 
        return;
    }
}

void sys_frame_parse(uint8_t ch)
{  
    if(4 > frame_head_pointer) {
        sys_frame_parse_head(ch);
    } else {
        sys_frame_pasre_body(ch);
    }   
}

int8_t sys_frame_read(uint8_t* buf, uint8_t type, uint8_t size)
{
    if((size <= frame_size) && (1 == frame_valid_flag) && (frame_type == type)) {
        memcpy((void*)buf, (const void*)&frame_recv_buf[2], size);
        frame_valid_flag = 0;
        return 0;
    } else {
        return -1;
    }
}



void sys_frame_pack_head(void)
{
    frame_send_buf[0] = FRAME_HEAD0;
    frame_send_buf[1] = FRAME_HEAD1;
    frame_send_buf[2] = FRAME_HEAD2;
    frame_send_buf[3] = FRAME_HEAD3;
}

void sys_frame_pack_body(uint8_t* buf, uint8_t type, uint8_t size)
{
    uint8_t i = 0;
    frame_send_buf[4] = type;
    frame_send_buf[5] = size;
    if((FRAME_MAX_SIZE - 8) >= size) {
        for(i = 0; i < size; i++) {
            frame_send_buf[6 + i] = buf[i];
            frame_check += buf[i];
        } 
        frame_send_buf[6 + i] = frame_check;
        frame_send_buf[7 + i] = frame_check >> 8;
    }
    frame_check = 0;
}

void sys_frame_pack(uint8_t* buf, uint8_t type, uint8_t size)
{
    sys_frame_pack_head();
    sys_frame_pack_body(buf, type, size);
}

int8_t sys_frame_write(uint8_t* buf, uint8_t type, uint8_t size)
{
    sys_frame_pack(buf, type, size);
    return 0;
}
