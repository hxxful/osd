#include "drv_common.h"
#include "drv_spi_hardware.h"
#include "drv_w25qxx.h"


#define	DRV_W25QXX_CS PAout(2)

void drv_w25qxx_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHBPeriphClockCmd(	RCC_AHBPeriph_GPIOA, ENABLE );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
    drv_spi1_hardware_init();
    drv_spi1_hardware_setspeed(SPI_BaudRatePrescaler_4);
}

void drv_w25qxx_connect(void)
{
    DRV_W25QXX_CS = 0;
}

void drv_w25qxx_disconnect(void)
{
    DRV_W25QXX_CS = 1;
}

uint8_t drv_w25qxx_write(uint8_t ch)
{
    drv_spi1_hardware_write(ch);
    return 0;
}

uint8_t drv_w25qxx_read(void)
{
    return drv_spi1_hardware_read();
}



