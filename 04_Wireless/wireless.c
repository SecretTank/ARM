#include <avr/io.h>
#include "USART.h"
#include <util/setbaud.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#include <delay.h>
#define SSID "biju_and_me"
#define PASS "bijuaydcac"
#define ACCESSPOINT_NAME "\"UT-MEMS-2\""
#define PASSWORD "\"tcadTCAD67\""
#define IP_ADDRESS "\"192.168.82.103\""
#define TCP "\"TCP\""


int connectWiFi(void);
void loop(void);

const char port[5] = "7778";
int main(void)
{
		initUSART();
		for(int i=0;i<5;i++)
		{
				connectWiFi();
		}
}
int connectWiFi()
{
		char message[100] = "AT+CWJAP=";
		strcpy(message,strcat(message,ACCESSPOINT_NAME));
		strcpy(message,strcat(message,","));
		strcpy(message,strcat(message,PASSWORD));
		strcpy(message,strcat(message,"\r\n"));
		//char response[20];
		printString("\r\nAT+CWMODE=3\r\n");
		printString(message);
		printString("\r\nAT+CIPMUX=1\r\n");
		strcpy(message,"\r\nAT+CIPSTART=4,");
		strcpy(message,strcat(message,TCP));
		strcpy(message,strcat(message,","));
		strcpy(message,strcat(message,IP_ADDRESS));
		strcpy(message,strcat(message,","));
		strcpy(message,strcat(message,port));
		strcpy(message,strcat(message,"\r\n"));
						printString(message);
						//printString("\r\nAT+CIPSEND=4,18\r\n");

						/*readString(response,3);
						  if(!strcmp(response,"OK")){

						  readString(response,3);
						  if(!strcmp(response,"OK")){
						  printString("AT+CIPMUX=1");
						  readString(response,3);
						  if(!strcmp(response,"OK")){
						  strcpy(message,"AT+CIPSTART=4,\"TCP\",");
						  strcpy(message,strcat(message,IP_ADDRESS));
						  strcpy(message,strcat(message,","));
						  strcpy(message,strcat(message,port));
						  readString(response,3);
						  if(!strcmp(response,"OK\nLinked"))

						  }
						  }
						  }*/
		return 1;
}
//at+CIPMUX=1
//at+CIPSTART=4,"TCP","192.168.82.103",7778
//at+CIPSEND=4,25
