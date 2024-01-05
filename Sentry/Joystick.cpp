#include "Joystick.h"

Joystick::Joystick(int _vrx_pin, int _vry_pin, int _sw_pin) {
  vrx_pin = _vrx_pin;
  vry_pin = _vry_pin;
  sw_pin = _sw_pin;

  button = new ezButton (sw_pin);
  button->setDebounceTime(50); // set debounce time to 50 milliseconds
}

bool Joystick::refresh () {
  button->loop(); // MUST call the loop() function first

  bool stateChanged = false;

  bool new_pressed = button->isPressed();
  if (new_pressed != pressed) {
    stateChanged = true;
  }
  pressed = new_pressed;

  // read analog X and Y analog values
  int new_x = analogRead(vrx_pin);
  if (abs(new_x - x) > axisMovementThreshold) {
    stateChanged = true;
  }
  x = new_x;

  int new_y = analogRead(vry_pin);
  if (abs(new_y - y) > axisMovementThreshold) {
    stateChanged = true;
  }
  y = new_y;

  return stateChanged;
}

JoystickDirection Joystick::getDirection () {
  int xMidpoint = 768;
  int yMidpoint = 787;

  bool isLeft = x < (xMidpoint - axisMovementThreshold);
  bool isRight = x > (xMidpoint + axisMovementThreshold);
  bool isDown = y < (yMidpoint - axisMovementThreshold);
  bool isUp = y > (yMidpoint + axisMovementThreshold);

  if (isUp) {
    if (isLeft) {
      return JoystickUpLeft;
    }
    else if (isRight) {
      return JoystickUpRight;
    }
    return JoystickUp;
  }
  else if (isDown) {
    if (isLeft) {
      return JoystickDownLeft;
    }
    else if (isRight) {
      return JoystickDownRight;
    }
    return JoystickDown;
  }
  else if (isLeft) {
    return JoystickLeft;
  }
  else if (isRight) {
    return JoystickRight;
  }
  return JoystickNone;
}

int Joystick::getX () {
  return x;
}

int Joystick::getY () {
  return y;
}

bool Joystick::isPressed () {
  return pressed;
}
