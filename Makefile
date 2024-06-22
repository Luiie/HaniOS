ARCH = armv7-a
MCPU = cortex-a8

TARGET = RealViewPB

CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OC = arm-none-eabi-objcopy
OD = arm-none-eabi-objdump

OUTDIR = ./build

LINKER_SCRIPT = ./hanios.ld
MAP_FILE = ./build/hanios.map

ASM_SRCS = $(wildcard ./boot/*.S)
ASM_OBJS = $(patsubst ./boot/%.S, ./build/%.os, $(ASM_SRCS))

VPATH = ./boot\
		./HAL/$(TARGET)\
		./lib

C_SRCS = $(wildcard ./boot/*.c)
C_SRCS += $(wildcard ./HAL/$(TARGET)/*.c)
C_SRCS += $(wildcard ./lib/*.c)
C_OBJS = $(patsubst ./%.c, ./build/%.o, $(C_SRCS))

INC_DIRS = -I ./include\
		   -I ./HAL\
		   -I ./HAL/$(TARGET)\
		   -I ./lib

CFLAGS = -c -g -std=c11

hanios = ./build/hanios.axf
hanios_bin = ./build/hanios.bin

.PHONY: all clear run debug gdb

all: $(hanios)

clear:
	@rm -fr ./build
    
run: $(hanios)
	qemu-system-arm -M realview-pb-a8 -kernel $(hanios) -nographic
    
debug: $(hanios)
	qemu-system-arm -M realview-pb-a8 -kernel $(hanios) -nographic -S -gdb tcp::1234,ipv4
    
gdb:
	arm-none-eabi-gdb ./build/hanios.axf

$(hanios): $(ASM_OBJS) $(C_OBJS) $(LINKER_SCRIPT)
	$(LD) -n -T $(LINKER_SCRIPT) -o $(hanios) $(C_OBJS) $(ASM_OBJS) -Map=$(MAP_FILE)
	$(OC) -O binary $(hanios) $(hanios_bin)

./build/%.os: ./%.S
	mkdir -p $(shell dirname $@)
	$(CC) -march=$(ARCH) -marm $(INC_DIRS) $(CFLAGS) -o $@ $<

./build/%.o: ./%.c
	mkdir -p $(shell dirname $@)
	$(CC) -march=$(ARCH) -marm $(INC_DIRS) $(CFLAGS) -o $@ $<