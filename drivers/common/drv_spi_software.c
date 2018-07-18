#include "drv_common.h"
#include "drv_spi_software.h"

/*注意PORT_CLK调用函数也可能需要修改*/
#define PORT_CLK          RCC_AHBPeriph_GPIOA

/*SPI1引脚所属端口组*/
#define PORT_SPI1_CLK     GPIOA
#define PORT_SPI1_MISO    GPIOA
#define PORT_SPI1_MOSI    GPIOA

/*SPI1引脚*/
#define PIN_SPI1_CLK      GPIO_Pin_5
#define PIN_SPI1_MISO     GPIO_Pin_6
#define PIN_SPI1_MOSI     GPIO_Pin_7

/*SPI1引脚输入输出控制*/
#define SPI1_CLK          PAout(5)
#define SPI1_MISO         PAin(6)
#define SPI1_MOSI         PAout(7)

void drv_spi1_software_delay(void);

void drv_spi1_software_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHBPeriphClockCmd(PORT_CLK, ENABLE);


    GPIO_InitStructure.GPIO_Pin = PIN_SPI1_CLK;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PORT_SPI1_CLK, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = PIN_SPI1_MOSI;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(PORT_SPI1_MOSI, &GPIO_InitStructure);


    GPIO_InitStructure.GPIO_Pin = PIN_SPI1_MISO;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_Init(PORT_SPI1_MISO, &GPIO_InitStructure);

    GPIO_SetBits(PORT_SPI1_CLK, PIN_SPI1_CLK);
    GPIO_SetBits(PORT_SPI1_MOSI, PIN_SPI1_MOSI);
}

void drv_spi1_software_write(uint8_t ch)
{
    uint8_t i;

    for(i = 0; i < 8; i++) {
        SPI1_CLK = 0;
        drv_spi1_software_delay();

        if(ch & 0x80) {
            SPI1_MOSI = 1;
        } else {
            SPI1_MOSI = 0;
        }
        ch <<= 1;

        drv_spi1_software_delay();
        SPI1_CLK = 1;
        drv_spi1_software_delay();
    }

}

//uint8_t drv_spi1_software_read(void)
//{
//    uint8_t i;
//    uint8_t ch = 0;
//  
//    for(i = 0; i < 8; i++) {
//        SPI1_CLK = 0;
//        drv_spi1_software_delay();

//        ch <<= 1;
//        if(SPI1_MISO) {
//            ch |= 0x01;
//        }

//        SPI1_CLK = 1;
//        drv_spi1_software_delay();
//    }
//    return ch;
//}

uint8_t drv_spi1_software_read(void)
{
    uint8_t i;
    uint8_t ch = 0;
  
    SPI1_MOSI = 0;
    for(i = 0; i < 8; i++) {              
        ch <<= 1;
        SPI1_CLK = 1;
        drv_spi1_software_delay();
        ch += SPI1_MISO;
        SPI1_CLK = 0;
        drv_spi1_software_delay();
    }
    return ch;
}



void drv_spi1_software_delay(void)
{
    uint16_t i = 5;
    while(i--);
}

