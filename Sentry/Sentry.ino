#include <Arduino.h>
#include <stdint.h>
#include "Display.h"
//#include "Display_1306.h"
#include "Display_1331.h"
#include "Joystick.h"
#include "LoRaTrans.h"
#include "LoRaCommander.h"
#include "ThermalEncoder.h"

Display* display;
Joystick* joystick;
LoRaTrans* lora;
LoRaCommander* commander;
ThermalEncoder encoder = ThermalEncoder(THERMAL_HEIGHT, THERMAL_WIDTH, false);
//long nextCommandId = 0;
long currCommandId = 0;

bool awaitingResponse = false;
long maxCommandWaitTime = 10000;// max millis to wait for a response to a command
unsigned long currCommandStartTime = 0;

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
  commander = new LoRaCommander(lora, LORA_ADDR_SPOTTER);
  display = new Display_1331();
  joystick = new Joystick(VRX_PIN, VRY_PIN, SW_PIN);

  showDisplayMessage("Ready");
}

void loop() {
  if(joystick->refresh()) {
    JoystickDirection direction = joystick->getDirection();
    /*display->clear();
    display->showText("Ok", DISPLAY_STATUS_X, DISPLAY_STATUS_Y, TextSmall, Blue);
    display->showSymbol(getDirectionSymbol(direction), 60, 20);
    //display->showText("X: " + String(joystick->getX()), 10, 5, TextSmall, Green);
    //display->showText("Y: " + String(joystick->getY()), 10, 15, TextSmall, Yellow);
    */

    if (joystick->isPressed()) {
      requestThermal();
    }

    display->repaint();
  }

  if (lora->hasMessage()) {
    showDisplayMessage("Receiving");
    int messageLength = lora->retrieveMessage();
    logConsole("LORA message size: " + String(messageLength) + "!!");
    //display->showText("LORA (" + String(messageLength) + ")", 10, 25, TextSmall);
    if (messageLength > 0) {
      // if it's a therml image, render it
      if (lora->getChunkInBufferTime() > lora->getMessageBufferTime()) {
        display->clear();
        showDisplayMessage("Thermal");
        display->showThermal(lora->getChunkInBuffer(), THERMAL_HEIGHT,THERMAL_WIDTH, 32, 0);

        int xOffset = 18;
        int yOffset = 0;
        for (int r = 0; r < THERMAL_INTERPOLATED_HEIGHT; r++) {
          float* interpolatedRow = encoder.getInterpolatedRow(lora->getChunkInBuffer(), r);
          display->showInterpolatedThermalRow(interpolatedRow, xOffset, r + yOffset);
        }

        display->repaint();
      }
      else { //  maybe it's just a string
        String rawMessage = String((char*)lora->getMessageBuffer());
        Command command = commander->extractCommand(rawMessage, lora->getLastSender());

        if (command.getCommandType() == Receipt) {
          logConsole("Got Receipt for: " + String(command.getId()));
        }
        else if (command.getCommandType() == Result) {
          logConsole("Got result of: " + String(command.getId()) + " = " + String(command.getParams()));
          awaitingResponse = false;
        }
        else {
          logConsole("LORA message: " + String((char*)lora->getMessageBuffer()));
        }
        showDisplayMessage("Ready");
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

  // Check if we should stop waiting for a response
  if (awaitingResponse) {
    if (millis() - maxCommandWaitTime > currCommandStartTime) {
      awaitingResponse = false;
    }
  }

  /*if (!awaitingResponse) {
    // send a command
  }*/
}

void clearDisplayMessage () {
  display->clearArea(DISPLAY_STATUS_X, DISPLAY_STATUS_Y, 64, 8);
}

void showDisplayMessage (String msg) {
  clearDisplayMessage();
  display->showText(msg, DISPLAY_STATUS_X, DISPLAY_STATUS_Y, TextSmall, Blue);
}

void requestThermal() {
    currCommandId++;
    Command command;
    command.setCommandType(GetThermal);
    command.setParams("0");
    command.setId(currCommandId);
    command.setRecipient(LORA_ADDR_SPOTTER);
    commander->sendCommand(command);
    awaitingResponse = true;
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