#include <Servo.h> // Command to insert the Servo library into your program.

int servoPin = 3; // Port to control the servo Motor
int servoPos; 
// Start position of the Servo, stright wheels (only executed at begining)
// Max. range right is 40° and max. range left is 130°
int servoStartPos = 80;
String msg = "What angle for the Servo?";
String msg2 = "The chosen angle is: ";
String msg3 = "°";

Servo myServo; // Create a virtual object into your Arduino so you can interact with it. 
               // Also give it a name (myServo).

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // Attach the virtual Servo (object) to your Arduino using the control pin to interact with it.
  myServo.attach(servoPin);  
  // The Servo will start at the configured Start position of the Servo.              
  myServo.write(servoStartPos); 
}

void loop() {
  // put your main code here, to run repeatedly:
  
  Serial.println(msg);

  while (Serial.available() == 0) {
  }
  
  servoPos = Serial.parseInt();
  
  if (servoPos < 40 || servoPos > 130){
    Serial.println("Angle should be a value in between 40° and 130°");
  }
  else{
    myServo.write(servoPos); // Tell the Servo to go to a certain position.
  // 0 degrees till 180 degrees
  }

  Serial.println(msg2 + servoPos + msg3);
}
