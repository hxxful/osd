#include "drv_common.h"
#include "drv_systick.h"

#define drv_systick_irq_func SysTick_Handler

static uint8_t  fac_us = 0;
static uint16_t fac_ms = 0;

#define HCLK_DIV8 0xFFFFFFFB
void drv_systick_init(void)
{
    SysTick->CTRL &= HCLK_DIV8;
    fac_us = 48000000/8000000;
    fac_ms = (uint16_t)fac_us * 1000;
}

void drv_systick_irq_func(void)
{

}

void drv_systick_delay_us(uint32_t nus)
{
    uint32_t tmp;
    SysTick->LOAD = (uint32_t)nus*fac_us;
    SysTick->VAL = 0x00;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    do {
        tmp = SysTick->CTRL;
    } while(tmp & 0x01 && !(tmp & (1 << 16)));
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL = 0X00;
}

void drv_systick_delay_ms(uint16_t nms)
{
    uint32_t tmp;
    SysTick->LOAD = (uint32_t)nms * fac_ms;
    SysTick->VAL = 0x00;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
    do {
        tmp = SysTick->CTRL;
    } while(tmp & 0x01 && !(tmp & (1 << 16)));
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL = 0X00;
}


