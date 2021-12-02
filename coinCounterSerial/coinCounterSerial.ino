#include <SoftwareSerial.h>

#ifdef ARDUINO_AVR_UNO  
SoftwareSerial mySerial(3, 4); // RX, TX
#endif

#ifdef ARDUINO_AVR_LEONARDO
SoftwareSerial mySerial(16, 9); // RX, TX // Arduino 16: MOSI, outer-center on ISP port
#endif

bool sendIfSerialIsAvailable = false;

// coinAcceptor
#define pulseCount20kr  2
#define pulseCount10kr  3
#define pulseCount5kr  4
#define pulseCount1kr 5

// Statistics
int kr = 0;
int kr1 = 0;
int kr5 = 0;
int kr10 = 0;
int kr20 = 0;

int coinType = 0;
int numCoins=0;
int numCoinsLast=0;

void printCoinCounterStandard() {
  Serial.print("Coin: ");
  Serial.print(coinType);
  Serial.print(", Coin#: ");
  Serial.print(numCoins);
  Serial.print(",  1kr:");
  if (kr1<10) Serial.print(" ");
  Serial.print(kr1);
  Serial.print(",  5kr:");
  if (kr5<10) Serial.print(" ");
  Serial.print(kr5);
  Serial.print(",  10kr:");
  if (kr10<10) Serial.print(" ");
  Serial.print(kr10);
  Serial.print(",  20kr");
  if (kr20<10) Serial.print(" ");
  Serial.print(kr20);
  Serial.print(",  Total: ");
  if (kr<10) Serial.print(" ");
  if (kr<100) Serial.print(" ");
  if (kr<1000) Serial.print(" ");
  Serial.println(kr);
}



void setup() {
  Serial.begin(115200);

#ifdef ARDUINO_AVR_LEONARDO
  unsigned long timeOut = millis();
  while (!Serial && (millis()-timeOut < 3000)) {
    ; // wait for serial port to connect. Needed for native USB
  }

  if (Serial) {
    Serial.println("Start CoinCounter Leonardo");
  }

#endif

  if (Serial) {
    sendIfSerialIsAvailable = true;
  }
  
  mySerial.begin(9600);

}

void loop() {
  if (mySerial.available()) {
    byte coin = mySerial.read();
    if (coin==pulseCount20kr) {kr20++; kr += 20;}
    else if (coin==pulseCount10kr) {kr10++; kr += 10;}
    else if (coin==pulseCount5kr) {kr5++; kr += 5;}
    else if (coin==pulseCount1kr) {kr1++; kr += 1;}
  
    coinType = coin;
    numCoins++;
    printCoinCounterStandard();
  }
  if (Serial.available()) {
    byte rx=Serial.read();
    if (rx=='c') {
      kr=0;
      kr1=0;
      kr5=0;
      kr10=0;
      kr20=0;
      coinType=0;
      numCoins=0;
      Serial.println("\nReset Counters\n");
      printCoinCounterStandard();
    }
  }

}
