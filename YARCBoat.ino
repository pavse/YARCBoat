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
WidgetTerminal terminal(V4);

void setup()
{
  Serial.begin(115200);
  myBoat.motorLeft.setPinPlus  (  5 ); // when move forward 1 is here
  myBoat.motorLeft.setPinMinus (  0 ); // and 0 here
  myBoat.motorLeft.setPinPWM   (  3 ); // and PWM here
  myBoat.motorRight.setPinPlus ( 16 ); // when move forward 1 is here
  myBoat.motorRight.setPinMinus( 14 ); // and 0 here
  myBoat.motorRight.setPinPWM  (  1 ); // and PWM here
  Blynk.begin(auth, ssid, pass);
  terminal.println("\nYARCBoat has started");
  terminal.flush();
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

BLYNK_WRITE(V4)
{
 if (String("d") == param.asStr() || String("dump") == param.asStr()) {
    terminal.print("Speed Left: ") ;
    terminal.print(myBoat.motorLeft.getSpeed()) ;
    terminal.print(", Speed Right: ") ;
    terminal.print(myBoat.motorRight.getSpeed()) ;
    terminal.println() ;
  } else {
    terminal.print("Unknown command:");
    terminal.write(param.getBuffer(), param.getLength());
    terminal.println();
  };
  terminal.flush();
}

void loop()
{
  Blynk.run();
  // read gyroscope
  myBoat.updateMotors();
  //

}

