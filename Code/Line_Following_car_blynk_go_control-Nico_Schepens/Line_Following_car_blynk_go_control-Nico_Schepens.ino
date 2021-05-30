#include <analogWrite.h>

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "hFiGeSS2SYIYC9vdREbCGmg6zG-OInC3";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "telenet-32924";
char pass[] = "";


// IR SENSOREN

int IRSensor_Binnen_Links = 26;
int IRSensor_Binnen_Rechts = 25;

//MOTOR LINKS
int in1 = 27;
int in2 = 14;


//MOTOR RECHTS
int in3 = 12;
int in4 = 13;

//LEDS
int led_rood = 4;
int led_geel = 2;
int led_groen = 15;

//TIMER
int counter = 0;



void setup() {
  Serial.begin(115200);

  /*
   * Wi-Fi
   */
  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  
  /*
   * BLYNK
   */
  // Initialize the BLYNK Client
  Blynk.begin(auth, ssid, pass, "server.wyns.it", 8081);
  

  pinMode(IRSensor_Binnen_Links, INPUT);
  pinMode(IRSensor_Binnen_Rechts, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(led_rood, OUTPUT);
  pinMode(led_geel, OUTPUT);
  pinMode(led_groen, OUTPUT);
}

void loop() {

  Blynk.run();

  Serial.print("IRSensor Binnen Rechts status = " );
  Serial.println(digitalRead(IRSensor_Binnen_Rechts));
  Serial.print("IRSensor Binnen Links status = " );
  Serial.println(digitalRead(IRSensor_Binnen_Links));



  //VOORUIT
  if (digitalRead(IRSensor_Binnen_Rechts) == 1 && digitalRead(IRSensor_Binnen_Links) == 1) {
    digitalWrite(in1, 200);
    digitalWrite(in2, 0);
    digitalWrite(in3, 0);
    digitalWrite(in4, 200);
    digitalWrite(led_groen, HIGH);
    digitalWrite(led_geel, LOW);
    counter = counter + 1;
    Serial.print(counter);

    if (counter >= 200) {
      digitalWrite(in1, 0);
      digitalWrite(in2, 0);
      digitalWrite(in3, 0);
      digitalWrite(in4, 0);
      digitalWrite(led_groen, LOW);
      digitalWrite(led_geel, LOW);
      digitalWrite(led_rood, HIGH);
    }

  }

  //STOP
  if (digitalRead(IRSensor_Binnen_Rechts) == 0 && digitalRead(IRSensor_Binnen_Links) == 0) {
    digitalWrite(in1, 0);
    digitalWrite(in2, 0);
    digitalWrite(in3, 0);
    digitalWrite(in4, 0);
    digitalWrite(led_groen, LOW);
    digitalWrite(led_geel, HIGH);
    digitalWrite(led_rood, LOW);
    counter = 0;



  }

  //DRAAIEN
  if (digitalRead(IRSensor_Binnen_Links) == 0 && digitalRead(IRSensor_Binnen_Rechts) == 1) {
    digitalWrite(in1, 0);
    digitalWrite(in2, 200);
    digitalWrite(in3, 0);
    digitalWrite(in4, 200);
    digitalWrite(led_groen, HIGH);
    digitalWrite(led_geel, LOW);
    digitalWrite(led_rood, LOW);
    counter = 0;

  }

  if (digitalRead(IRSensor_Binnen_Links) == 1 && digitalRead(IRSensor_Binnen_Rechts) == 0) {
    digitalWrite(in1, 200);
    digitalWrite(in2, 0);
    digitalWrite(in3, 200);
    digitalWrite(in4, 0);
    digitalWrite(led_groen, HIGH);
    digitalWrite(led_geel, LOW);
    digitalWrite(led_rood, LOW);
    counter = 0;

  }
}
