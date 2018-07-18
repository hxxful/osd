#include <stdint.h>
#include "stm32f0xx.h"

#define ODR_OFFSET 0x14
#define IDR_OFFSET 0x10

#define GPIOA_ODR_Addr    (GPIOA_BASE + ODR_OFFSET)
#define GPIOB_ODR_Addr    (GPIOB_BASE + ODR_OFFSET)
#define GPIOC_ODR_Addr    (GPIOC_BASE + ODR_OFFSET)
#define GPIOD_ODR_Addr    (GPIOD_BASE + ODR_OFFSET)
#define GPIOE_ODR_Addr    (GPIOE_BASE + ODR_OFFSET)
#define GPIOF_ODR_Addr    (GPIOF_BASE + ODR_OFFSET) 
#define GPIOG_ODR_Addr    (GPIOG_BASE + ODR_OFFSET)  

#define GPIOA_IDR_Addr    (GPIOA_BASE + IDR_OFFSET)
#define GPIOB_IDR_Addr    (GPIOB_BASE + IDR_OFFSET)
#define GPIOC_IDR_Addr    (GPIOC_BASE + IDR_OFFSET)
#define GPIOD_IDR_Addr    (GPIOD_BASE + IDR_OFFSET)
#define GPIOE_IDR_Addr    (GPIOE_BASE + IDR_OFFSET)
#define GPIOF_IDR_Addr    (GPIOF_BASE + IDR_OFFSET)
#define GPIOG_IDR_Addr    (GPIOG_BASE + IDR_OFFSET)

/**********真位带操作*************/
//#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
//#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
//#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

/***********仿位带操作***********/
typedef struct {
    uint16_t bit0: 1;
    uint16_t bit1: 1;
    uint16_t bit2: 1;
    uint16_t bit3: 1;
    uint16_t bit4: 1;
    uint16_t bit5: 1;
    uint16_t bit6: 1;
    uint16_t bit7: 1;
    uint16_t bit8: 1;
    uint16_t bit9: 1;
    uint16_t bit10: 1;
    uint16_t bit11: 1;
    uint16_t bit12: 1;
    uint16_t bit13: 1;
    uint16_t bit14: 1;
    uint16_t bit15: 1;
}FAKE_BITBAND;
 
#define BITBAND(addr, bitnum) ((FAKE_BITBAND*)(addr))->bit##bitnum
#define BIT_ADDR(addr, bitnum)   BITBAND(addr, bitnum)




/**************不用修改********************/
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)

#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)

void drv_nvic_setvectortable(uint32_t NVIC_VectTab, uint32_t Offset);
void drv_nvic_prioritygroupconfig(uint8_t nvic_group);
void drv_nvic_init(uint8_t channel, uint8_t priority, FunctionalState cmd);
void drv_ex_nvic_config(uint8_t gpiox, uint8_t bitx, uint8_t trim);
void drv_rcc_deinit(void);

