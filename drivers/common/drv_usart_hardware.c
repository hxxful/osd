#include "sys_protocol.h"
#include "drv_common.h"
#include "drv_usart_hardware.h"

#define USART_WORDLENGTH            ((uint32_t)0x00000000)
#define USART_PARITY                ((uint32_t)0x00000000)
#define USART_MODE                  USART_CR1_RE | USART_CR1_TE
#define USART_HARDWAREFLOWCONTROL   ((uint32_t)0x00000000)

#define CR3_CLEAR_MASK              ((uint32_t)(USART_CR3_RTSE | USART_CR3_CTSE))
#define CR1_CLEAR_MASK              ((uint32_t)(USART_CR1_M | USART_CR1_PCE | \
                                                USART_CR1_PS | USART_CR1_TE | \
                                                USART_CR1_RE))
#define drv_irq_usart1_func         USART1_IRQHandler

uint8_t		txbuf[TXBUFCAP + 5];
uint32_t 	txpoint = 0;
uint32_t 	txtail = 0;
uint32_t 	arynum = 0;

void drv_usart1_hardware_init(uint32_t baudrate)
{    
    uint32_t divider = 0; 
    uint32_t apbclock = 0; 
    uint32_t tmpreg = 0;
    
    USART_TypeDef* USARTx = USART1;
    GPIO_TypeDef * GPIOx = GPIOA;
    
    /*开GPIOA时钟*/
    RCC->AHBENR |= 0x00020000;
    /*开USARAT1时钟*/
    RCC->APB2ENR |= 0x00004000;
    
    /*模式 复用模式 引脚2、3*/
    GPIOx->AFR[0] |= 0x00001100;
    GPIOx->MODER  |= 0x000000A0; 
    /*输出 上拉输出 引脚2、3*/
    GPIOx->OTYPER &= 0xFFFFFFF3;
    /*速度 高速输出 引脚2、3*/
    GPIOx->OSPEEDR |= 0x000000F0;
    /*方式 推挽上拉 引脚2、3*/
    GPIOx->PUPDR |= 0x00000050;
    
    /*复位串口*/
    RCC->APB2RSTR |= 1 << 14;
    /*停止复位*/
	RCC->APB2RSTR &= ~(1 << 14);

    /* Disable USART */
    USARTx->CR1 &= (uint32_t)~((uint32_t)USART_CR1_UE);
    
    /*---------------------------- USART CR2 Configuration -----------------------*/
    tmpreg = USARTx->CR2;
    /* Clear STOP[13:12] bits */
    tmpreg &= (uint32_t)~((uint32_t)USART_CR2_STOP);
  
    /* Configure the USART Stop Bits, Clock, CPOL, CPHA and LastBit --------------*/
    /* Set STOP[13:12] bits according to USART_StopBits value */
    tmpreg |= (uint32_t)0x00000000;
  
    /* Write to USART CR2 */
    USARTx->CR2 = tmpreg;
    
    /*---------------------------- USART CR1 Configuration -----------------------*/
    tmpreg = USARTx->CR1;
    /* Clear M, PCE, PS, TE and RE bits */
    tmpreg &= (uint32_t)~((uint32_t)CR1_CLEAR_MASK);

    /* Configure the USART Word Length, Parity and mode --------------------------*/
    /* Set the M bits according to USART_WordLength value */
    /* Set PCE and PS bits according to USART_Parity value */
    /* Set TE and RE bits according to USART_Mode value */
    tmpreg |= (uint32_t)(USART_WORDLENGTH | USART_PARITY | USART_MODE);

    /* Write to USART CR1 */
    USARTx->CR1 = tmpreg;
    
    /*---------------------------- USART CR3 Configuration -----------------------*/  
    tmpreg = USARTx->CR3;
    /* Clear CTSE and RTSE bits */
    tmpreg &= (uint32_t)~((uint32_t)CR3_CLEAR_MASK);

    /* Configure the USART HFC ---------------------------------------------------*/
    /* Set CTSE and RTSE bits according to USART_HardwareFlowControl value */
    tmpreg |= USART_HARDWAREFLOWCONTROL;

    /* Write to USART CR3 */
    USARTx->CR3 = tmpreg;

    /*---------------------------- USART BRR Configuration -----------------------*/
    /* Configure the USART Baud Rate -------------------------------------------*/
    apbclock = 48000000;

    /* Determine the integer part */
    if ((USARTx->CR1 & USART_CR1_OVER8) != 0) {
        /* (divider * 10) computing in case Oversampling mode is 8 Samples */
        divider = (uint32_t)((2 * apbclock) / baudrate);
        tmpreg  = (uint32_t)((2 * apbclock) % baudrate);
    } else {
        /* if ((USARTx->CR1 & CR1_OVER8_Set) == 0) */
        /* (divider * 10) computing in case Oversampling mode is 16 Samples */
        divider = (uint32_t)((apbclock) / baudrate);
        tmpreg  = (uint32_t)((apbclock) % baudrate);
    }

    /* round the divider : if fractional part i greater than 0.5 increment divider */
    if (tmpreg >=  baudrate / 2) {
        divider++;
    } 

    /* Implement the divider in case Oversampling mode is 8 Samples */
    if ((USARTx->CR1 & USART_CR1_OVER8) != 0) {
        /* get the LSB of divider and shift it to the right by 1 bit */
        tmpreg = (divider & (uint16_t)0x000F) >> 1;
        
        /* update the divider value */
        divider = (divider & (uint16_t)0xFFF0) | tmpreg;
    }

    /* Write to USART BRR */
    USARTx->BRR = (uint16_t)divider;
    
    /* Enable USART */
    USARTx->CR1 |= USART_CR1_UE;
    
    drv_nvic_init(USART1_IRQn, 3, ENABLE);
}

void drv_usart1_hardware_read(void)
{

}

void drv_usart1_hardware_write(uint8_t ch)
{
    USART1->TDR = (ch & (uint16_t)0x01FF);

}

void drv_irq_usart1_func(void)
{
    if(USART1->ISR & (1 << 6)) {
        USART1->ICR |= (1 << 6);
        if(0 != arynum) {
            USART1->TDR = (uint8_t)txbuf[txpoint];
            if(txpoint < TXBUFCAP - 1) {
                txpoint++;
            } else {
                txpoint = 0;
            }
            arynum--;
            if(0 == arynum) {
                txtail = txpoint;
            }
        }
    }

    if(USART1->ISR & (1 << 5)) {
        //USART1->ICR |= (1 << 5);
        sys_frame_parse(USART1->RDR);
    }
}

void drv_irq_usart1_enable(void)
{
    USART1->CR1 |= 1 << 5;
    USART1->CR1 |= 1 << 6;
}

void drv_irq_usart1_disable(void)
{
    USART1->CR1 &= ~(1 << 5);
    USART1->CR1 &= ~(1 << 6);
}

