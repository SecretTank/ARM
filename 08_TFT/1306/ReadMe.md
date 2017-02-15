# Connections

| Pin        | STM32      | Device  |
| ---------- |:----------:|:-------:|
| TX         | PA1        | USB-TTL |
| RX         | PA0        | USB-TTL |
| D0         | PB13       |   IMU   |
| D1 (MOSI)  | PB15       |   IMU   |
| Data/Comm  | PD12       |   IMU   |
| CS         | PD0        |   IMU   |
| RST        | PD13       |   IMU   |

* The most important things in driving SPI is CS
* MISO can wired ground or floated 
