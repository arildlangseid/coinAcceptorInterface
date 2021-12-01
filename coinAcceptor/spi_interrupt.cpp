#include "spi_interrupt.h"
#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

//#define DEBUG_PRINT_ERROR 1


/*
   Pubblic memberfunctions
*/

// read incomming port in time-critical parts
volatile int8_t b0;
volatile int8_t b1;
volatile int8_t b2;
volatile int8_t b3;
volatile int8_t b4;
volatile int8_t b5;
volatile int8_t b6;
volatile int8_t b7;

// working variables after time-critical port reading
volatile int8_t ob0;
volatile int8_t ob1;
volatile int8_t ob2;
volatile int8_t ob3;
volatile int8_t ob4;
volatile int8_t ob5;
volatile int8_t ob6;
volatile int8_t ob7;

volatile uint8_t isr_tmp;
volatile uint8_t isr_output;
volatile uint8_t statusFlag = STATUS_IDLE;

// Arduino-pins
#define SPICLK 2
#define SPIMOSI 3

#ifdef ARDUINO_AVR_UNO
  #define SPICLK PD2
  #define SPIDATA PD3
  #define SPICLK_INTERRUPT INT0
  #define COIN_ISR_VECTOR INT0_vect
#endif
#ifdef ARDUINO_AVR_LEONARDO
  #define SPICLK PD1
  #define SPIDATA PD0
  #define SPICLK_INTERRUPT INT1
  #define COIN_ISR_VECTOR INT1_vect
#endif


ISR(COIN_ISR_VECTOR, ISR_NAKED)
{
  // Store as litle as possible
  asm(
    "push  r24\n"
    "in  r24, 0x3f\n"
    "push  r24\n"
  );

//  b0=PIND;
  asm (
    "in r24, 0x09\n" // Read PIND
    "sts (b0),r24\n" // Store to b0
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
  );
//  b1=PIND;
  asm (
    "in r24, 0x09\n"
    "sts (b1),r24\n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
  );
//  b2=PIND;
  asm (
    "in r24, 0x09\n"
    "sts (b2),r24\n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
  );
//  b3=PIND;
  asm (
    "in r24, 0x09\n"
    "sts (b3),r24\n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
  );
//  b4=PIND;
  asm (
    "in r24, 0x09\n"
    "sts (b4),r24\n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
  );
//  b5=PIND;
  asm (
    "in r24, 0x09\n"
    "sts (b5),r24\n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
  );  
//  b6=PIND;
  asm (
    "in r24, 0x09\n"
    "sts (b6),r24\n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
    "NOP \n"
  );
  //b7=PIND;
  asm (
    "in r24, 0x09\n"
    "sts (b7),r24\n"
  );

  if ( statusFlag == STATUS_IDLE )
  {
    // restore registers used in isr
    asm(
      "pop r24\n"
      "out 0x3f, r24\n"
      "pop r24\n"
      "reti\n"
    );

  }

  // Store readings to output-variables for further calculations
  asm (
//    ob0=b0;
    "lds r24, (b0)\n"
    "sts ob0, r24\n"
//    ob1=b1;
    "lds r24, (b1)\n"
    "sts ob1, r24\n"
//    ob2=b2;
    "lds r24, (b2)\n"
    "sts ob2, r24\n"
//    ob3=b3;
    "lds r24, (b3)\n"
    "sts ob3, r24\n"
//    ob4=b4;
    "lds r24, (b4)\n"
    "sts ob4, r24\n"
//    ob5=b5;
    "lds r24, (b5)\n"
    "sts ob5, r24\n"
//    ob6=b6;
    "lds r24, (b6)\n"
    "sts ob6, r24\n"
//    ob7=b7;
    "lds r24, (b7)\n"
    "sts ob7, r24\n"
  );


  //statusFlag=STATUS_IDLE;
  asm (
    "ldi r24, 0x00\n"
    "sts (statusFlag), r24\n"
  );

  // restore registers used in isr
  asm(
    "pop r24\n"
    "out 0x3f, r24\n"
    "pop r24\n"
    "reti\n"
  );

}

bool SPIINT::checkIncomming() {
  if (statusFlag==STATUS_IDLE) {
    // We are timing the bit-reading above to be slightly before the clock-signal falling edge.
    // This way we can verify that we have a high clock on every bit an so be sure we have a valid 8bit reading
    // (if we are too late, clock on bit7 will be low - and so we discard the reading as invalid)
    byte verify = ob0&ob1&ob2&ob3&ob4&ob5&ob6&ob7 & (1<<SPICLK);
    isr_tmp = 0;
    isr_tmp |= (ob0&(1<<SPIDATA))>>SPIDATA<<7;
    isr_tmp |= (ob1&(1<<SPIDATA))>>SPIDATA<<6;
    isr_tmp |= (ob2&(1<<SPIDATA))>>SPIDATA<<5;
    isr_tmp |= (ob3&(1<<SPIDATA))>>SPIDATA<<4;
    isr_tmp |= (ob4&(1<<SPIDATA))>>SPIDATA<<3;
    isr_tmp |= (ob5&(1<<SPIDATA))>>SPIDATA<<2;
    isr_tmp |= (ob6&(1<<SPIDATA))>>SPIDATA<<1;
    isr_tmp |= (ob7&(1<<SPIDATA))>>SPIDATA<<0;

#ifdef DEBUG_PRINT_ERROR
    Serial.print("tcnt1:");Serial.println(tcnt1now);
    Serial.print("verify:");Serial.println(verify);
    Serial.print("isr_tmp:");Serial.println(isr_tmp,HEX);
    Serial.println(ob0&((1<<SPICLK)|(1<<SPIDATA)));
    Serial.println(ob1&((1<<SPICLK)|(1<<SPIDATA)));
    Serial.println(ob2&((1<<SPICLK)|(1<<SPIDATA)));
    Serial.println(ob3&((1<<SPICLK)|(1<<SPIDATA)));
    Serial.println(ob4&((1<<SPICLK)|(1<<SPIDATA)));
    Serial.println(ob5&((1<<SPICLK)|(1<<SPIDATA)));
    Serial.println(ob6&((1<<SPICLK)|(1<<SPIDATA)));
    Serial.println(ob7&((1<<SPICLK)|(1<<SPIDATA)));
    Serial.println("-");
    Serial.println(ob0&(1<<SPIDATA));
    Serial.println(ob1&(1<<SPIDATA));
    Serial.println(ob2&(1<<SPIDATA));
    Serial.println(ob3&(1<<SPIDATA));
    Serial.println(ob4&(1<<SPIDATA));
    Serial.println(ob5&(1<<SPIDATA));
    Serial.println(ob6&(1<<SPIDATA));
    Serial.println(ob7&(1<<SPIDATA));
    Serial.println("-");
#endif

    if (verify>0) {
      isr_output = isr_tmp;
      return true;
    }
  }
}

/*
   Constructor
*/
SPIINT::SPIINT(int dummy)
{
  pinMode(SPICLK, INPUT);
  pinMode(SPIMOSI, INPUT);

  pinMode(8,OUTPUT);
  digitalWrite(8,LOW);

#ifdef DEBUG_PRINT_ERROR
  Serial.println(F("SPIINT created"));
#endif
}

/*
   Destructor
*/
SPIINT::~SPIINT()
{
}


void SPIINT::timerSetup() {
  TCCR1A=0;
  // Stop timer > prescaler set to 0
  TCCR1B=0;
  // set top value to ICR1
  ICR1=0xffff;

  // Set Initial Timer value
  TCNT1=0;

  // Reset all trigger modes on interrupt
  EICRA=0;
  // Set trigger mode on Interrupt (setting both INT0 and INT1 for both Uno and Leonardo)
  EICRA|=(1<<ISC01)|(1<ISC00); // INT0 rising
  EICRA|=(1<<ISC11)|(1<ISC10); // INT1 rising

  // disable interrupts
  EIMSK=0;
  
}

void SPIINT::timerStart() {
  // Setup Timer1
  TCNT1=0;
  TCCR1B|=(1<<CS12)|(1<<CS10);

  statusFlag = STATUS_IDLE;

  // enable Interrup
  EIMSK|=(1<<SPICLK_INTERRUPT); // INT0 inabled

  //Enable global interrutps
  sei();
}

uint8_t SPIINT::getStatusFlag(){
  return statusFlag;
}
void SPIINT::setStatusFlag(uint8_t iStatusFlag){
  statusFlag = iStatusFlag;
}
uint8_t SPIINT::getOutput(){
  return isr_output;
}


/**
   Private memberfunctions
*/

void SPIINT::printBits() {
  Serial.println("--bits--");
  Serial.println(ob0);
  Serial.println(ob1);
  Serial.println(ob2);
  Serial.println(ob3);
  Serial.println(ob4);
  Serial.println(ob5);
  Serial.println(ob6);
  Serial.println(ob7);
}
