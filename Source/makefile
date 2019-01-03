CC = i686-elf-gcc
AS = nasm
AFLAGS = -f elf32
CFLAGS = -c -std=gnu99 -ffreestanding -O0 -Wall -w -g -I ./include
LD = i686-elf-gcc
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib

TARGET = ../bin/guinni.bin

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c) $(shell find ./src -name "*.c")) $(patsubst %.asm, %.o, $(wildcard *.asm) $(shell find ./src -name "*.asm"))

all: $(TARGET)	

$(TARGET): $(OBJECTS)
	mkdir -p ../bin
	$(LD) -o $@ -T linker.ld -ffreestanding -O2 -nostdlib $^

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@
%.o: %.asm
	$(AS) $(AFLAGS) $^ -o $@
clean:
	rm $(TARGET) $(OBJECTS)
	rm -r ../bin
	rm -rf iso

iso:	all
	mkdir -p iso
	mkdir -p iso/boot
	mkdir -p iso/boot/grub
	# ~ Now is not the time for fear, that comes later ~
	# nm ../bin/guinni.bin > ../bin/initrd/boot/INFINITY.MAP	
	# mkifsrd -d ../bin/initrd -o ../bin/iso/initrd.img
	cp ../bin/guinni.bin iso/boot/guinni.bin
	cp config/grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o ../bin/guinni.iso iso

qemu:	iso
	qemu-system-i386 -cdrom ../bin/guinni.iso

run:	qemu
