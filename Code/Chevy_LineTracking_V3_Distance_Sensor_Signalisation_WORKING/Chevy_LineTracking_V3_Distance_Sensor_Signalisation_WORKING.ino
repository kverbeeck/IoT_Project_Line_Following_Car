/*
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

   OLED Screen 128x64 connected to MEGA2560: SDA (20); SCL (21)
*/

/*
   Include the necessary libraries
*/
#include <Wire.h> // I2C Library
// Core graphics library for all Adafruit displays, providing a common set of graphics primitives (points, lines, circles, etc.).
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> // Library for Adafruit Monochrome OLEDs based on SSD1306 drivers.
// The fonts that work better with the OLED display are the 9 and 12 points size.
#include <Fonts/FreeSerifBoldItalic12pt7b.h>
#include <Servo.h> // Servo library

/*
   128x64 OLED Screen
*/
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/*
   SERVO Motor: HS-422 (20Kg)
*/
int servoPin = 3; // Port to control the servo Motor
// Start position of the Servo, stright wheels (only executed at begining)
int servoStartPos = 85;
int servoCenterPos = 85; // Drive Forward
int servoLeftmax = 105; // Turn Left
int servoRightmax = 65; // Turn Right

Servo myServo; // Create a virtual object into your Arduino so you can interact with it.
// Also give it a name (myServo).

/*
   LEDs
*/
#define LED_LF 22 // LED Left Front
#define LED_RF 23 // LED Right Front
#define LED_LB 53 // LED Left Back
#define LED_RB 52 // LED Right Back
#define LED_LF 22 // LED Left Front
#define redLED 35 // red LED on top of car (signalisation)
#define yellowLED 33 // yellow LED on top of car (signalisation)
#define greenLED 31 // green LED on top of car (signalisation)

/*
   Line Tracking Sensor
*/
#define LT_L 2 // Left Sensor
#define LT_M 4 // Middle Sensor
#define LT_R 10 // Right Sensor

/*
   HC-SR04 Distance Sensor
*/
int trigPin = 27;    // Trigger
int echoPin = 29;    // Echo
// The pingTravelDistance devided by 2 (/2)
float cm;

// The total pingTravelTime (RTT, two-way)
int pingTravelTime;

/*
   DC Motors - L298N I/O Pins
*/
int ENA = 5;  // Control Channel A for left wheel
int ENB = 6;  // Control Channel B for right wheel
int IN1 = 7;  // Control Signal 1 for left wheel
int IN2 = 8;  // Control Signal 2 for left wheel
int IN3 = 9;  // Control Signal 3 for right wheel
int IN4 = 11; // Control Signal 4 for right wheel

// set car speed
int CAR_SPEED = 90; // 255 is Max. , Min. is 70

void stop_car() {
  digitalWrite(IN1, LOW); // IN1 = 0
  digitalWrite(IN2, LOW); // IN2 = 0
  digitalWrite(IN3, LOW); // IN3 = 0
  digitalWrite(IN4, LOW); // IN4 = 0
}

void forward(int car_speed) {
  analogWrite(ENA, car_speed);
  analogWrite(ENB, car_speed);
  digitalWrite(IN1, HIGH); // IN1 = 1
  digitalWrite(IN2, LOW); // IN2 = 0
  digitalWrite(IN3, LOW); // IN3 = 0
  digitalWrite(IN4, HIGH); // IN4 = 1
  // Keep driving forward untill "stop_car()" Function !!!!
}

/*
   HC-SR04 Distance Sensor
*/
void measure_distance() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.

  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  // Delay to make sure that the triggerpin has been set to low.
  delayMicroseconds(5);
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  // (RTT, two-way)
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pingTravelTime = pulseIn(echoPin, HIGH);

  // Convert the time into a distance
  // distance = (traveltime/2) x speed of sound
  // We need to divide the traveltime by 2 because we have to take into account that the wave was sent,
  // hit the object, and is then returned back to the sensor.
  // The speed of sound is: 343m/s = 0.0343 cm/uS = 1/29.1 cm/uS
  // Divide by 29.1 or multiply by 0.0343 (Speed of sound)
  cm = (pingTravelTime / 2.) / 29.1;
}

/*
   128x64 OLED Screen
*/
void OLED_okdrive() {
  display.clearDisplay();
  // Display the measured distance on the OLED
  display.setCursor(0, 0);
  // Display static text
  display.println("Distance:");
  display.print(cm);
  display.println("cm");
  display.setCursor(0, 45);
  display.println("OK, DRIVE");
  display.display();
}

void OLED_stopcar() {
  display.clearDisplay();
  // Display the measured distance on the OLED
  display.setCursor(0, 0);
  // Display static text
  display.println("Distance:");
  display.print(cm);
  display.println("cm");
  display.setCursor(0, 45);
  display.println("STOP CAR !");
  display.display();
}

//----------------------------------------------------------------------------------------------------

void setup() {

  Serial.begin(115200);

  /*
    128x64 OLED Screen
  */

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  // 0x3C is I2C address
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Clear the buffer.
  display.clearDisplay();
  // display.setTextSize(1);
  display.setFont(&FreeSerifBoldItalic12pt7b);
  display.setTextColor(WHITE);
  display.invertDisplay(true);
  display.setCursor(20, 40);
  // Display static text (CHEVY WELCOME SCREEN)
  display.println("CHEVY");
  display.display();
  delay(1000);
  // Prepare the Display for dynamic text
  display.setFont();
  display.setTextSize(2);
  display.invertDisplay(false);
  delay(1000);

  /*
    SERVO Motor
  */
  // Attach the virtual Servo (object) to your Arduino using the control pin to interact with it.
  myServo.attach(servoPin);
  // The Servo will start at the configured Start position of the Servo.
  myServo.write(servoStartPos);

  /*
    Line Tracking Sensor
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
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  digitalWrite(redLED, HIGH);
  digitalWrite(yellowLED, HIGH);
  digitalWrite(greenLED, HIGH);

  /*
    DC Motors
  */
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  /*
     HC-SR04 Distance Sensor
  */
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

//----------------------------------------------------------------------------------------------------

void loop() {

  /*
     Line Tracking Sensor
  */

  // Print Line Tracking Sensor State: 0 is Black Line, 1 is no Black Line

  //  Serial.print("LT_L: ");
  //  Serial.print(digitalRead(LT_L));
  //  Serial.print("  LT_M: ");
  //  Serial.print(digitalRead(LT_M));
  //  Serial.print("  LT_R: ");
  //  Serial.println(digitalRead(LT_R));

  // If a Black Line is detected by the Left Sensor.
  if (!(digitalRead(LT_L)) && digitalRead(LT_R)) { // Turn Left
    forward(CAR_SPEED);
    myServo.write(servoLeftmax);
  }

  // If a Black Line is detected by the Right Sensor.
  else if (digitalRead(LT_L) && !(digitalRead(LT_R))) { // Turn Right
    forward(CAR_SPEED);
    myServo.write(servoRightmax);
  }

  // If no Black Line is detected by Left (LT-L) or Right (LT-R) sensor.
  else if (digitalRead(LT_L) && digitalRead(LT_R)) { // Drive Forward
    forward(CAR_SPEED);
    myServo.write(servoCenterPos);
  }

  // If black perpendicular line is detected
  else if (!(digitalRead(LT_L)) && !(digitalRead(LT_M)) && !(digitalRead(LT_R))) { // Stop Car
    myServo.write(servoCenterPos);
    stop_car();
  }

  measure_distance();

  // While the distance to the object is smaller or equal to 20, then STOP the CAR !!!
  while (cm < 20.0) {
    OLED_stopcar();
    stop_car();
    measure_distance();
  }

  OLED_okdrive();
}
