/*************************************************************
  LED is connected to digital port 40 of ARDUINO MEGA
  Use the BLYNK example code at 
  https://examples.blynk.cc/?board=Arduino%20Mega%202560&shield=ESP8266%20WiFi%20Shield&example=GettingStarted%2FPushData&auth=SYbg29M3AiMlp83wB2HOlAhRHZ6wc1w_
  Board: Arduino Mega 2560 (This board is talking to the BLYNK Server, not the ESP-01)
  Connection: ESP8266 WiFi Shield
  Example: Push Data
  No need to configure the LED in this C++ code, the LED is configured in the BLYNK app (physical digital port 40).
  Button pushes in BLYNK app will be pushed to MEGA 2560.
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

char server[] = "192.168.10.122";
#define port 8080

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "SYbg29M3AiMlp83wB2HOlAhRHZ6wc1w_";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "BLYNK"; // Use the Orange modem Wi-Fi
char pass[] = "Bucky196";


// Hardware Serial on Mega, Leonardo, Micro...
#define EspSerial Serial1

// or Software Serial on Uno, Nano...
//#include <SoftwareSerial.h>
//SoftwareSerial EspSerial(2, 3); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);

BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, millis() / 1000);
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  // You can also specify server:
  // Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 80);
  // Own Server and port
  Blynk.begin(auth, wifi, ssid, pass, server, port);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
