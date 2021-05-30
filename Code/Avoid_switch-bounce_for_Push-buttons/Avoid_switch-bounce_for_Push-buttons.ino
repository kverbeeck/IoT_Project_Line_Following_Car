/*
   This code demonstrates the use of a capacitor (100nF) to avoid switch-bounce.
   The capacitor is placed in parallel over the pull-down resistor used for the push-button.
   Button pressed in this case is "1" and button released in this case is "0".
   When the button is pressed, the capacitor will quickly charge.
   When the button is released, the capacitor will discharge slower via the pull-down resistor.
*/

// #define: When the sketch is compiled, the IDE replaces any instance of the defined word with the 
//          number that follows it (labeling). 

#define internalLED 13
#define pushButton 45
int buttonVal;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(internalLED, OUTPUT);
  pinMode(pushButton, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  buttonVal = digitalRead(pushButton);
  Serial.print("ButtonVal = ");
  Serial.println(buttonVal);

  if (buttonVal) { // Does exactly the same as: if (buttonVal == HIGH)
    digitalWrite(internalLED, HIGH);
    delay(2000); // Stay high for 500ms
    digitalWrite(internalLED, LOW);
  }
}
