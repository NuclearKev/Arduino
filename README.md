# Arduino
This repo contains a bunch of programs that I created for the Arduino Uno board. This was entirely for educational purposes.

All the programs are free software under the GPLv3, use them as you wish.

You will need a few things in order to use these programs:

an Arduino, lib-avr, avr-gcc, avrdude, and a nice text editor (You might need something else but I don't remember)

You'll notice most of them are rather rudimentary (such as the header files); but keep in mind they are all for education.

main.c: This is simple program that you can use to see the USART and the Timer1 in action. 

adc.c: You can use this to see the ADC working on the board. Keep in mind that it converts the value into a character and spits it out using the USART. Thus, you will need something like GNU Screen to see it.

pwm.c: This program shows how PWM works on the arduino. It works best with an LED; you'll get a cool glowing effect. You can also use a servo with it but it'll act weird. 

compile-convert-upload.sh: This is a shell script that you can run that will compile your code, convert it a intel .hex format, and upload it to the Arduino. 

vu.c: This is a basic VU meter program. All it does is take the audio and output the volume to some LEDs right now. You can view the tsa-amp.ps (you'll need to download it) file to see the op-amp circuit I designed in order for the Arduino to be able to pick up the voltage. 

vu-amp.ps: This is a schematic for a simple op-amp circuit for the vu.c program. Please note that this is a generic design and the resistor values can be changed to whatever you want. In my case, I used a 25k pot for R2 so that I could keep the volume on the computer low and still get a good response on the LEDs.
