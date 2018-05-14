//インクルードガード
#ifndef DEV_LCD_CUI_H
#define DEV_LCD_CUI_H

//インクルード
#include <stdio.h>

//構造体　宣言・定義
typedef union {
  unsigned char BYTE;
  struct {
    unsigned char B7:1;
    unsigned char B6:1;
    unsigned char B5:1;
    unsigned char B4:1;
    unsigned char B3:1;
    unsigned char B2:1;
    unsigned char B1:1;
    unsigned char B0:1;
  } BIT;
} _IOREG;

typedef union{
  unsigned char BYTE;
  struct  {
    unsigned char B7:1;
    unsigned char B6:1;
    unsigned char B5:1;
    unsigned char B4:1;
    unsigned char B3:1;
    unsigned char B2:1;
    unsigned char B1:1;
    unsigned char B0:1;
  } BIT;
} st_port;

typedef union {
  unsigned char BYTE;
  struct {
    unsigned char B7:1;
    unsigned char B6:1;
    unsigned char B5:1;
    unsigned char B4:1;
    unsigned char B3210:4;
  } BIT;
} st_lcd;

//仮想LCD定義
st_lcd LCD;

//自作関数定義
void LCD_initialize();
void lcd_out_8bit(unsigned char d);
void lcd_out_4bit(unsigned char d, unsigned char rs);
void LCDClear();
void LCDDisplay(unsigned char *str, int line);
void wait( unsigned int);
void wait20us();
void update();
void LCDcui_out(char);

//各種Define定義
#define LCD_E	LCD.BIT.B5
#define LCD_RS	LCD.BIT.B4
#define LCD_D	LCD.BIT.B3210

_IOREG P4DDR;
_IOREG P4DR;
_IOREG P4PCR;

_IOREG P5DDR;
_IOREG P5DR;
_IOREG P5PCR;

_IOREG P6DDR;
_IOREG P6DR;

unsigned char line[32];
int point;

void LCD_initialize(void)
{
  P4DDR.BYTE= 0xFF;
  P4DR.BYTE = 0x0F;

  wait(15);

  lcd_out_8bit(0x23);
  wait(5);

  lcd_out_8bit(0x23);
	wait(1);

	lcd_out_8bit(0x23);
	wait(1);

	lcd_out_8bit(0x22);
	wait(1);

	lcd_out_4bit(0x28, 0);
	wait(1);

	lcd_out_4bit(0x0C, 0);
	wait(1);

	lcd_out_4bit(0x06, 0);
	wait(1);

	lcd_out_4bit(0x01, 0);
	wait(2);
}

void lcd_out_8bit(unsigned char data)
{
  int i;
	LCD_RS = 0;
	LCD_E = 1;
	LCD.BYTE = data;
	wait(1);
	LCD_E = 0;
	wait(1);
  if(data == 0x01)for(i=0;i<32;i++)line[i];
  update();
}

void lcd_out_4bit(unsigned char data, unsigned char rs)
{
	LCD_RS = rs;
	LCD_D = (data >> 4) & 0x0F;
	LCD_E = 1;
	wait(1);
	LCD_E = 0;
	wait(1);

	LCD_RS = rs;
	LCD_D = data & 0x0F;
	LCD_E = 1;
	wait(1);
	LCD_E = 0;
	wait(1);

  if(rs == 1) LCDcui_out(data);
  update();
}

void LCDDisplay(unsigned char *str, int line)
{
	if (line == 1)  {
		lcd_out_4bit(0x80, 0);
    point = 0;
	} else {
		lcd_out_4bit(0xC0, 0);
    point = 16;
	}
	while (*str) {
		lcd_out_4bit(*str++, 1);
	}
}

void LCDClear()
{
	lcd_out_4bit(0x01,1);
	wait(2);
}

void wait20us(){
  unsigned int i,j;
  for(i=0;i<10;i++)for(j=0;j<1000;j++);
}

void wait( unsigned int ms )
{
  unsigned int i;

  for( i=ms * 50 ; i > 0 ; i-- ) wait20us();

}

void LCDcui_out(char c){
  line[point++] = c;
  point%=32;
}

void update(){
  int i;
  printf("\033[2J");
  for(i=0;i<16;i++)printf("%c",line[i]);
  puts("");
  for(i=0;i<16;i++)printf("%c",line[16+i]);
  puts("");
  for(i=0;i<16;i++)printf("-");
  puts("");
  printf("LED1:%c LED2:%c\n",((P4DR.BIT.B6)?'x':'o'),((P4DR.BIT.B7)?'x':'o'));
}

#endif
