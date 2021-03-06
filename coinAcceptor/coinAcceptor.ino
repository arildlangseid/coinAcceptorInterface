#include "spi_interrupt.h"

// Remember to change pin and interrupt configuration in spi_interrupt.cpp
SPIINT spi(1);

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
      //digitalWrite(8,HIGH);
    }

  }
  if ( spi.getStatusFlag() == STATUS_IDLE ) {
    coinNumberNow = spi.getOutput();
    if (coinNumberNow != coinNumberLast) {
//      spi.printBits();

      int number = -1;
      switch(coinNumberNow) {
        case 0x0C: number=9; break; // 0000 1100 | 000 1100 0x0C 
        case 0x04: number=8; break; // 0000 0100 | 000 0100 0x04
        case 0xB8: number=7; break; // 1011 1000 | 011 1000 0x38
        case 0x44: number=6; break; // 0100 0100 | 100 0100 0x44
        case 0x4C: number=5; break; // 0100 1100 | 100 1100 0x4C
        case 0x1D: number=4; break; // 0001 1101 | 001 1101 0x1D
        case 0x8C: number=3; break; // 1000 1100 | 000 1100 0x0C
        case 0x86: number=2; break; // 1000 0110 | 000 0110 0x06
        case 0xBD: number=1; break; // 1011 1110 | 011 1110 0x7E
        case 0x24: number=0; break; // 0010 0100 | 010 0100 0x24
        default: break;
      }
      if (number > 0)
      {
        coinCounter++;
        Serial.print("coin# ");
        Serial.print(coinCounter);
    //    number += '0';
        Serial.print(": hex: ");
        Serial.print(coinNumberNow,HEX);
        Serial.print(", Value: ");
        Serial.println(number);

#ifdef ARDUINO_AVR_LEONARDO
        // send coin-number on serial
        Serial1.write(number);
#endif
//        delay(120);
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
