bug001: USART1发送中断不停进入
answer: 初始化发送时不要使能 USART_IT_TC 中断
		初始化接收时要使能 USART_IT_RXNE
    //USART_ITConfig(USART1, USART_IT_TC, ENABLE);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

bug002: 若打开USE_DMA_SPI_OSD时，实现MAX7456的DMA发送，此时DMA与SPI进行发送到MAX7456，在DMA中断(drv_irq_dma1_ch1_func)中关闭DMA与SPI，则只能发送三次便不能进入DMA中断
answer: 取消在DMA中断中调用关闭DMA和SPI片选，在drv_dma1_write中实现先关闭DMA，再配置DMA，再打开DMA则可以连续传输	
		但效果还没有直接使用SPI来进行发送显的流畅，具体原因暂未分析