#ifndef SPI_INTERRUPT_h
#define SPI_INTERRUPT_h

#include <inttypes.h>
#include <Arduino.h>

#include <avr/interrupt.h>

#define STATUS_IDLE 0
#define STATUS_SEARCHING 1

//extern volatile int8_t isr_output = 0;

class SPIINT {
  public:

    // Constructor / Destructor
    SPIINT(int dummy);
    ~SPIINT();

  void timerSetup();
  void timerStart();
//  void timerRead();

  //bool isPulseFound();
  //uint16_t getCapt1();
  //uint16_t getCapt2();
  //uint16_t getCapt3();
  uint16_t getTimer();
  uint8_t getFlag();
  void setFlag(uint8_t iFlag);
  void incFlag();
  uint8_t getOutput();
  void printBits();
  void checkIncomming();
    
  private:
    uint8_t _SPI_CLK_PIN;
    uint8_t _SPI_MOSI_PIN;



};

#endif
