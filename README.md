# coinAcceptorInterface

# How to find the compiled assembly of the arduino code:
Turn on verbose output during compilation in the preferences.
Find the output directory in the output from the compiler and cd to that dir in an cmd-shell
avr-objdump.exe -Sz coinAcceptor.ino.elf > coinAcceptor.assembly.txt


# coinAcceptorInterface
Arduino project to fast and reliable read out the coin type of the ch926 coin acceptor that uses 9-bit SPI to the 74HC164 chip (7-segment driver)

# coinCounterOLED
Arduino project to implement a display to show the results from coinAcceptorInterface on a small .96inch OLED

# coinCounterSerial
Arduino project to send the output from coinAcceptorInterface to the PC (Arduino IDE Serial Monitor)

# coinCounterStepperMotor
Arduino project to run the cheap stepper-motors to drive the coindisc of the modified coin sorter I remixed from Thingiverse.com

# documents
Various documents I have collected during this project. One important source for information (a blog on the ch926) has disappeared from the internet, but fortunately archive.org had the blog in its archives, so I saved a copy for reference. Big credits to Vince!