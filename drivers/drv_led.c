#include "drv_common.h"
#include "drv_led.h"

#define MAX_NUM_LED	1

#define LED0 PAout(8)
#define LED1 PAout(8)

void drv_led_init(void)
{
    /*开GPIOA时钟*/
    RCC->AHBENR |= 0x00020000;
    
    /*模式 复用模式 引脚8*/
    GPIOA->MODER  &= 0xFFFCFFFF;
    GPIOA->MODER  |= 0x00010000; 
    /*输出 上拉输出 引脚8*/
    GPIOA->OTYPER &= 0xFEFF;
    /*速度 高速输出 引脚88*/
    GPIOA->OSPEEDR &= 0xFFFCFFFF;
    GPIOA->OSPEEDR |= 0x00030000;
    /*方式 推挽上拉 引脚8*/
    GPIOA->PUPDR &= 0xFFFCFFFF;
    GPIOA->PUPDR |= 0x00010000;
}

int8_t drv_led_write(uint8_t n, uint8_t cmd)
{
    if(1 < cmd) {
        return -1;
    }

    if(MAX_NUM_LED < n) {
        return -2;
    }

    switch(n) {
    case 0:
        LED0 = cmd;
        break;
    case 1:
        LED1 = cmd;
        break;
    default:
        break;
    }

    return 0;
}

int8_t drv_led_read(uint8_t n)
{
    uint8_t res = 0x00;

    if(MAX_NUM_LED < n) {
        return -1;
    }

    switch(n) {
    case 0:
        res = LED0;
        break;
    case 1:
        res = LED1;
        break;
    default:
        break;
    }

    return (int8_t)res;
}


