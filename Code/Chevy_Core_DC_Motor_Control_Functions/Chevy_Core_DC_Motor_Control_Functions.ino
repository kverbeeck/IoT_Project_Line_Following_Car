
// Remove the Bluetooth Module before connecting the Arduino to the Arduino IDE !!!
// You will need all 4 control signals, even if you have only 1 DC motor right and 1 DC motor left !!!!

int ENA = 5;  // Control Channel A for left wheels
int ENB = 6;  // Control Channel B for right wheels
int IN1 = 7;  // Control Signal 1 for left wheels
int IN2 = 8;  // Control Signal 2 for left wheels
int IN3 = 9;  // Control Signal 3 for right wheels
int IN4 = 11; // Control Signal 4 for right wheels


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN4, OUTPUT);
  digitalWrite(ENA, HIGH); // We can leave these Control channels enabled (Left Wheels)
  digitalWrite(ENB, HIGH); // We can leave these Control channels enabled (Right Wheels)
}


void loop() {
  // put your main code here, to run repeatedly:

  // Go forward
  digitalWrite(IN1, HIGH); // IN1 = 1
  digitalWrite(IN2, LOW);  // IN2 = 0
  digitalWrite(IN3, LOW);  // IN3 = 0
  digitalWrite(IN4, HIGH); // IN4 = 1
  delay(5000); // Go forward for 5 seconds

  digitalWrite(ENA, LOW); // Stop the car
  digitalWrite(ENB, LOW); // Stop the car
  delay(1000);
  digitalWrite(ENA, HIGH); // Start the car
  digitalWrite(ENB, HIGH); // Start the car
 
  // Go backward
  digitalWrite(IN1, LOW);  // IN1 = 0
  digitalWrite(IN2, HIGH); // IN2 = 1
  digitalWrite(IN3, HIGH); // IN3 = 1
  digitalWrite(IN4, LOW);  // IN4 = 0
  delay(5000); // Go backward for 5 seconds

  digitalWrite(ENA, LOW); // Stop the car
  digitalWrite(ENB, LOW); // Stop the car

  while (true){
    // Infinite loop doing nothing
    // RESET button on Arduino will reset the program
  }
}
