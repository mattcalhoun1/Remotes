#include <Arduino.h>
#include <stdint.h>
#include "Display.h"
//#include "Display_1306.h"
#include "Display_1331.h"
#include "Joystick.h"
#include "LoRaTrans.h"

Display* display;
Joystick* joystick;
LoRaTrans* lora;

void setup() {
  long start = millis();
  // if log enabled, wait up to 5 sec for serial to become available
  if (LOG_ENABLED) {
    while (!Serial) {
      if (start + 5000 < millis()) {
        break;
      }
      delay(10);
    } 
  }
  Serial.begin(115200);
  delay(100);

  lora = new LoRaTrans();
  display = new Display_1331();
  joystick = new Joystick(VRX_PIN, VRY_PIN, SW_PIN);
}

void loop() {
  if(joystick->refresh()) {
    JoystickDirection direction = joystick->getDirection();
    display->clear();
    display->showText("Ok", DISPLAY_STATUS_X, DISPLAY_STATUS_Y, TextSmall, Blue);
    display->showSymbol(getDirectionSymbol(direction), 60, 20);
    //display->showText("X: " + String(joystick->getX()), 10, 5, TextSmall, Green);
    //display->showText("Y: " + String(joystick->getY()), 10, 15, TextSmall, Yellow);

    if (joystick->isPressed()) {
      display->showText("*", 96, 10, TextLarge, Red);
      if (lora->send("this is mkrzero", LORA_ADDR_SPOTTER)) {
        logConsole("Message sent to spotter");
      }
    }

    display->repaint();
  }

  if (lora->hasMessage()) {
    display->clear();
    display->showText("Receiving...", DISPLAY_STATUS_X, DISPLAY_STATUS_Y, TextSmall, Blue);
    int messageLength = lora->retrieveMessage();
    logConsole("LORA message size: " + String(messageLength) + "!!");
    //display->showText("LORA (" + String(messageLength) + ")", 10, 25, TextSmall);
    
    if (messageLength > 0) {
      // if it's a therml image, render it
      if (lora->getChunkInBufferTime() > lora->getMessageBufferTime()) {
        display->clear();
        display->showText("Thermal", DISPLAY_STATUS_X, DISPLAY_STATUS_Y, TextSmall, Blue);
        display->showThermal(lora->getChunkInBuffer(), THERMAL_HEIGHT,THERMAL_WIDTH, 32, 0);
        display->repaint();
      }
      else { //  maybe it's just a string
        logConsole("LORA message: " + String((char*)lora->getMessageBuffer()));
      }
    }

  }
  /*else {
    logConsole("No Lora");
    if (lora->send("this is mkrzero", LORA_ADDR_SPOTTER)) {
      logConsole("Message sent to spotter");
    }
  }
  */


  delay(100);
}

int getDirectionSymbol (JoystickDirection direction) {
  if (direction == JoystickUp) {
    return 0x18;
  }
  else if (direction == JoystickDown) {
    return 0x19;
  }
  else if (direction == JoystickLeft) {
    return 0x1a;
  }
  else if (direction == JoystickRight) {
    return 0x1b;
  }
  else if (direction == JoystickNone) {
    return 0x00;
  }
  else {
    return 0x02;
  }
}

void logConsole (String msg) {
  Serial.println(msg);
}