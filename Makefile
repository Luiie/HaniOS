ARCH = armv7-a
MCPU = cortex-a8

CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OC = arm-none-eabi-objcopy
OD = arm-none-eabi-objdump

OUTDIR=./out

LINKER_SCRIPT = ./hanios.ld

ASM_SRCS = $(wildcard ./boot/*.S)
ASM_OBJS = $(patsubst ./boot/%.S, ./build/%.o, $(ASM_SRCS))

hanios = ./build/hanios.axf
hanios_bin = ./build/hanios.bin

.PHONY: all clean run debug gdb

all: $(hanios)

clean:
	@rm -fr ./build
	
run: $(hanios)
	qemu-system-arm -M realview-pb-a8 -kernel $(hanios) -nographic
	
debug: $(hanios)
	qemu-system-arm -M realview-pb-a8 -kernel $(hanios) -nographic -S -gdb tcp::1234,ipv4
	
gdb:
	arm-none-eabi-gdb

$(hanios): $(ASM_OBJS) $(LINKER_SCRIPT)
	$(LD) -n -T $(LINKER_SCRIPT) -o $(hanios) $(ASM_OBJS)
	$(OC) -O binary $(hanios) $(hanios_bin)

build/%.o: boot/%.S
	mkdir -p $(shell dirname $@)
	$(AS) -march=$(ARCH) -mcpu=$(MCPU) -g -o $@ $<