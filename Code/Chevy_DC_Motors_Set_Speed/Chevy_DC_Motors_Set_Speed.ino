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

void stop_car(){
  digitalWrite(IN1, LOW); // IN1 = 0
  digitalWrite(IN2, LOW);  // IN2 = 0
  digitalWrite(IN3, LOW);  // IN3 = 0
  digitalWrite(IN4, LOW); // IN4 = 0
  delay(1000);
}

void forward(int car_speed){
  analogWrite(ENA, car_speed);
  analogWrite(ENB, car_speed);
  digitalWrite(IN1, HIGH); // IN1 = 1
  digitalWrite(IN2, LOW); // IN2 = 0
  digitalWrite(IN3, LOW); // IN3 = 0
  digitalWrite(IN4, HIGH); // IN4 = 1
  // Keep driving forward untill "stop_car()" Function !!!!
}

void backward(int car_speed)
{
  analogWrite(ENA, car_speed);
  analogWrite(ENB, car_speed);
  digitalWrite(IN1, LOW); // IN1 = 0
  digitalWrite(IN2, HIGH); // IN2 = 1
  digitalWrite(IN3, HIGH); // IN3 = 1
  digitalWrite(IN4, LOW); // IN4 = 0
  // Keep driving forward untill "stop_car()" Function !!!!
}


void setup() {
  // put your setup code here, to run once:
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


  start_car();
  // digitalWrite(ENA, HIGH); // We can leave these Control channels enabled (Left Wheels)
  // digitalWrite(ENB, HIGH); // We can leave these Control channels enabled (Right Wheels)
}


void loop() {
  // put your main code here, to run repeatedly:

  forward(CAR_SPEED); //go forward for 3 seconds
  delay(2000);

  stop_car();
  
  backward(CAR_SPEED); //go backward for 3 seconds
  delay(2000);

  stop_car();

  while(1){
    // halts the "void loop()", code only runs once.
  }
}
