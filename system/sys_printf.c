#include <stdio.h>
#include "sys_common.h"
#include "sys_delay.h"
#include "sys_printf.h"
#include "drv_usart_hardware.h"

int fputc(int ch, FILE *f)
{
    static int32_t firstone = 0;
    int32_t errtimes = 0;
    while( arynum >= TXBUFLIM ) {
        errtimes++;
        sys_delay_us(20);
        if(0 == errtimes % 20000L) {
            drv_usart1_hardware_write(ch);
        }
    }

    drv_irq_usart1_disable();

    if((arynum == 0) && (firstone == 0)) {
        drv_usart1_hardware_write(ch);
        firstone = 1;
    } else {
        firstone=0;
        arynum++;
        txbuf[txtail] = (uint8_t)ch;
        if(txtail < TXBUFCAP - 1)
            txtail++;
        else
            txtail=0;
    }
    drv_irq_usart1_enable();
    return ch;
}

#pragma import(__use_no_semihosting)
struct __FILE {
    int handle;
};
FILE __stdout;

void _sys_exit(int x)
{
    x = x;
}
