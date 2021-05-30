/*
   Remove the Bluetooth Module before connecting the Arduino to the Arduino IDE !!!
   You will need all 4 control signals, even if you have only 1 DC motor right and 1 DC motor left !!!!

   Left Motor truth table
   ----------------------------------------------------------------------------
   ENA         IN1             IN2         Description
   LOW   Not Applicable   Not Applicable   Motor is off
   HIGH        LOW             LOW         Motor is stopped (brakes)
   HIGH        LOW             HIGH        Motor is on and turning forwards
   HIGH        HIGH            LOW         Motor is on and turning backwards
   HIGH        HIGH            HIGH        Motor is stopped (brakes)

   Right Motor truth table
   ----------------------------------------------------------------------------
   ENB         IN3             IN4         Description
   LOW   Not Applicable   Not Applicable   Motor is off
   HIGH        LOW             LOW         Motor is stopped (brakes)
   HIGH        LOW             HIGH        Motor is on and turning forwards
   HIGH        HIGH            LOW         Motor is on and turning backwards
   HIGH        HIGH            HIGH        Motor is stopped (brakes)
*/

/*
   SERVO Motor
*/
#include <Servo.h> // Command to insert the Servo library into your program.

int servoPin = 3; // Port to control the servo Motor
// Start position of the Servo, stright wheels (only executed at begining)
// Max. range right is 30° and max. range left is 130°
int servoCenterPos = 85;
int servoLeftmax = 105;
int servoRightmax = 65;
int oldServoPos = 85;
int newServoPos= 85;

Servo myServo; // Create a virtual object into your Arduino so you can interact with it.
// Also give it a name (myServo).

/*
   Line Tracking
*/
#define LT_L 2 // Left Sensor
#define LT_M 4 // Middle Sensor
#define LT_R 10 // Right Sensor


void setup() {
  Serial.begin(115200);

  /*
    SERVO Motor
  */
  // Attach the virtual Servo (object) to your Arduino using the control pin to interact with it.
  myServo.attach(servoPin);
  // The Servo will start at the configured Start position of the Servo.
  myServo.write(servoCenterPos);

  /*
    Line Tracking
  */
  pinMode(LT_L, INPUT);
  pinMode(LT_M, INPUT);
  pinMode(LT_R, INPUT);
}


void loop() {
  /*
    Line Tracking: 0 is Black Line, 1 is no Black Line
  */
  Serial.print("LT_L: ");
  Serial.print(digitalRead(LT_L));
  Serial.print("  LT_M: ");
  Serial.print(digitalRead(LT_M));
  Serial.print("  LT_R: ");
  Serial.println(digitalRead(LT_R));

  // If a Black Line is detected by the Left Sensor
  if (digitalRead(LT_L) == 0 && digitalRead(LT_M) == 1 && digitalRead(LT_R) == 1) {
    if (oldServoPos == servoLeftmax) { // Case 1
      myServo.write(servoLeftmax);
    }
    if (oldServoPos == servoCenterPos) { // Case 2
      for (int i = oldServoPos ; i <= servoLeftmax ; i++) {
        newServoPos = i;
        myServo.write(newServoPos);
        delay(5);
      }
      oldServoPos = newServoPos;
    }
    if (oldServoPos == servoRightmax) { // Case 3
      for (int i = oldServoPos ; i <= servoLeftmax ; i++) {
        newServoPos = i;
        myServo.write(newServoPos);
        delay(5);
      }
      oldServoPos = newServoPos;
    }
  }
  // If a Black Line is detected by the Right Sensor
  if (digitalRead(LT_L) == 1 && digitalRead(LT_M) == 1 && digitalRead(LT_R) == 0) {
    if (oldServoPos == servoRightmax) { // Case 1
      myServo.write(servoRightmax);
    }
    if (oldServoPos == servoCenterPos) { // Case 2
      for (int i = oldServoPos ; i >= servoRightmax ; i--) {
        newServoPos = i;
        myServo.write(newServoPos);
        delay(5);
      }
      oldServoPos = newServoPos;
    }
    if (oldServoPos == servoLeftmax) { // Case 3
      for (int i = oldServoPos ; i >= servoRightmax ; i--) {
        newServoPos = i;
        myServo.write(newServoPos);
        delay(5);
      }
      oldServoPos = newServoPos;
    }
  }
  // If a Black Line is detected by the middle Sensor
  if (digitalRead(LT_L) == 1 && digitalRead(LT_M) == 0 && digitalRead(LT_R) == 1) {
    if (oldServoPos == servoCenterPos) { // Case 1
      myServo.write(servoCenterPos);
    }
    if (oldServoPos > servoCenterPos) { // Case 2
      for (int i = oldServoPos ; i >= servoCenterPos ; i--) {
        newServoPos = i;
        myServo.write(newServoPos);
        delay(5);
      }
      oldServoPos = newServoPos;
    }
    if (oldServoPos < servoCenterPos) { // Case 3
      for (int i = oldServoPos ; i <= servoCenterPos ; i++) {
        newServoPos = i;
        myServo.write(newServoPos);
        delay(5);
      }
      oldServoPos = newServoPos;
    }
  }
  Serial.print("oldServoPos = ");
  Serial.print(oldServoPos);
  Serial.print("  newServoPos = ");
  Serial.println(newServoPos);
  delay(500);
}
