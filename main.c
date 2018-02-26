#include "stm32l433xx.h"
#include "config.h"


int cnt,i,j,time_cnt=2000;

void Delay_ms(uint16_t ms);

char test[]="interrupts project _____";
char b[7]={0x10,0x10,0x16,0x19,0x11,0x11,0x1E}; 
char c[]="Carrie";
char s[]="Semed";

 


 int main (void)
{
	
	RCC->APB1ENR1 |=(1<<4);              //TIM6 clock enabled		
	TIM6->PSC = 0;                       // f timer = fclk / 24000 => 1kHz
	TIM6->ARR = 0xFFf;
	TIM6->CR1 = TIM_CR1_CEN;   
	Config_Lcd();
	Config_Interrupt();
	
	
	while(1)
	{
		Delay_ms(1000);

		send_string(c);
		Cursor_To_Second_Row();
		send_string(s);
		Shift_Display_Right(9);
		Delay_ms(1000);
		Clear_Lcd();
	}
	
	return 0;
}


