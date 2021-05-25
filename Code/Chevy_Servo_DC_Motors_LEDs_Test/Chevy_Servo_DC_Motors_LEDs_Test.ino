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
   DC Motors
*/
int ENA = 5;  // Control Channel A for left wheels
int ENB = 6;  // Control Channel B for right wheels
int IN1 = 7;  // Control Signal 1 for left wheels
int IN2 = 8;  // Control Signal 2 for left wheels
int IN3 = 9;  // Control Signal 3 for right wheels
int IN4 = 11; // Control Signal 4 for right wheels

void start_car() {
  digitalWrite(ENA, HIGH); // Start the car
  digitalWrite(ENB, HIGH); // Start the car
  delay(500);
}

void stop_car() {
  digitalWrite(IN1, LOW); // IN1 = 0
  digitalWrite(IN2, LOW);  // IN2 = 0
  digitalWrite(IN3, LOW);  // IN3 = 0
  digitalWrite(IN4, LOW); // IN4 = 0
  delay(1000);
}

void car_drive_forward() {
  digitalWrite(IN1, HIGH); // IN1 = 1
  digitalWrite(IN2, LOW);  // IN2 = 0
  digitalWrite(IN3, LOW);  // IN3 = 0
  digitalWrite(IN4, HIGH); // IN4 = 1
  delay(2000); // Start Servo after 2 seconds
  // Keep driving forward untill "stop_car()" Function !!!!
}

void car_drive_backward() {
  digitalWrite(IN1, LOW);  // IN1 = 0
  digitalWrite(IN2, HIGH); // IN2 = 1
  digitalWrite(IN3, HIGH); // IN3 = 1
  digitalWrite(IN4, LOW);  // IN4 = 0
  delay(2000); // Start Servo after 2 seconds
  // Keep driving forward untill "stop_car()" Function !!!! 
}

void car_turn_left() {
  servoPos = 130;
  myServo.write(servoPos); // Tell the Servo to go to a certain position.
  delay(1000); // Delay needed for Servo to reach position
}

void car_turn_right() {
  servoPos = 40;
  myServo.write(servoPos); // Tell the Servo to go to a certain position.
  delay(1000); // Delay needed for Servo to reach position
}

void car_drive_straight() {
  servoPos = 80;
  myServo.write(servoPos); // Tell the Servo to go to a certain position.
  delay(1000); // Delay needed for Servo to reach position
}


void setup() {
  // put your setup code here, to run once:
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
    DC Motors
  */
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN4, OUTPUT);
  // digitalWrite(ENA, HIGH); // We can leave these Control channels enabled (Left Wheels)
  // digitalWrite(ENB, HIGH); // We can leave these Control channels enabled (Right Wheels)

  start_car();
}


void loop() {
  // put your main code here, to run repeatedly:

  car_turn_left();
  car_turn_right();
  car_drive_straight();

  car_drive_forward();

  car_turn_left();
  car_turn_right();
  car_drive_straight();

  stop_car();

  car_turn_left();
  car_turn_right();
  car_drive_straight();

  car_drive_backward();

  car_turn_left();
  car_turn_right();
  car_drive_straight();

  stop_car();
}