# include <lpc214x.h>
# define RS 16
# define EN 18
# include "delay.h"
void command(char);
void data(char);
void init(void);
void string(char *);
void number(unsigned int);
char pin[]={19,20,21,22};
char value[]={0x10,0x20,0x40,0x80};
int t=0;
int main()
{ int s=0;
	PINSEL0=0;
	IO1DIR=1<<16|1<<17|1<<18|1<<19;
	init();
	command(0x85);
	string("BATHROOM");
		IO1SET=1<<16|1<<17|1<<18|1<<19;
	while(1)
	{
		
		if(IO0PIN&(1<<0))
		{
			if(s==0)
			{
				//IO0SET=1<<15;
				command(0xC5);
				string("Person IN!");
				s=1;
			}
			else
			{
			//	IO0CLR=1<<15;
				command(0xC5);
				string("Person OUT!");
				s=0;
			}
		 while(IO0PIN &(1<<0));
			delay(1000);
}
		}
	}
void command(char x)
{
	int i;
	char y;
	    
	for(i=0;i<=3;i++)
	{
		y=x & value[i];
		if(y!=0)
		{
			IO0SET=1<<pin[i];
		}
		else
			{
				IO0CLR=1<<pin[i];
		  }
			
	}
    	IO0CLR=1<<RS;
			IO0SET=1<<EN;
			delay(10);
			IO0CLR=1<<EN;
		for(i=0;i<=3;i++)
	{
		y=(x<<4) & value[i];// shifting lower to upper nibble
		if(y!=0)
		{
			IO0SET=1<<pin[i];
		}
		else
			{
				IO0CLR=1<<pin[i];
		  }
	}
	IO0CLR=1<<RS;
			IO0SET=1<<EN;
			delay(10);
			IO0CLR=1<<EN;
	
}
void data(char x)
{
	int i;
	char y;
	   
	for(i=0;i<=3;i++)
	{
		y=x & value[i];
		if(y!=0)
		{
			IO0SET=1<<pin[i];
		}
		else
			{
				IO0CLR=1<<pin[i];
		  }
			
	}
    	IO0SET=1<<RS;
			IO0SET=1<<EN;
			delay(10);
			IO0CLR=1<<EN;
		for(i=0;i<=3;i++)
	{
		y=(x<<4) & value[i];// shifting lower to upper nibble
		if(y!=0)
		{
			IO0SET=1<<pin[i];
		}
		else
			{
				IO0CLR=1<<pin[i];
		  }
	}
	    IO0SET=1<<RS;
			IO0SET=1<<EN;
			delay(10);
			IO0CLR=1<<EN;
}
void init(void)
{
	IO0DIR=1<<RS|1<<EN|1<<19|1<<20|1<<21|1<<22|1<<17;
	IO0CLR=1<<17;
	command(0x02);// return home
	command(0x28);// 4 bit mode
	command(0x06);
	command(0x0E);
	command(0x01);
	command(0x80);
}
void string(char *p)
{
	while(*p!='\0')
	{
		data(*p);
		p++;
	}
}
void number(unsigned int x)
{
	unsigned int m=0,i,d=1, n;
	if(x==0)
	{	
	data(48);
	}
	
	else
	{
		n=x;
		while(x!=0)
		{
			x=x/10;
			m++;
		}
		
		for(i=0;i<m-1;i++)
		{
			d=d*10;
		}
		
		for(i=0;i<m;i++)
		{
			data((n/d)+48);
			n=n%d;
			d=d/10;
			
		}
		
	}
}