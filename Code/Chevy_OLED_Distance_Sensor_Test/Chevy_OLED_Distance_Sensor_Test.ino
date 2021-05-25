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

   OLED Screen MEGA2560: SDA (20); SCL (21)
*/


/*
   Include the necessary libraries
*/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSerifBoldItalic12pt7b.h> // The fonts that work better with the OLED display are the 9 and 12 points size.

/*
   128x64 OLED Screen
*/
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/*
   HC-SR04 Distance Sensor
*/
int trigPin = 27;    // Trigger
int echoPin = 29;    // Echo
// The average pingTravelDistance devided by 2 (/2)
float cm;
// Declare a counter for the distance measure iterations.
int j;
// Number of distance measurements to be averaged.
int numMeas = 65; // 15 microseconds * 65 = 975 microseconds (1 millisecond)
// Sum of all Ping RTT's (bucket)
float pingTravelTimeSum;
// Average of all Ping RTT's
float pingTravelTimeAverage;
// The total pingTravelDistance (RTT, two-way)


//-----------------------------------------------------------------------------------------

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
  delay(2000);
  // Prepare the Display for dynamic text
  display.setFont();
  display.setTextSize(2);
  display.invertDisplay(false);

  /*
    HC-SR04 Distance Sensor
  */
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

//-----------------------------------------------------------------------------------------

void loop() {

  /*
    HC-SR04 Distance Sensor
  */
  
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  pingTravelTimeSum = 0; // reset before every measuring loop !!!! 

  for (j = 1; j <= numMeas; j++) {
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
    pingTravelTimeSum += pulseIn(echoPin, HIGH);
  }
  pingTravelTimeAverage = pingTravelTimeSum / numMeas;
  // Convert the time into a distance
  // distance = (traveltime/2) x speed of sound
  // We need to divide the traveltime by 2 because we have to take into account that the wave was sent,
  // hit the object, and then returned back to the sensor.
  // The speed of sound is: 343m/s = 0.0343 cm/uS = 1/29.1 cm/uS
  // Divide by 29.1 or multiply by 0.0343 (Speed of sound)
  cm = (pingTravelTimeAverage / 2.) / 29.1; 

  /*
    128x64 OLED Screen
  */
  display.clearDisplay();
  // Display the measured distance on the OLED
  display.setCursor(0, 0);
  // Display static text
  display.println("Distance:");
  display.print(cm);
  display.println("cm");
  display.setCursor(0, 45);
  // If the distance to the object is larger or equal to 20, then DRIVE !!!
  if (cm >= 20.0) {
    display.println("OK, DRIVE");
  }
  // Else STOP the Car !!!
  else {
    display.println("STOP CAR !");
  }
  display.display();
}
