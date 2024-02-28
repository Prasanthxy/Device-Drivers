#include<LPC21xx.H>
#include "Delay.h"
#define LCD_D 0xf<<20
#define Rs 1<<17
#define Rw 1<<18
#define E 1<<19
void LCD_Config(void);
void LCD_Command(unsigned char);
void LCD_Data(unsigned char);
void LCD_String(unsigned char*);
void LCD_Integer(int);
void LCD_Float(float);

void LCD_Config(void)
{
	IODIR1|=LCD_D|Rs|Rw|E;		//P1.20 to P1.23 and P1.17,P1.18,P1.19 as output pins
	LCD_Command(0x01);		//Clear the display
	LCD_Command(0x02);		//Return the cursor to home position
	LCD_Command(0x0c);		//Display ON and cursor OFF
	LCD_Command(0x28);		//Selecting 4-bit interfacing mode
	LCD_Command(0x80);		//Selecting DDRAM base address
}
void LCD_Command(unsigned char cmd)
{
	IOPIN1=(cmd&0xf0)<<16;
	IOCLR1=Rs;            	//Rs as 0 for command register mode
	IOCLR1=Rw;
	IOSET1=E;
	delay_milliseconds(2);	//Waiting for internal latching
	IOCLR1=E;
	
	IOPIN1=(cmd&0x0f)<<20;
	IOCLR1=Rs;				       //Rs as 0 for command register mode
	IOCLR1=Rw;
	IOSET1=E;
	delay_milliseconds(2);	//Waiting for internal latching
	IOCLR1=E;
}
void LCD_Data(unsigned char d)
{
	IOPIN1=(d&0xf0)<<16;
	IOSET1=Rs;				//Rs as 1 for data register mode
	IOCLR1=Rw;
	IOSET1=E;
	delay_milliseconds(2);
	IOCLR1=E;
	
	IOPIN1=(d&0x0f)<<20;
	IOSET1=Rs;				//Rs as 1 for data register mode
	IOCLR1=Rw;
	IOSET1=E;
	delay_milliseconds(2);
	IOCLR1=E;
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
