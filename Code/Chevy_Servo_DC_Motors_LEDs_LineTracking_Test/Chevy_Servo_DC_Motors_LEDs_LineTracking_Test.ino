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

/*
   DC Motors - L298N I/O Pins
*/
int ENA = 5;  // Control Channel A for left wheel
int ENB = 6;  // Control Channel B for right wheel
int IN1 = 7;  // Control Signal 1 for left wheel
int IN2 = 8;  // Control Signal 2 for left wheel
int IN3 = 9;  // Control Signal 3 for right wheel
int IN4 = 11; // Control Signal 4 for right wheel

//set car speed
int CAR_SPEED = 70; // 255 is Max. , Min. is .....

void start_car() {
  digitalWrite(ENA, HIGH); // Start the car
  digitalWrite(ENB, HIGH); // Start the car
  delay(500);
}

void stop_car() {
  digitalWrite(IN1, LOW); // IN1 = 0
  digitalWrite(IN2, LOW); // IN2 = 0
  digitalWrite(IN3, LOW); // IN3 = 0
  digitalWrite(IN4, LOW); // IN4 = 0
  // delay(1000);
}



void forward(int car_speed){
  analogWrite(ENA, car_speed);
  analogWrite(ENB, car_speed);
  servoPos = 80;
  myServo.write(servoPos); // Tell the Servo to go to a certain position.
  digitalWrite(IN1, HIGH); // IN1 = 1
  digitalWrite(IN2, LOW); // IN2 = 0
  digitalWrite(IN3, LOW); // IN3 = 0
  digitalWrite(IN4, HIGH); // IN4 = 1
  // Keep driving forward untill "stop_car()" Function !!!!
}

void left(int car_speed){
  digitalWrite(ENA, car_speed); // Drive at configured Speed
  digitalWrite(ENB, car_speed); // Drive at configured Speed
  servoPos = 130;
  myServo.write(servoPos); // Tell the Servo to go to a certain position.
  digitalWrite(IN1, HIGH); // IN1 = 1
  digitalWrite(IN2, LOW); // IN2 = 0
  digitalWrite(IN3, LOW); // IN3 = 0
  digitalWrite(IN4, HIGH); // IN4 = 1
}

void right(int car_speed){
  digitalWrite(ENA, car_speed); // Drive at configured Speed
  digitalWrite(ENB, car_speed); // Drive at configured Speed
  servoPos = 30;
  myServo.write(servoPos); // Tell the Servo to go to a certain position.
  digitalWrite(IN1, HIGH); // IN1 = 1
  digitalWrite(IN2, LOW); // IN2 = 0
  digitalWrite(IN3, LOW); // IN3 = 0
  digitalWrite(IN4, HIGH); // IN4 = 1
}


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
    Line Tracking
  */
  pinMode(LT_L, INPUT);
  pinMode(LT_M, INPUT);
  pinMode(LT_R, INPUT);

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
    DC Motors
  */
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
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
  if (digitalRead(LT_L) == 0 && digitalRead(LT_R) == 1) {
    left(CAR_SPEED);
  }
//  // If a Black Line is detected by the middle Sensor
//  if (digitalRead(LT_L) == 1 && digitalRead(LT_M) == 0 && digitalRead(LT_R) == 1) {
//    car_drive_forward(CAR_SPEED);
//  }
  // If a Black Line is detected by the Right Sensor
  else if (digitalRead(LT_L) == 1 && digitalRead(LT_R) == 0) {
    right(CAR_SPEED);
  }

  else{
    forward(CAR_SPEED);
  }

//  // If a Black Line is NOT detected by any of the Sensors
//  if ((digitalRead(LT_L) == 1 && digitalRead(LT_M) == 1 && digitalRead(LT_R) == 1) || 
//     (digitalRead(LT_L) == 0 && digitalRead(LT_M) == 0 && digitalRead(LT_R) == 0)) {
//    stop_car();
//    servoPos = 80;
//    myServo.write(servoPos); // Tell the Servo to go to a certain position.
//  }
}
