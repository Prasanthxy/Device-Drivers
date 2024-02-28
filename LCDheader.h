#include<LPC21xx.H>
#include "Delay.h"
#define LCD_D 0xff<<0
#define Rs 1<<8
#define E 1<<9
void LCD_Config(void);
void LCD_Command(unsigned char);
void LCD_Data(unsigned char);
void LCD_String(unsigned char*);
void LCD_Integer(int);
void LCD_Float(float);

void LCD_Config(void)
{
	IODIR0|=LCD_D|Rs|E;		//P0.0 to P0.7 and P0.8,P0.9 as output pins
	LCD_Command(0x01);		//Clear the display
	LCD_Command(0x02);		//Return the cursor to home position
	LCD_Command(0x0c);		//Display ON and cursor OFF
	LCD_Command(0x38);		//Selecting 8-bit interfacing mode
	LCD_Command(0x80);		//Selecting DDRAM base address
}
void LCD_Command(unsigned char cmd)
{
	IOCLR0=LCD_D;
	IOSET0=cmd;
	IOCLR0=Rs;				//Rs as 0 for command register mode
	IOSET0=E;
	delay_milliseconds(2);	//Waiting for internal latching
	IOCLR0=E;
}
void LCD_Data(unsigned char d)
{
	IOCLR0=LCD_D;
	IOSET0=d;
	IOSET0=Rs;				//Rs as 1 for data register mode
	IOSET0=E;
	delay_milliseconds(2);
	IOCLR0=E;
}
void LCD_String(unsigned char*p)
{
	while(*p)
		LCD_Data(*p++);
}
void LCD_Integer(int n)
{
	unsigned char a[7];
	signed char i=0;
	if(n==0)
		LCD_Data('0');
	else
	{
		if(n<0)
		{
			LCD_Data('-');
			n=-n;
		}
		while(n!=0)
		{
			a[i++]=n%10;
			n=n/10;
		}
		for(i=i-1;i>=0;i--)
		LCD_Data(a[i]+48);
	}
}
void LCD_Float(float f)
{
	int temp=0;
	temp=f;
	LCD_Integer(temp);
	temp=(f-temp)*1000;
	LCD_Data('.');
	LCD_Integer(temp);
}
