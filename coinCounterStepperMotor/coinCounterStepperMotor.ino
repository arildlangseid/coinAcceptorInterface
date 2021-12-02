/* Example sketch to control a 28BYJ-48 stepper motor with ULN2003 driver board, AccelStepper and Arduino UNO: continuous rotation. More info: https://www.makerguides.com */
// Include the AccelStepper library:
#include <AccelStepper.h>

// Motor pin definitions:
#define motorPin1  4      // IN1 on the ULN2003 driver
#define motorPin2  5      // IN2 on the ULN2003 driver
#define motorPin3  6     // IN3 on the ULN2003 driver
#define motorPin4  7     // IN4 on the ULN2003 driver
// Define the AccelStepper interface type; 4 wire motor in half step mode:
#define MotorInterfaceType 8
// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper library with 28BYJ-48 stepper motor:
//AccelStepper stepper = AccelStepper(MotorInterfaceType, motorPin1, motorPin3, motorPin2, motorPin4);
//AccelStepper stepper = AccelStepper(AccelStepper::HALF4WIRE, motorPin1, motorPin3, motorPin2, motorPin4);
AccelStepper stepper = AccelStepper(AccelStepper::FULL4WIRE, motorPin1, motorPin3, motorPin2, motorPin4);


int motorTurnDir = -1; // either -1 or 1 to make the coindisc turn ccw
int motorSpeed = 2000; // Set motor speed to AccelStepper


bool motorRun = false;
unsigned long delayTimer = 0;
int motorUpdateInterval = 5000;

void setup() {
  Serial.begin(115200);
  
#ifdef ARDUINO_AVR_LEONARDO
  unsigned long timeOut = millis();
  while (!Serial && (millis()-timeOut < 3000)) {
    ; // wait for serial port to connect. Needed for native USB
  }
  Serial.println("Start CoinAcceptor Leonardo");
#endif

  // Set the maximum steps per second:
  stepper.setMaxSpeed(motorSpeed);
  stepper.setAcceleration(200);
  stepper.setSpeed(motorSpeed);
  stepper.setCurrentPosition(0);

  delayTimer = millis();
}

unsigned long timeNow = 0;
void loop() {
  timeNow = millis()-delayTimer;
  if ((motorRun == false) && timeNow <= 700) {
    // Accelerated start
    stepper.setCurrentPosition(0);
    stepper.moveTo(2000*motorTurnDir);
    motorRun = true;
    Serial.println("Start");
  }

  if ((motorRun==true) && timeNow <= motorUpdateInterval) {
    // set new moving target to make motor run continously
    stepper.move(512*motorTurnDir);
  }

  stepper.run();
  delayTimer = millis();
}
