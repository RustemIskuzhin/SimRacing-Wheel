/*
  Copyright (c) 2014-2015 NicoHood
  See the readme for credit to other people.

  Gamepad example
  Press a button and demonstrate Gamepad actions

  You can also use Gamepad1,2,3 and 4 as single report.
  This will use 1 endpoint for each gamepad.

  See HID Project documentation for more infos
  https://github.com/NicoHood/HID/wiki/Gamepad-API
*/

#include "HID-Project.h"

//#define DEBUG

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  #ifndef DEBUG 
     Gamepad.begin();
  #else
     Serial.begin(115200);
  #endif 
  delay(100);
  
}

void loop() {
  if (!digitalRead(pinButton)) {
    digitalWrite(pinLed, HIGH);
  };

    int inputPot0 = analogRead(0);  
    int inputPot1 = analogRead(1);
    int inputPot2 = analogRead(2);
    
  #ifndef DEBUG
    if ((inputPot0 > 300) and (inputPot0 < 561))
      Gamepad.xAxis(map(inputPot0, 300, 561, -32767, 32767 ));
    else if (inputPot0 < 300) 
      Gamepad.yAxis(-32767);
    else 
      Gamepad.yAxis(32767);
    if (inputPot1 > 350)
      Gamepad.yAxis(map(inputPot1, 200, 1024, -32767, 32767 ));
    else
      Gamepad.yAxis(-32767);

    if (inputPot2 > 350)   
      Gamepad.ryAxis((inputPot2, 300, 1024, -32767, 32767 ));
    else
      Gamepad.ryAxis(-32767);   
    // Functions above only set the values.
    // This writes the report to the host.
    Gamepad.write();  
   #else    
       Serial.print("axis[0]= ");
       Serial.print(inputPot0);
       Serial.print(" axis[1]= ");
       Serial.print(inputPot1);
       Serial.print(" axis[2]= ");
       Serial.print(inputPot2);
       Serial.println();
   #endif 

  // Simple debounce
  delay(1);
  digitalWrite(pinLed, LOW);

}
