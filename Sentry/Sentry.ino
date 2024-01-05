#include "Display.h"
#include "Joystick.h"

Display* display;
Joystick* joystick;

void setup() {
  while (!Serial) delay(10);
  Serial.begin(115200);
  delay(100);

  display = new Display();
  joystick = new Joystick(VRX_PIN, VRY_PIN, SW_PIN);
}

void loop() {
  if(joystick->refresh()) {
    JoystickDirection direction = joystick->getDirection();
    display->clear();
    display->showSymbol(getDirectionSymbol(direction), 60, 20);
    display->showText("X: " + String(joystick->getX()), 10, 5, TextSmall);
    display->showText("Y: " + String(joystick->getY()), 10, 15, TextSmall);

    if (joystick->isPressed()) {
      display->showText("*", 96, 10, TextLarge);
    }

    display->repaint();
  }

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