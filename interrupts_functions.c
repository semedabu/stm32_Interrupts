#include "stm32l433xx.h"
#include "config.h"
extern int cnt,j;
char interrupt_test[]="interrupt event";



//***************************************************************************************************
//***************************************************************************************************
void EXTI0_IRQHandler(void)
{

		if (!(GPIOA->IDR & (1<<0)) )
		{
			send_string(interrupt_test);
		}

		//Clear the EXTI pending bits
		NVIC_ClearPendingIRQ(EXTI3_IRQn);
		EXTI->PR1 |=(1<<0);
}

//***************************************************************************************************
//***************************************************************************************************

void EXTI15_10_IRQHandler(void)
{   
	  cnt++;
		j++;
	  send_string(interrupt_test);
	  Delay_ms(1000);
	Clear_Lcd();
		NVIC_ClearPendingIRQ(EXTI15_10_IRQn);               //Clear the EXTI pending bits
		EXTI->PR1 |=(1<<15);
}

//***************************************************************************************************
//***************************************************************************************************
void EXTI3_IRQHandler(void)
{   
	  cnt++;
		j++;
		NVIC_ClearPendingIRQ(EXTI1_IRQn);               //Clear the EXTI pending bits
		EXTI->PR1 |=(1<<3);
}

//***************************************************************************************************
//***************************************************************************************************

void EXTI9_5_IRQHandler(void)
{   
	  cnt++;
		j++;
	  send_string(interrupt_test);
	  Delay_ms(1000);
	  Clear_Lcd();
		NVIC_ClearPendingIRQ(EXTI9_5_IRQn);               //Clear the EXTI pending bits
		EXTI->PR1 |=(1<<9);
}
//***************************************************************************************************
//***************************************************************************************************
	
void Config_Interrupt(void)
{	
      GPIOB ->MODER   |=  GPIO_MODER_MODE9_0;               ///set GPIO2 as general output
      GPIOB ->MODER   &=  ~(GPIO_MODER_MODE9_1);
			GPIOB ->OTYPER  &=  ~(GPIO_OTYPER_OT_9);            ///push pull output type for GPIOA12
			GPIOB ->OSPEEDR |=  (GPIO_OSPEEDER_OSPEEDR9_0);       // high speed for GPPIOC12
			GPIOB ->OSPEEDR |=  (GPIO_OSPEEDER_OSPEEDR9_1);
			GPIOB ->PUPDR   &=  ~(GPIO_PUPDR_PUPDR9);             //NO PULL UP*/
	
	    GPIOC ->MODER   |=  GPIO_MODER_MODE14_0;               ///set GPIO2 as general output
      GPIOC ->MODER   &=  ~(GPIO_MODER_MODE14_1);
			GPIOC ->OTYPER  &=  ~(GPIO_OTYPER_OT_14);            ///push pull output type for GPIOA12
			GPIOC ->OSPEEDR |=  (GPIO_OSPEEDER_OSPEEDR14_0);       // high speed for GPPIOC12
			GPIOC ->OSPEEDR |=  (GPIO_OSPEEDER_OSPEEDR14_1);
			GPIOC ->PUPDR   |=  (GPIO_PUPDR_PUPDR14);             //NO PULL UP*/

	
	  SYSCFG->EXTICR[2] &= ~SYSCFG_EXTICR3_EXTI9;
	  SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI15_PB  ;
	  SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI14_PC  ;
	  SYSCFG->EXTICR[2] |= SYSCFG_EXTICR3_EXTI9_PB  ;
	
	  EXTI->IMR1   |= (1<<15);                          //interrupt source is unmaskrd
	  EXTI->EMR1   |=(1<<15);                              //Unmask interrupt line 15
		EXTI->FTSR1  |= (1<<15);                                   //falling edge line 15
	
	  EXTI->IMR1   |= (1<<6);                          //interrupt source is unmaskrd
	  EXTI->EMR1   |=(1<<6);                              //Unmask interrupt line 6
		EXTI->FTSR1  |= (1<<6);                                   //falling edge line 6
	
	  EXTI->IMR1   |= (1<<9);                          //interrupt source is unmaskrd
	  EXTI->EMR1   |=(1<<9);                              //Unmask interrupt line 15
		EXTI->FTSR1  |= (1<<9);                                   //falling edge line 15
	
	  EXTI->IMR1   |= (1<<14);                          //interrupt source is unmaskrd
	  EXTI->EMR1   |=(1<<14);                              //Unmask interrupt line 15
		EXTI->FTSR1  |= (1<<14);                                   //falling edge line 15
	  
	
		__enable_irq();                                      //enable interrupt
		NVIC_SetPriority(EXTI15_10_IRQn,4);                   //Set priority
    NVIC_ClearPendingIRQ(EXTI15_10_IRQn);                //clear pending  
	  NVIC_EnableIRQ(EXTI15_10_IRQn);   
		
		NVIC_SetPriority(EXTI9_5_IRQn,4);                   //clear pending
    NVIC_ClearPendingIRQ(EXTI9_5_IRQn);              //clear pending
		NVIC_EnableIRQ(EXTI9_5_IRQn);                   ///enable interrupt
		
}


