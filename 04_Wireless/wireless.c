#include <avr/io.h>
#include "USART.h"
#include <util/setbaud.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SSID "biju_and_me"
#define PASS "bijuaydcac"
#define DST_IP "220.181.111.85" //baidu.com
int connectWiFi(void);
void loop(void);
int main(void)
{
		// Open serial communications and wait for port to open:
		initUSART();
		//test if the module is ready
		printString("----- ESP8266 Demo ------\r\n");
		_delay_ms(1000);
		/*if(readString("ready"))
		  {
		  cerr << "module is ready" ;
		  }
		  else
		  {
		  cerr << "Module have no response." ;
		  while(1);
		  }*/
		_delay_ms(1000);
		//connect to the wifi
		int connected=0;
		for(int i=0;i<5;i++)
		{
				if(connectWiFi())
				{
						connected = 1;
						break;
				}
		}
		if (!connected){while(1);}
		_delay_ms(5000);
		//print the ip addr
		/*Serial.println("AT+CIFSR");
		  dbgSerial.println("ip address:");
		  while (Serial.available())
		  dbgSerial.write(Serial.read());*/
		//set the single connection mode
		printString("AT+CIPMUX=0");
}
void loop()
{
		char cmd[100] = "AT+CIPSTART=\"TCP\",\"";
		strcat(cmd, DST_IP);
		strcat(cmd, "\",80");
		printString(cmd);
		//dbgSerial.println(cmd);
		//if(Serial.find("Error")) return;
		strcpy(cmd,"GET / HTTP/1.0\r\n\r\n");
		printString("AT+CIPSEND=");
		char buffer[16];
		itoa (strlen(cmd),buffer,16);
		printString(buffer);
		/*if(Serial.find(">"))
		  {
		  dbgSerial.print(">");
		  }else
		  {
		  Serial.println("AT+CIPCLOSE");
		  dbgSerial.println("connect timeout");
		  _delay_ms(1000);
		  return;
		  }*/
		printString(cmd);
		_delay_ms(2000);
		//Serial.find("+IPD");
		//while (Serial.available())
		//{
				//char c = receiveByte();
				//transmitByte(c);
				//dbgSerial.write(c);
				//if(c=='\r') dbgSerial.print('\n');
		//}
		//dbgSerial.println("====");
		_delay_ms(1000);
}
int connectWiFi()
{
		printString("AT+CWMODE=1");
		char cmd[100] ="AT+CWJAP=\"";
		strcat(cmd,SSID);
		strcat(cmd,"\",\"");
		strcat(cmd,PASS);
		strcat(cmd,"\"");
		//dbgSerial.println(cmd);
		printString(cmd);
		_delay_ms(2000);
		/*if(Serial.find("OK"))
		  {
		  dbgSerial.println("OK, Connected to WiFi.");
		  return true;
		  }else
		  {
		  dbgSerial.println("Can not connect to the WiFi.");
		  return false;
		  }*/
		return 1;
}

