#include <SoftwareSerial.h>
#include <U8glib.h>

// uncomment for SPI-interface
//U8GLIB_SH1106_128X64 u8g(12, 11, 8, 9, 10);  // D0=12, D1=11, CS=8, DC=9, Reset=10
// uncomment for I2C-interface
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0); // I2C / TWI // Leonardo: SCL=3, SCA=2, UNO: SCL=A5, SDA=A4

SoftwareSerial mySerial(3, 4); // RX, TX

// coinAcceptor
int kr = 0;
int kr1 = 0;
int kr5 = 0;
int kr10 = 0;
int kr20 = 0;
#define pulseCount20kr  2
#define pulseCount10kr  3
#define pulseCount5kr  4
#define pulseCount1kr 5

int i = 0;
void printCoinCounterStandard() {
  Serial.print("Coin: ");
  Serial.print(i);
/*  
  Serial.print(",  Millis: ");
  Serial.print(puls_last_millis-coin_start_millis);
  if (puls_last_millis-coin_start_millis>maxMillis) maxMillis=puls_last_millis-coin_start_millis;
  Serial.print(", MinStart: ");
  Serial.print(minPulseStartMillis);
  Serial.print(", MaxMillis: ");
  Serial.print(maxMillis);
*/
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


void updateDisplay() {
u8g.firstPage();  
  do {
    u8g.setFont(u8g_font_7x13);  //u8g_font_helvB24
    u8g.drawStr(0, 0+13, "1  :"); 
    u8g.drawStr(0, 0+13*2, "5  :"); 
    u8g.drawStr(127-9*7, 0+13, "10  :"); 
    u8g.drawStr(127-9*7, 0+13*2, "20  :"); 

    u8g.setFont(u8g_font_5x8);  //u8g_font_helvB24
    u8g.drawStr(7+2, 0+13, "kr"); 
    u8g.drawStr(7+2, 0+13*2, "kr"); 
    u8g.drawStr(127-9*7+2*7+2, 0+13, "kr"); 
    u8g.drawStr(127-9*7+2*7+2, 0+13*2, "kr"); 

    u8g.setFont(u8g_font_7x13);  //u8g_font_helvB24
    char chrArray[10];
    String coins = String(kr1);
    coins.toCharArray(chrArray,10);
    u8g.drawStr(5*7+(3-coins.length())*7, 0+13, chrArray); 
    coins = String(kr5);
    coins.toCharArray(chrArray,10);
    u8g.drawStr(35+(3-coins.length())*7, 0+13*2, chrArray); 
    coins = String(kr10);
    coins.toCharArray(chrArray,10);
    u8g.drawStr(127-3*7+(3-coins.length())*7, 0+13, chrArray); 
    coins = String(kr20);
    coins.toCharArray(chrArray,10);
    u8g.drawStr(127-3*7+(3-coins.length())*7, 0+13*2, chrArray); 
    
    u8g.setFont(u8g_font_ncenR24);  
    coins = String(kr);
    if (kr>999) {
      // add thousand delimiter
      int coinLength = coins.length();
      coins = coins.substring(1,coinLength-4) + "." + coins.substring(coinLength-3,coinLength);
      Serial.println(coins);
    } else {
      // fix length for <1000
      coins = " " + coins; 
    }
    coins.toCharArray(chrArray,10);
    int fontWidth = 18;
    u8g.drawStr(0+(6-coins.length())*fontWidth, 63, chrArray); 

    u8g.setFont(u8g_font_9x15);  //u8g_font_helvB24
    u8g.drawStr(127-2*9, 63, "kr"); 
  } while( u8g.nextPage() );
}

void setup() {
  Serial.begin(115200);

  mySerial.begin(9600);

  int counter=0;
}

int numCoins=0;

int loopCounter=0;
void loop() {
  updateDisplay();
  if (mySerial.available()) {
    byte coin = mySerial.read();
    if (coin==pulseCount20kr) {kr20++; kr += 20;}
    else if (coin==pulseCount10kr) {kr10++; kr += 10;}
    else if (coin==pulseCount5kr) {kr5++; kr += 5;}
    else if (coin==pulseCount1kr) {kr1++; kr += 1;}
  
    i = coin;
    numCoins++;
    printCoinCounterStandard();
    //Serial.println(coin,HEX);
  }
  if (Serial.available()) {
    byte rx=Serial.read();
    if (rx=='c') {
      kr=0;
      kr1=0;
      kr5=0;
      kr10=0;
      kr20=0;
      i=0;
      Serial.println("\nReset Counters\n");
      printCoinCounterStandard();
      numCoins=0;
    }
  }

}

void displayTest(){
    u8g.firstPage();
  do {
        u8g.setFont(u8g_font_7x13);  //u8g_font_helvB24
    u8g.drawStr(5*7, 0+13, "  0"); 
    u8g.drawStr(35, 0+13*2, "  0"); 
    u8g.drawStr(127-3*7, 0+13, "  0"); 
    u8g.drawStr(127-3*7, 0+13*2, "  0"); 

  } while( u8g.nextPage() );
}
