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
 * Line Tracking
*/
#define LT_L 2 // Left Sensor
#define LT_M 4 // Middle Sensor
#define LT_R 10 // Right Sensor

/*
 * LEDs
*/
#define LED_LF 14 // LED Left Front
#define LED_RF 15 // LED Right Front
#define LED_LB 53 // LED Left Back
#define LED_RB 52 // LED Right Back


void setup(){
  Serial.begin(115200);

  /*
  * Line Tracking
  */
  pinMode(LT_L, INPUT);
  pinMode(LT_M, INPUT);
  pinMode(LT_R, INPUT);

  /*
  * LEDs
  */
  pinMode(LED_LF, OUTPUT);
  pinMode(LED_RF, OUTPUT);
  pinMode(LED_LB, OUTPUT);
  pinMode(LED_RB, OUTPUT);
}


void loop() {
  /*
  * Line Tracking: 0 is Black Line, 1 is no Black Line
  */
  Serial.print("LT_L: ");
  Serial.print(digitalRead(LT_L));
  Serial.print("  LT_M: ");
  Serial.print(digitalRead(LT_M));
  Serial.print("  LT_R: ");
  Serial.println(digitalRead(LT_R));
  
  /*
  * LEDs
  */
  digitalWrite(LED_LF, HIGH);
  digitalWrite(LED_RF, HIGH);
  digitalWrite(LED_LB, HIGH);
  digitalWrite(LED_RB, HIGH);
  
  delay(500);
}
