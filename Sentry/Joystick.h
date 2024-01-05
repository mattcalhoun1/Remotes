#include <ezButton.h>

enum JoystickDirection {
  JoystickUp = 0,
  JoystickUpRight = 1,
  JoystickRight = 2,
  JoystickDownRight = 3,
  JoystickDown = 4,
  JoystickDownLeft = 5,
  JoystickLeft = 6,
  JoystickUpLeft = 7,
  JoystickNone = 8
};

class Joystick {
  public:
    Joystick(int _vrx_pin, int _vry_pin, int _sw_pin);
    bool refresh ();
    int getX ();
    int getY ();
    bool isPressed ();
    JoystickDirection getDirection ();
  private:
    int vrx_pin;
    int vry_pin;
    int sw_pin;

    ezButton* button;
    int x = 0;
    int y = 0;
    bool pressed = false;

    const int axisMovementThreshold = 100;

};
