/**************************************************************
   Blynk is a platform with iOS and Android apps to control
   Arduino, Raspberry Pi and the likes over the Internet.
   Blynk library is licensed under MIT license
   This example runs directly on ESP8266 chip.
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Auth Token, WiFi credentials are defined here:
#include "Auth.h"

#include "BoatController.h"

Boat myBoat;

void setup()
{
  Serial.begin(115200);
  myBoat.motorLeft.setPinPlus  (  5 ); // when move forward PWM is here
  myBoat.motorLeft.setPinMinus (  0 ); // and zero here
  myBoat.motorRight.setPinPlus ( 16 ); // when move forward PWM is here
  myBoat.motorRight.setPinMinus( 14 ); // and zero here
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
  // read gyroscope
  myBoat.motorLeft.setSpeed(10);
  //

}

