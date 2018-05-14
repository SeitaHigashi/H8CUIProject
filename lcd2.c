/*
 * H8/3069F LAN �վ�ɽ���ץ������� sample_lcd.c
 * �վ�ɽ������ʸ����ɽ���������̎ߎێ��ގ׎�
 * �����ѥ������� Ʊ�ǥ��쥯�ȥ��� rom_start.S,3069rom_hms.x,dev_lcd.h�����뤳��.
 * dev_lcd.h  �ǥХ����ե�������h�إå����Ȥ������Ѥ���.
 * ����dev_lcd.h�˾���������ɽ�����Ǥ����褦�˥ץ������ष�Ƥ����Τǰ�����
 * ���ꤹ ���С�ʸ�����վ��ξ����������饤����ɽ��.
 */

#include "dev_lcd_cui.h"

#define LED1 P4DR.BIT.B6
#define LED2 P4DR.BIT.B7

#define DSW1 P5DR.BIT.B0
#define DSW2 P5DR.BIT.B1
#define DSW3 P5DR.BIT.B2
#define DSW4 P5DR.BIT.B3
//static unsigned char str2[16]="";

#define SIZE 14

void swap(char* one,char* two,int i){
	char c;
	c=one[i];
	one[i]=two[i];
	two[i]=c;

}

int main(void)
{
	int i;
	char one[SIZE]="Seita Higashi";
	char two[SIZE]="             ";
	LCD_initialize();       //LCD�ν������� dev_lcd.h�˥ץ������व���Ƥ���.

	P4DDR.BYTE = 0xFF;		// PORT4����4�ӥåȽ��Ϥ�����.

	P5DDR.BYTE = 0x00;		// PORT5����4�ӥå����� ������.
	P5PCR.BYTE = 0xFF;		// PORT5���ץ륢�å�����.

	for(i=0;1;i++){
		LCDDisplay(one,1);
		LCDDisplay(two,2);
		i%=SIZE;
		swap(one,two,i);
		wait(5);
	}

	 return 0;

}
