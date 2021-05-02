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

//Line Tracking IO define
#define LT_R !digitalRead(10)
#define LT_M !digitalRead(4)
#define LT_L !digitalRead(2)


void setup(){
  Serial.begin(115200);
  pinMode(10,INPUT);
  pinMode(4,INPUT);
  pinMode(2,INPUT);
}


void loop() {
  Serial.print("LT_L: ");
  Serial.print(LT_L);
  Serial.print("  LT_M: ");
  Serial.print(LT_M);
  Serial.print("  LT_R: ");
  Serial.println(LT_R);
  delay(500);
}
