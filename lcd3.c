#include "dev_lcd_cui.h"

#define LED1 P4DR.BIT.B6
#define LED2 P4DR.BIT.B7

#define DSW1 P5DR.BIT.B0
#define DSW2 P5DR.BIT.B1
#define DSW3 P5DR.BIT.B2//
#define DSW4 P5DR.BIT.B3

int main(void)
{
	LCD_initialize();

	P4DDR.BYTE = 0xFF;

	P5DDR.BYTE = 0x00;
	P5PCR.BYTE = 0xFF;

	while(1){
	if(DSW1 == 1)LCDDisplay("1",1);
	else if(DSW2==1)LCDDisplay("2",1);
	else if(DSW3==1)LCDDisplay("3",1);
	else if(DSW4==1)LCDDisplay("4",1);
	else LCDDisplay("None",1);
	}

	 return 0;

}
