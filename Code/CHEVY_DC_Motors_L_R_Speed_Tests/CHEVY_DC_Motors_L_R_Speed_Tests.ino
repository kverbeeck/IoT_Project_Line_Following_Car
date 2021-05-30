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
// int CAR_SPEED_F = 90; // Car Speed for Driving Forward 255 is Max. , Min. is 70     // 90 is good !!!!
// int CAR_SPEED_T = 120; // Car Speed for Turning 255 is Max. , Min. is 70            // 120 is good !!!!
int LEFT_SPEED = 120; // 70 is min. to start rotating on AC power
int RIGHT_SPEED = 90; // 60 is min. to start rotating on AC Power

void stop_car() {
  digitalWrite(IN1, LOW); // IN1 = 0
  digitalWrite(IN2, LOW); // IN2 = 0
  digitalWrite(IN3, LOW); // IN3 = 0
  digitalWrite(IN4, LOW); // IN4 = 0
}

void forward() {
  analogWrite(ENA, LEFT_SPEED);
  analogWrite(ENB, RIGHT_SPEED);
  digitalWrite(IN1, HIGH); // IN1 = 1
  digitalWrite(IN2, LOW); // IN2 = 0
  digitalWrite(IN3, LOW); // IN3 = 0
  digitalWrite(IN4, HIGH); // IN4 = 1
}


//----------------------------------------------------------------------------------------------------

void setup() {

  // Debug console Serial Monitor
  Serial.begin(115200);

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

//----------------------------------------------------------------------------------------------------

void loop() {
  
  forward();
}
