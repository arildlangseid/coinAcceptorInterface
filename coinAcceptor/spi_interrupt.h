#ifndef SPI_INTERRUPT_h
#define SPI_INTERRUPT_h

#include <inttypes.h>
#include <Arduino.h>

#include <avr/interrupt.h>

#define STATUS_IDLE 0
#define STATUS_SEARCHING 1


class SPIINT {
  public:

    // Constructor / Destructor
    SPIINT();
    ~SPIINT();

  void timerSetup();
  void timerStart();

  uint8_t getStatusFlag();
  void setStatusFlag(uint8_t iStatusFlag);
  uint8_t getOutput();
  void printBits();
  bool checkIncomming();
    
  private:

};

#endif
