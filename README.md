# coinAcceptorInterface

# How to find the compiled assembly of the arduino code:
Turn on verbose output during compilation in the preferences.
Find the output directory in the output from the compiler and cd to that dir in an cmd-shell
avr-objdump.exe -Sz coinAcceptor.ino.elf > coinAcceptor.assembly.txt
