CC=clang
CFLAGS=-nostdlib -ffreestanding -fno-stack-protector -fno-asynchronous-unwind-tables -fpic -mno-red-zone -Wall -I./amd64
LD=ld
# add -pie later, adds .dynamic and other garbage to PROGBITS
LDFLAGS=-flto -nostdlib -static --nmagic -T linker.ld

.PHONY: all

all:
	$(CC) $(CFLAGS) -c amd64/start.S -o start.o
	$(CC) $(CFLAGS) -c amd64/arch.c -o arch.o
	$(CC) $(CFLAGS) -c amd64/serial.c -o serial.o
	$(CC) $(CFLAGS) -c main.c -o main.o
	$(LD) $(LDFLAGS) start.o arch.o serial.o main.o -o kernel.elf

.PHONY: clean

clean:
	rm *.o
