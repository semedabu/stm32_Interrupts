#include "stm32l433xx.h"
void Config_IO(void);
void Config_Interrupt(void);


extern int cnt,j;
void Shift_Display_Right(int x);
void Cursor_To_Second_Row(void);
void EXTI0_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
void EXTI1_IRQHandler(void);
void Config_IO(void);
void Config_Interrupt(void);


void Delay_us(uint16_t us);
void Delay_ms(uint16_t ms);
void e_high();
void Clear_Lcd(void);
void e_low();

void rs_high();
void rs_low();
void pulse_e();

void send_LCD(char s);

void lcd_writeCMD(char m);
void lcd_writeDATA(char m);
void initializeLCD();
void send_string(char *buf);
void Config_Lcd (void);

