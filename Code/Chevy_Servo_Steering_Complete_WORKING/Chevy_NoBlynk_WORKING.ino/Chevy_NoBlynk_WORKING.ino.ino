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

   BIG NOTE*: BLYNK Server will interfere with the servo's response time, so try to avoid sending 
   data while driving !!!!!!!!!!!!!
*/

// BLYNK info in Serial Monitor (Comment this out to disable prints and save space.
// #define BLYNK_PRINT Serial

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
// #include <ESP8266_Lib.h> // Library for ESP-01 Wi-Fi Module
// #include <BlynkSimpleShieldEsp8266.h> // Library for ESP-01 Wi-Fi Module talking to BLYNK Server

/*
   BLYNK Server
*/
// char server[] = "192.168.10.122";
// #define port 8080

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
// char auth[] = "SYbg29M3AiMlp83wB2HOlAhRHZ6wc1w_";

// Your WiFi credentials.
// Set password to "" for open networks.
// char ssid[] = "BLYNK"; // Use the Orange modem Wi-Fi
// char pass[] = "Bucky196";


// Hardware Serial on Mega, Leonardo, Micro...
// #define EspSerial Serial1

// or Software Serial on Uno, Nano...
//#include <SoftwareSerial.h>
//SoftwareSerial EspSerial(2, 3); // RX, TX

// Your ESP8266 baud rate:
// #define ESP8266_BAUD 115200

// ESP8266 wifi(&EspSerial);

// BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
//void myTimerEvent()
//{
//  // You can send any value at any time.
//  // Please don't send more that 10 values per second !!!!!!!!!
//  Blynk.virtualWrite(V5, millis() / 1000);
//}

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
int servoLeftmax = 110; // Turn Left // 105
int servoRightmax = 60; // Turn Right // 65

Servo myServo; // Create a virtual object into your Arduino so you can interact with it.
// Also give it a name (myServo).

/*
   LEDs
*/
#define redLED 35 // red LED on top of car (signalisation)
#define yellowLED 33 // yellow LED on top of car (signalisation)
#define greenLED 31 // green LED on top of car (signalisation)
#define LED_LF 22 // LED Left Front
#define LED_RF 23 // LED Right Front
#define LED_LB 53 // LED Left Back
#define LED_RB 52 // LED Right Back

// Red LED On
void RedLEDsOn(){
  digitalWrite(redLED, HIGH), digitalWrite(yellowLED, LOW), digitalWrite(greenLED, LOW);
}

// Yellow LED On
void YellowLEDsOn(){
  digitalWrite(redLED, LOW), digitalWrite(yellowLED, HIGH), digitalWrite(greenLED, LOW);
}

// Green LED On
void GreenLEDsOn(){
  digitalWrite(redLED, LOW), digitalWrite(yellowLED, LOW), digitalWrite(greenLED, HIGH);
}

/*
   Push-Button
*/
#define pushButton 45
int museum_timer;

/*
   Line Tracking Sensor
*/
#define LT_L 2 // Left Sensor
#define LT_M 4 // Middle Sensor
#define LT_R 10 // Right Sensor
int linelost_timer = 0;

/*
   HC-SR04 Distance Sensor
*/
int trigPin = 27;    // Trigger
int echoPin = 29;    // Echo
// The pingTravelDistance devided by 2 (/2)
float cm;

// The total pingTravelTime (RTT, two-way)
int pingTravelTime;

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
   DC Motors - L298N I/O Pins
*/
int ENA = 5;  // Control Channel A for left wheel
int ENB = 6;  // Control Channel B for right wheel
int IN1 = 7;  // Control Signal 1 for left wheel
int IN2 = 8;  // Control Signal 2 for left wheel
int IN3 = 9;  // Control Signal 3 for right wheel
int IN4 = 11; // Control Signal 4 for right wheel

// set car speed
int CAR_SPEED_F = 80; // Car Speed for Driving Forward 255 is Max. , Min. is 70.
int CAR_SPEED_T = 80; // Car Speed for Turning 255 is Max. , Min. is 70.

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
}

void turnLeft(int car_speed) {
  analogWrite(ENA, car_speed);
  analogWrite(ENB, car_speed);
  digitalWrite(IN1, HIGH); // IN1 = 1
  digitalWrite(IN2, LOW); // IN2 = 0
  digitalWrite(IN3, LOW); // IN3 = 0
  digitalWrite(IN4, HIGH); // IN4 = 1
}

void turnRight(int car_speed) {
  analogWrite(ENA, car_speed);
  analogWrite(ENB, car_speed);
  digitalWrite(IN1, HIGH); // IN1 = 1
  digitalWrite(IN2, LOW); // IN2 = 0
  digitalWrite(IN3, LOW); // IN3 = 0
  digitalWrite(IN4, HIGH); // IN4 = 1
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

// Function while halting at an exhibit.
void OLED_sightseeing() {
  display.clearDisplay();
  // Display the measured distance on the OLED
  display.setCursor(0, 0);
  // Display static text
  display.println("Exhibit");
  display.setCursor(0, 30);
  display.println("Time Left:");
  display.print(museum_timer/1000);
  display.println(" Sec.");
  display.display();
}

//----------------------------------------------------------------------------------------------------

void setup() {
  
  // Debug console Serial Monitor
  Serial.begin(115200);

  /*
   BLYNK Server
  */
  
//  // Set ESP8266 baud rate
//  EspSerial.begin(ESP8266_BAUD);
//  delay(10);
//
//  // You can also specify server:
//  // Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 80);
//  // Own Server and port
//  Blynk.begin(auth, wifi, ssid, pass, server, port);
//
//  // Setup a function to be called every second
//  timer.setInterval(1000L, myTimerEvent);

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
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(LED_LF, OUTPUT);
  pinMode(LED_RF, OUTPUT);
  pinMode(LED_LB, OUTPUT);
  pinMode(LED_RB, OUTPUT);
  digitalWrite(LED_LF, HIGH);
  digitalWrite(LED_RF, HIGH);
  digitalWrite(LED_LB, HIGH);
  digitalWrite(LED_RB, HIGH);

  /*
   Push-Button
  */
  pinMode(pushButton, INPUT);

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
   BLYNK Server
  */
//  Blynk.run(); // Maintain the connection and send & receive data
//  timer.run(); // Initiates BlynkTimer

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

  // If no Black Line is detected by Left (LT-L) or Right (LT-R) sensor.
  if (digitalRead(LT_L) && digitalRead(LT_R)) { // Drive Forward
    forward(CAR_SPEED_F);
    myServo.write(servoCenterPos);
    GreenLEDsOn();
    linelost_timer += 1;
    Serial.println(linelost_timer);
    if (linelost_timer >= 50) {
      stop_car();
      RedLEDsOn();
    }
  }

  // If a Black Line is detected by the Left Sensor.
  else if (!(digitalRead(LT_L)) && digitalRead(LT_R)) { // Turn Left
    turnLeft(CAR_SPEED_T);
    myServo.write(servoLeftmax);
    GreenLEDsOn();
    linelost_timer = 0;
    Serial.println(linelost_timer);
  }

  // If a Black Line is detected by the Right Sensor.
  else if (digitalRead(LT_L) && !(digitalRead(LT_R))) { // Turn Right
    turnRight(CAR_SPEED_T);
    myServo.write(servoRightmax);
    GreenLEDsOn();
    linelost_timer = 0;
    Serial.println(linelost_timer);
  }

  // If black perpendicular line is detected
  // Halt Car for 20 seconds, unless hardware or Virtual (BLYNK) push-button is pushed
  else if (!(digitalRead(LT_L)) && !(digitalRead(LT_M)) && !(digitalRead(LT_R))) { 
    YellowLEDsOn();
    delay(500); // Wait 500ms before halting the car
    myServo.write(servoCenterPos);
    stop_car();
    museum_timer = 20000; // Halt Car for 10 seconds
    linelost_timer = 0;
    Serial.println(linelost_timer);
    while (museum_timer >= 0){
      museum_timer -= 200; // subtract 200ms from timer
      OLED_sightseeing();
      delay(200); // delay 200ms after subtrackting from timer
      // measure_distance(); // Not needed while halting for sight seeing
//      Blynk.run(); // Otherwise BLYNK will crash while in the loop
//      timer.run(); // Otherwise BLYNK will crash while in the loop
      if (digitalRead(pushButton) == 1){
        break;
      }
    }
  }

  measure_distance();

  // While the distance to the object is smaller or equal to 20, then STOP the CAR !!!
  while (cm < 20.0) {
    OLED_stopcar();
    stop_car();
    YellowLEDsOn();
    measure_distance();
//    Blynk.run(); // Otherwise BLYNK will crash while in the loop
//    timer.run(); // Otherwise BLYNK will crash while in the loop
  }

  OLED_okdrive();
}
