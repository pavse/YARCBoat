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

BLYNK_WRITE(V0) { // Speed slider
  myBoat.setSpeed(param.asInt());
};

BLYNK_WRITE(V1) { // Wheel slider
  myBoat.setRotation(param.asInt());
};

BLYNK_WRITE(V2) { // Reverce button
  myBoat.Reverse = param.asInt() == 1;
};

BLYNK_WRITE(V3) { // Go straight button
  Blynk.virtualWrite(V1, 0);
};

void loop()
{
  Blynk.run();
  // read gyroscope
  myBoat.updateMotors();
  //

}

