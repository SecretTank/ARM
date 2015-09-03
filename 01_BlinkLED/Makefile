# Makefile for building STM32 projects
#
# Bijan Binaee <bijan@binaee.com>, 2015
#

#Device Parameters
TARGET_DEVICE = STM32F407xx
FLASH_ORIGIN = 0x8000000


OPENOCD_SCRIPTS = /usr/share/openocd/scripts
Programmer = /usr/share/openocd/scripts/board/stm32f4discovery.cfg


#Input/Output Files
SOURCES = main.c
TARGET = BlinkLED


# Name of the startup file.  'hd' for high density
STARTUP = startup_stm32f407xx.s
FLASH_LINKER = STM32F407VGTx_FLASH.ld

# Build for the Cortex-M4 with basic optimisations and debugging
# Using the GNU ARM EABI tools
CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
OBJCOPY = $(CROSS_COMPILE)objcopy
CFLAGS = -mcpu=cortex-m4 -mlittle-endian -mthumb -mthumb-interwork -O -g -I /usr/include/CMSIS -D $(TARGET_DEVICE) -Wl,--gc-sections

# List of all binaries to build
all: $(TARGET).bin

# Create a raw binary file from the ELF version
$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# Create the ELF version by mixing together the startup file,
# application, and linker file
$(TARGET).elf: $(STARTUP) $(SOURCES) system_stm32f4xx.c 
	$(CC) -o $@ $(CFLAGS) -nostartfiles -Wl,-T$(FLASH_LINKER) $^

# Program the binary to the board using the builtin serial bootloader
flash:
	openocd -s $(OPENOCD_SCRIPTS) -f $(Programmer) -c "init;reset halt;flash write_image erase $(TARGET).bin $(FLASH_ORIGIN);reset run;shutdown"
#	openocd -s $(OPENOCD_SCRIPTS) -f $(Programmer) -c "init;program $(TARGET).elf $(FLASH_ORIGIN) verify reset;shutdown"

# Remove the temporary files
clean:
	rm -f *.o *.elf *.bin

