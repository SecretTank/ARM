# Makefile for building STM32 projects
#
# Bijan Binaee <bijan@binaee.com>, 2015
#

#Device Parameters
TARGET_DEVICE = STM32F407xx
FLASH_ORIGIN = 0x8000000


OPENOCD_SCRIPTS = /usr/share/openocd/scripts
PROGRAMMER = board/stm32f4discovery.cfg

# Project sources
SRCS = main.c stm32f4xx_it.c system_stm32f4xx.c syscalls.c utils.c
SRCS += Audio.c mp3_data.c

# all the files will be generated with this name (main.elf, main.bin, main.hex, etc)

PROJ_NAME=euphoniousـbird
OUTPATH=build

###################################################

# Check for valid float argument
# NOTE that you have to run make clan after
# changing these as hardfloat and softfloat are not
# binary compatible
ifneq ($(FLOAT_TYPE), hard)
ifneq ($(FLOAT_TYPE), soft)
override FLOAT_TYPE = hard
#override FLOAT_TYPE = soft
endif
endif

###################################################

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
SIZE=arm-none-eabi-size

CFLAGS  = -std=gnu99 -g -O2 -Wall -Tstm32_flash.ld
CFLAGS += -mlittle-endian -mthumb -mthumb-interwork -nostartfiles -mcpu=cortex-m4

ifeq ($(FLOAT_TYPE), hard)
CFLAGS += -fsingle-precision-constant -Wdouble-promotion
CFLAGS += -mfpu=fpv4-sp-d16 -mfloat-abi=hard
#CFLAGS += -mfpu=fpv4-sp-d16 -mfloat-abi=softfp
else
CFLAGS += -msoft-float
endif

###################################################

vpath %.c src
vpath %.a lib

ROOT=$(shell pwd)

CFLAGS += -Iinc -Ilib -Ilib/inc 
CFLAGS += -Ilib/inc/core -Ilib/inc/peripherals

# MP3
CFLAGS += -Ihelix/pub

# add startup file to build
SRCS += lib/startup_stm32f4xx.s

# Libraries to use
LIBS = -Llib -lstm32f4 -Lhelix -lhelix -lm

OBJS = $(SRCS:.c=.o)

###################################################

.PHONY: lib proj

all: lib proj
	$(SIZE) $(OUTPATH)/$(PROJ_NAME).elf

lib:
	$(MAKE) -C lib FLOAT_TYPE=$(FLOAT_TYPE)
	$(MAKE) -C helix FLOAT_TYPE=$(FLOAT_TYPE)

proj: 	$(OUTPATH)/$(PROJ_NAME).elf

$(OUTPATH)/$(PROJ_NAME).elf: $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)
	$(OBJCOPY) -O ihex $(OUTPATH)/$(PROJ_NAME).elf $(OUTPATH)/$(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(OUTPATH)/$(PROJ_NAME).elf $(OUTPATH)/$(PROJ_NAME).bin
	
# Program the binary to the board using the builtin serial bootloader
flash: all
	openocd -s $(OPENOCD_SCRIPTS) -f $(PROGRAMMER) -c "init;reset halt;flash write_image erase $(OUTPATH)/$(PROJ_NAME).bin $(FLASH_ORIGIN);reset run;shutdown"
#	openocd -s $(OPENOCD_SCRIPTS) -f $(Programmer) -c "init;program $(TARGET).elf $(FLASH_ORIGIN) verify reset;shutdown"

clean:
	rm -f *.o
	rm -f $(OUTPATH)/$(PROJ_NAME).elf
	rm -f $(OUTPATH)/$(PROJ_NAME).hex
	rm -f $(OUTPATH)/$(PROJ_NAME).bin
	$(MAKE) clean -C lib
	$(MAKE) clean -C helix
	
	
