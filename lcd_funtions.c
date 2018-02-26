#include "stm32l433xx.h"
#include "config.h"
void Cursor_To_Second_Row(void)
{
	
	lcd_writeCMD(0xc0);
}

void Shift_Display_Right(int x)
{
	int i;
	for(i=0;i<=x;i++)
	{
	lcd_writeCMD(0x1C);
	Delay_ms(500);
	}
	
	
}
void Delay_us(uint16_t us)
{
		TIM6->ARR = us*4;         //timer 3
		TIM6->CNT = 0;
		//while(TIM6->CNT <us){}
			while((TIM6->SR & TIM_SR_UIF)==0);
		TIM6->SR &= ~TIM_SR_UIF;
}

//***************************************************************************************************
//***************************************************************************************************

void Delay_ms(uint16_t ms)
{
		int i=0;
		for(i=0;i<ms;i++)
		Delay_us(1000);
}

//***************************************************************************************************
//***************************************************************************************************

void Config_IO(void)
	{  
	int j=2;
		
		  RCC->APB2ENR    |=(1<<0);                                //SYSCFG ENABLE               
			RCC->AHB2ENR    |=  RCC_AHB2ENR_GPIOBEN;
			RCC->AHB2ENR    |=  RCC_AHB2ENR_GPIOCEN;
		  RCC->AHB2ENR    |=  RCC_AHB2ENR_GPIOAEN;
		
//LCD R/S.................................................................................................
			GPIOC ->MODER   |=  GPIO_MODER_MODE13_0;               ///set GPIO13 as general output
			GPIOC ->MODER   &=  ~(GPIO_MODER_MODE13_1);
			GPIOC ->OTYPER  &=  ~(GPIO_OTYPER_OT_13);            ///push pull output type for GPIOC12
			GPIOC ->OSPEEDR |=  (GPIO_OSPEEDER_OSPEEDR13_0);       // high speed for GPPIOC12
			GPIOC ->OSPEEDR |=  (GPIO_OSPEEDER_OSPEEDR13_1);
			GPIOC ->PUPDR   &=  ~(GPIO_PUPDR_PUPDR13);             //NO PULL UP*/
//LCD e.................................................................................................
		GPIOC ->MODER   |=  (1<<8);                        //PC4 output mode
			GPIOC ->MODER   &= ~(1<<9); 
			GPIOC ->OTYPER  &= ~(1<<4);                         //open drain on PC4
			GPIOC ->OSPEEDR |= (1<<8);                         //PC4 high speed
			GPIOC ->OSPEEDR |= (1<<9); 
			GPIOC  ->PUPDR  &=~(0<<8);
			GPIOC  ->PUPDR  &=~(0<<9);
//Datat Pin4.................................................................................................			
			GPIOA ->MODER   |=  GPIO_MODER_MODE0_0;               ///set GPIO2 as general output
			GPIOA ->MODER   &=  ~(GPIO_MODER_MODE0_1);
			GPIOA ->OTYPER  &=  ~(GPIO_OTYPER_OT_0);            ///push pull output type for GPIOA12
			GPIOA ->OSPEEDR |=  (GPIO_OSPEEDER_OSPEEDR0_0);       // high speed for GPPIOC12
			GPIOA ->OSPEEDR |=  (GPIO_OSPEEDER_OSPEEDR0_1);
			GPIOA ->PUPDR   &=  ~(GPIO_PUPDR_PUPDR0);             //NO PULL UP*/
	//Datat Pin5.................................................................................................		
			GPIOC ->MODER   |=  GPIO_MODER_MODE1_0;               ///set GPIO2 as general output
			GPIOC ->MODER   &=  ~(GPIO_MODER_MODE1_1);
			GPIOC ->OTYPER  &=  ~(GPIO_OTYPER_OT_1);            ///push pull output type for GPIOC12
			GPIOC ->OSPEEDR |=  (GPIO_OSPEEDER_OSPEEDR1_0);       // high speed for GPPIOC12
			GPIOC ->OSPEEDR |=  (GPIO_OSPEEDER_OSPEEDR1_1);
			GPIOC ->PUPDR   &=  ~(GPIO_PUPDR_PUPDR1);             //NO PULL UP*/
		
		//Datat Pin6.................................................................................................		
		GPIOC ->MODER   |=  GPIO_MODER_MODE2_0;               ///set GPIO2 as general output
			GPIOC ->MODER   &=  ~(GPIO_MODER_MODE2_1);
			GPIOC ->OTYPER  &=  ~(GPIO_OTYPER_OT_2);            ///push pull output type for GPIOC12
			GPIOC ->OSPEEDR |=  (GPIO_OSPEEDER_OSPEEDR2_0);       // high speed for GPPIOC12
			GPIOC ->OSPEEDR |=  (GPIO_OSPEEDER_OSPEEDR2_1);
			GPIOC ->PUPDR   &=  ~(GPIO_PUPDR_PUPDR2);             //NO PULL UP*/
			//Datat Pin7.................................................................................................		
			GPIOA ->MODER   |=  GPIO_MODER_MODE2_0;               ///set GPIO2 as general output
			GPIOA ->MODER   &=  ~(GPIO_MODER_MODE2_1);
			GPIOA ->OTYPER  &=  ~(GPIO_OTYPER_OT_2);            ///push pull output type for GPIOA12
			GPIOA ->OSPEEDR |=  (GPIO_OSPEEDER_OSPEEDR2_0);       // high speed for GPPIOC12
			GPIOA ->OSPEEDR |=  (GPIO_OSPEEDER_OSPEEDR2_1);
			GPIOA ->PUPDR   &=  ~(GPIO_PUPDR_PUPDR2);             //NO PULL UP*/
			
		

	}
	

void e_high()
{
    GPIOC->ODR |=(1<<4);
}


//*********************************************************************************************************
//*************************************************************************************************************

void e_low()
{
    GPIOC->ODR &= ~(1<<4);
}

//*********************************************************************************************************
//*************************************************************************************************************

void rs_high()
{
    GPIOC->ODR |= (1<<13);
}

//*********************************************************************************************************
//*************************************************************************************************************

void rs_low()
{
    GPIOC->ODR &= ~(1<<13);
}

//*********************************************************************************************************
//*************************************************************************************************************
void pulse_e()
{
    e_high();
    Delay_us(10);
    e_low();
    Delay_us(10);
}

//*********************************************************************************************************
//*************************************************************************************************************
void Clear_Lcd(void)
{
	lcd_writeCMD(0x01);	
			
}
				
void send_LCD(char s)
{
   if(s&0x01)
			GPIOA->ODR|=  (1<<0);
	 else
		  GPIOA->ODR &= ~(1<<0);
	 
	 if((s>>1)&0x01)
			GPIOC->ODR|=  (1<<1);
	 else
		  GPIOC->ODR&= ~(1<<1);
	 
	 if(( (s>>2)&0x01))
			GPIOC->ODR|=  (1<<2);
	 else
			GPIOC->ODR&= ~(1<<2);
		
	 if(( (s>>3)&0x01))
				GPIOA->ODR|=  (1<<2);
	 else
				GPIOA->ODR&= ~(1<<2);
     
}

//*********************************************************************************************************
//*************************************************************************************************************

void lcd_writeCMD(char m)
{
    rs_low();
  
    send_LCD( m>>4);
     Delay_us(100);
    pulse_e();
   // m = m>>4;
    send_LCD(m);
    Delay_us(100);
     pulse_e();
}

//*********************************************************************************************************
//*************************************************************************************************************
void lcd_writeDATA(char m)
	{
   // if(m>=0&&m<=127){
    rs_high();
 
    send_LCD( m>>4);
		Delay_us(100);
    pulse_e();
   //m = m>>4;
   // while(_RB13);
    send_LCD(m);
     pulse_e();
    }

//*********************************************************************************************************
//*************************************************************************************************************
void initializeLCD()
	{
     Delay_ms(50);
 //   lcd_writeCMD(0x08);
    lcd_writeCMD(0x20);
  //   Delay_ms(50);
    lcd_writeCMD(0x28);
   Delay_ms(50);
      lcd_writeCMD(0x28);
     Delay_ms(50);
     lcd_writeCMD(0x06);
 Delay_ms(50);
             lcd_writeCMD(0x0C);
 Delay_ms(100);
      lcd_writeCMD(0x01);
     //  lcd_writeCMD(0x02);
    Delay_ms(5);
       
     // lcd_writeCMD(0x01);
       // lcd_writeCMD(0x80);
        //  lcd_writeCMD(0x04);
       Delay_ms(1000);
    
}

//*********************************************************************************************************
//*************************************************************************************************************

void send_string(char *buf)
{
    char *ptz;
    ptz =buf;
    while(*ptz)
		{
        lcd_writeDATA(*ptz);
        ptz++;
        Delay_us(100);
    }
}
//*********************************************************************************************************
//*************************************************************************************************************


void Config_Lcd (void)
{
	Config_IO();
	initializeLCD();
	
}