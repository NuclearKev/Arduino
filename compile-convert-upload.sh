#! /bin/bash

clear

echo "What is the source file name (without the file extension)?"

read file

avr-gcc -c -g -Os -w -Wall -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -MMD -mmcu=atmega328p -DF_CPU=16000000L $file.c -o $file.o

avr-gcc -w -Os -Wl,--gc-sections -mmcu=atmega328p -o $file.elf $file.o -L /home/kevin/Development/arduino -lm 

avr-objcopy -O ihex $file.elf $file.hex

avrdude -v -p atmega328p -c arduino -P /dev/ttyACM* -D -B 115200 -U flash:w:$file.hex:i

#clean up because ain't nobody got time for all these files
rm $file.d $file.hex $file.elf $file.o
