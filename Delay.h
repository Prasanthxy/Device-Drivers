void delay_seconds(unsigned int s)
{
	T0PR=15000000-1;
	T0TCR=0x01;			//Enable timer
	while(T0TC<s);
	T0TCR=0x03;			//Enable and Reset the timer
	T0TCR=0x00;
}
void delay_milliseconds(unsigned int ms)
{
	T0PR=15000-1;
	T0TCR=0x01;
	while(T0TC<ms);
	T0TCR=0x03;
	T0TCR=0x00;
}
void delay_microseconds(unsigned int us)
{
	T0PR=15-1;
	T0TCR=0x01;
	while(T0TC<us);
	T0TCR=0x03;
	T0TCR=0x00;
}
