# ARM
ARM Example Projects in Linux

## How To Start
1. Download CMSIS Library (named STM32CubeF4 for stm32 MCU families) from [ST website](http://www.st.com/web/en/catalog/tools/PF259242)
2. Extract Files and replace it with **\<Your CMSIS Dir>** in the next step.
3. Run `Documents/preparing.sh "<Your CMSIS Dir>"` from your terminal, **be sure to not use sudo**. The script ask for root access automatically.
4. Enjoy

* In case of failure upon automatic installation see `Manual CMSIS Installation` section

## Dependencies
```
sudo pacman -S arm-none-eabi-gcc arm-none-eabi-newlib openocd
```

## Manual CMSIS Installation
1. Copy `%Cube%/Drivers/CMSIS/Include` to `/usr/include/CMSIS`
2. Copy `%Cube%/Drivers/CMSIS/Device/ST/STM32F4xx/Include` to `/usr/include/CMSIS/Device`

- to copy all files you could use something similar to the following command
```
sudo cp "/home/bijan/Project/ARM/STM32CubeF4/Drivers/CMSIS/Include/*" /usr/include/CMSIS 
```

