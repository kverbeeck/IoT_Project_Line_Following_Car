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
int servoPos;
// Start position of the Servo, stright wheels (only executed at begining)
// Max. range right is 40° and max. range left is 130°
int servoStartPos = 80;

Servo myServo; // Create a virtual object into your Arduino so you can interact with it.
// Also give it a name (myServo).

/*
   LEDs
*/
#define LED_LF 14 // LED Left Front
#define LED_RF 15 // LED Right Front
#define LED_LB 53 // LED Left Back
#define LED_RB 52 // LED Right Back

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
  myServo.write(servoStartPos);

  /*
   LEDs
  */
  pinMode(LED_LF, OUTPUT);
  pinMode(LED_RF, OUTPUT);
  pinMode(LED_LB, OUTPUT);
  pinMode(LED_RB, OUTPUT);
  digitalWrite(LED_LF, HIGH);
  digitalWrite(LED_RF, HIGH);
  digitalWrite(LED_LB, HIGH);
  digitalWrite(LED_RB, HIGH);

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
  if (digitalRead(LT_L) == 0) {
    servoPos = 130;
    myServo.write(servoPos); // Tell the Servo to go to a certain position.
    // delay(1000); // Delay needed for Servo to reach position
  }
  // If a Black Line is detected by any of the Sensors
  if (digitalRead(LT_M) == 0) {
    servoPos = 80;
    myServo.write(servoPos); // Tell the Servo to go to a certain position.
    // delay(1000); // Delay needed for Servo to reach position
  }
  // If a Black Line is detected by the Right Sensor
  if (digitalRead(LT_R) == 0) {
    servoPos = 40;
    myServo.write(servoPos); // Tell the Servo to go to a certain position.
    // delay(1000); // Delay needed for Servo to reach position
  }
  
}
