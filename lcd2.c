#include "dev_lcd_cui.h"

#define LED1 P4DR.BIT.B6
#define LED2 P4DR.BIT.B7

#define DSW1 P5DR.BIT.B0
#define DSW2 P5DR.BIT.B1
#define DSW3 P5DR.BIT.B2
#define DSW4 P5DR.BIT.B3

#define SIZE 14

void swap(unsigned char* one,unsigned char* two,int i){
	char c;
	c=one[i];
	one[i]=two[i];
	two[i]=c;

}

int main(void)
{
	int i;
	unsigned char one[SIZE]="Seita Higashi";
	unsigned char two[SIZE]="             ";
	LCD_initialize();

	P4DDR.BYTE = 0xFF;

	P5DDR.BYTE = 0x00;
	P5PCR.BYTE = 0xFF;

	for(i=0;1;i++){
		LCDDisplay(one,1);
		LCDDisplay(two,2);
		i%=SIZE;
		swap(one,two,i);
		wait(5);
	}

	 return 0;

}
