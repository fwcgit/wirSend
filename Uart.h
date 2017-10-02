#ifndef UART_H_
#define UART_H_


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<reg52.h>

#define sendBuffSize 10
#define REVEIVE_BUFF_SIZE 10

#define commRI 0x01
#define commTI 0x02

#define PACK_START 0x3A;
#define PACK_STOP 0x0D;

#define FOSC 24000000L
#define BAUD 9600

sfr AUXR = 0X8e;
sfr T2H = 0xd6;
sfr T2L = 0xd7;

#pragma SAVE
#pragma REGPARMS
extern void UART1_Init();
extern void sendData(char dat);
extern void sendStr(char *dat);
extern void sendStrlen(char *dat,int len);
extern void paraerData();
extern void sleep(unsigned int t);
extern void sleep_us(unsigned int t);
extern void opt_ss(unsigned char c1,unsigned char c2);

#pragma RESTORE
#endif
