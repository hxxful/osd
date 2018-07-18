#include "drv_common.h"
#include "drv_spi_hardware.h"

void drv_spi1_hardware_init(void)
{
	/*开GPIOA时钟*/
    RCC->AHBENR |= 0x00020000;
	/*开SPI1时钟*/
    RCC->APB2ENR |= 0x00001000;
    
	/*5、6、7引脚配置为 复用模式*/
    GPIOA->AFR[0] &= 0x000FFFFF;
    GPIOA->MODER  |= 0x0000A800;
	/*5、6、7引脚配置为 上拉输出*/
    GPIOA->OTYPER &= 0xFFFFFF1F;
	/*5、6、7引脚配置为 高速输出*/
    GPIOA->OSPEEDR &= 0xFFFF03FF;
    GPIOA->OSPEEDR |= 0x0000FC00;
	/*5、6、7引脚初始输 出高电平*/
    GPIOA->ODR |= 0x000000E0;
    
    /*SPI1配置*/
    SPI1->CR1 = 0x030C;
    SPI1->CR2 |= 0x0700;
    SPI1->CRCPR = 0x0007;
    /*使能SPI1接收DMA数据*/
    SPI1->CR2 |= 1 << 1;
    /*使能SPI1*/
    SPI1->CR1 |= 1 << 6;
}

static void spi_senddata8(SPI_TypeDef* SPIx, uint8_t data)
{
  uint32_t spixbase = 0x00;

  spixbase = (uint32_t)SPIx; 
  spixbase += 0x0C;
  
  *(uint8_t *) spixbase = data;
}

static uint8_t spi_receivedata8(SPI_TypeDef* SPIx)
{
  uint32_t spixbase = 0x00;
  
  spixbase = (uint32_t)SPIx; 
  spixbase += 0x0C;
  
  return *(uint8_t *) spixbase;
}

//static void spi_i2s_senddata16(SPI_TypeDef* SPIx, uint16_t data)
//{
//  SPIx->DR = (uint16_t)data;
//}

//uint16_t spi_i2s_receivedata16(SPI_TypeDef* SPIx)
//{
//  return SPIx->DR;
//}

uint8_t drv_spi1_hardware_read(void)
{
    uint8_t retry = 0;
    while (RESET == (SPI1->SR & SPI_SR_TXE)) {
        retry++;
        if(retry > 200) {
            return 0;
        }
    }
    spi_senddata8(SPI1, 0x00);

    retry = 0;
    while (RESET == (SPI1->SR & SPI_SR_RXNE)) {
        retry++;
        if(retry > 200) {
            return 0;
        }
    }
    return spi_receivedata8(SPI1);
}

void drv_spi1_hardware_write(uint8_t ch)
{
    uint8_t retry = 0;
    while (RESET == (SPI1->SR & SPI_SR_TXE)) {
        retry++;
        if(retry > 200) {
            return;
        }
    }
    spi_senddata8(SPI1, ch);
    
    retry = 0;
    while (RESET == (SPI1->SR & SPI_SR_RXNE)) {
        retry++;
        if(retry > 200) {
            return;
        }
    }
    spi_receivedata8(SPI1);
}

void drv_spi1_hardware_setspeed(uint8_t speed)
{
    /*四分频*/
    SPI1->CR1 &= 0xFFC7;
    SPI1->CR1 |= 0x0008;
    /*使能SPI1*/
    SPI1->CR1 |= 1 << 6;
}

