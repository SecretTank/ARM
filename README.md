# ARM
ARM Example Projects in Linux

## How To Start
1. Download CMSIS Library (named STM32CubeF4 for stm32 MCU families) from [ST website](http://www.st.com/web/en/catalog/tools/PF259242)
2. To install CMSIS follow Install CMSIS Section in the page.
3. run `Documents/preparing.sh` from your terminal with root access.
4. Enjoy

## Install CMSIS
1. Create Directory `/usr/include/CMSIS` and `/usr/include/CMSIS/Device`
3. Copy `%Cube%/Drivers/CMSIS/Include` to `/usr/include/CMSIS`
2. Copy `%Cube%/Drivers/CMSIS/Device/ST/STM32F4xx/Include` to `/usr/include/CMSIS/Device`

- to copy all files you could use something similar to the following command
```
sudo cp "/home/bijan/Project/ARM/STM32CubeF4/Drivers/CMSIS/Include/*" /usr/include/CMSIS 
```

