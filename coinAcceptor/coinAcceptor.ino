#include "spi_interrupt.h"

/*
 * CoinAcceptor interface for CH926 and alike coin acceptors from ebay with 9-bit SPI to the shift-register for
 * the 7-segment display on the side. Why the chinese made a firmware which sends 9 clock signals to the 8-bit shift register 74HC164
 * is beyond my imagination. Maybe some fun Winnie the Pooh came up with.
 * 
 * You have to open the cover on the display/led side of the coin acceptor.
 * On mine there were only one screw under the "Passed" sticker
 * You also have to remove the PCB. Two screws on the right side.
 * Then desolder the coin-coil which is glued into place - two pins upper right corner on the PCB.
 * Be careful when disconnecting the 4-wire flat cable to the coil and leds to the PCB.
 * 
 * Now - you have to solder three wires to the PCB.
 * First Ground - I connected GND the frontmost pin on the 4-pin serial port is ground.
 * Find the chip named 74HC164 and locate pins 1&2 and 8. The pins are small - but fortunately on the ends of the chip :-)
 * Pin 1&2 on the 74HC164 is the DATA-input pin must be connected to pin 3 on the Arduino
 * Pin 8 on the 74HC164 is the CLOCK-input pin must be connected to pin 2 on the Arduino
 * 
 * I have used an Arudino Micro (Leonardo) which actualy fits nicely under the PCB of the coin acceptor. Remember to insulate the Arduino in
 * electrical tape before mounting behind the PCB.
 * 
 * If you happen to have a coin-acceptor with more sensible 8 clock pulses to the 8-bit shift register 74HC164, you can do this
 * easily by connecting pin 1&2 on the 74HC164 to the MOSI pin and pin 8 on the 74HC164 to SPICLK on the Arduino. You can then
 * use Hardware SPI on the Arduino instead of this rather time-critical hack.
 * See this github-repo for atmel c-code: https://github.com/fablab-bayreuth/coinspi
 * 
 * There is no production-code for the Uno. This will need the SoftSerial library as the ATMega328P does not have the second hardware Serial.
 * The Uno is on the other hand superb for development and testing on a PC - as you will never soft-brick the Uno as it is possible to on the Leonardo.
 * (Never do an endless loop int the Loop() function on a Leonardo as you will have problems recognizing the USB-interface on a PC.)
 */


SPIINT spi;

#define debugPin 8

int16_t coinCounter = 0;

void setup() {
  Serial.begin(115200);

#ifdef ARDUINO_AVR_UNO
  Serial.println("Start CoinAcceptor Uno");
#endif
#ifdef ARDUINO_AVR_LEONARDO
  unsigned long timeOut = millis();
  while (!Serial && (millis()-timeOut < 3000)) {
    ; // wait for serial port to connect. Needed for native USB
  }
  Serial.println("Start CoinAcceptor Leonardo");
#endif
#ifdef ARDUINO_AVR_MEGA2560
    Serial.println("Start CoinAcceptor Mega2560");
#endif

#ifdef ARDUINO_AVR_LEONARDO
  // Serial for sending the coin-number on serial-pin
  Serial1.begin(9600);
#endif

  pinMode(debugPin, OUTPUT);
  
  spi.timerSetup();
  spi.timerStart();
}

uint8_t coinNumberNow = 0;
uint8_t coinNumberLast = 0;
void loop() {
  if ( spi.getStatusFlag() == STATUS_IDLE ) {
    if ( spi.checkIncomming() ) {
      // Debug-code for external Logic Analyzer
      //digitalWrite(8,HIGH);
    }

  }
  if ( spi.getStatusFlag() == STATUS_IDLE ) {
    coinNumberNow = spi.getOutput();
    if (coinNumberNow != coinNumberLast) {
//      spi.printBits();

      int number = -1;
      switch(coinNumberNow) {
        case 0x0C: number=9; break; // 0000 1100
        case 0x04: number=8; break; // 0000 0100
        case 0xB8: number=7; break; // 1011 1000
        case 0x44: number=6; break; // 0100 0100
        case 0x4C: number=5; break; // 0100 1100
        case 0x1D: number=4; break; // 0001 1101
        case 0x8C: number=3; break; // 1000 1100
        case 0xBD: number=1; break; // 1011 1110
        case 0x86: number=2; break; // 1000 0110
        case 0x24: number=0; break; // 0010 0100
        default: break;
      }
      if (number > 0)
      {
        coinCounter++;
        Serial.print("coin# ");
        Serial.print(coinCounter);
        Serial.print(": hex: ");
        Serial.print(coinNumberNow,HEX);
        Serial.print(", Value: ");
        Serial.println(number);

#ifdef ARDUINO_AVR_LEONARDO
        // send coin-number on serial
        Serial1.write(number);
#endif
      }


      // Debug-code for external Logic Analyzer
//      if (coinNumberNow != 0x24) {
//        digitalWrite(debugPin,LOW);
//      }
    }
    coinNumberLast = coinNumberNow;
    TCNT1=0;
    spi.setStatusFlag(STATUS_SEARCHING);
  }


}
