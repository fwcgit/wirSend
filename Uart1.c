#include "Uart.h"
#include<string.h>
#include<reg52.h>
typedef unsigned int uint;
typedef unsigned char byte;

byte buy = 0;
uint rxIndex = 0;
byte idata buff[REVEIVE_BUFF_SIZE] ;
sfr IAP_CONTR   =   0xC7; 

byte isRec = 0;
byte isHand = 0;

byte response = 0;

void Uart1() interrupt 4 using 1
{
	byte rByte;
	
	if(RI)
	{
		RI = 0;
		
		rByte = SBUF;
			
		if(rxIndex >= REVEIVE_BUFF_SIZE)
		{
			isRec = 0;
			rxIndex = 0;
		}
		if(rByte == 0x3b)
		{
			isRec = 1;
		}
		
		if(isRec)
		{
			buff[rxIndex++] = rByte;
		}
		
		
		if(rByte == 0x0d && isRec)
		{
			isHand = 1;
			isRec = 0;
			rxIndex = 0;
		}
	}
	
	if(TI)
	{
		TI = 0;
		buy = 0;
	}
}

void sendData(byte dat)
{
		while(buy);
	
		buy = 1;
		SBUF = dat;
}

void sendStr(char *dat)
{
	while(*dat)
	{
		sendData(*dat++);
	}
}
void sendStrlen(char *dat,int len)
{
	uint i;
	for(i=0;i<len;i++)
	{
		sendData(*(dat+i));
	}
}



void paraerData()
{
	uint check = 0;
	if(isHand)
	{
		
		if(*buff == 0x3C)
		{
			//check=*(buff+1)+*(buff+2)+*(buff+3);
			//check &= 0xff;
			//if(check == *(buff+4))
			//{
					if(*(buff+1) == 0xAd)
				{
						response = 1;
				}
				else if(*(buff+1) == 0xdd)
				{
					IAP_CONTR = 0x60;
				}
			//}

		}
		memset(buff,0,sizeof(buff));
		isHand = 0;
	}
	
}


void sleep(uint sleep)
{
	uint i,j;
	for(i = sleep ; i > 0 ; i --)
		for(j = 2000 ; j > 0 ; j --);
}
void sleep_us(unsigned int t)
{
	uint i,j;
	for(i = t ; i > 0 ; i --)
		for(j = 3 ; j > 0 ; j --);
}

void UART1_Init()
{
	SCON = 0X50;
	T2L = (65536 - (FOSC/4/BAUD));
	T2H = (65536 - (FOSC/4/BAUD)) >> 8;
	AUXR |= 0X14;
	AUXR |= 0X01;
	ES =1;
	EA = 1;
}

void opt_ss(unsigned char c1,unsigned char c2)
{
	unsigned char dats[6];
	dats[0] = 0X3C;
	dats[1] = 0XA0;
	dats[2] = c1;
	dats[3] = c2;
	dats[4] =(dats[1]+dats[2]+dats[3]) & 0xff;
	dats[5] = 0x0d;	
	
	sendStrlen(dats,6);
	response = 0;
	
}






