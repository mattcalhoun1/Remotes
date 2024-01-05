#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "Globals.h"

#define OLED_ADDR   0x3C

// 128 x 32 pixel display
#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


#ifndef DISPLAY_H
#define DISPLAY_H
enum TextSize {
  TextSmall = 1,
  TextMedium = 2,
  TextLarge = 3
};

class Display {
  public:
    Display ();
    void showThermal (float* frame, int resHeight, int resWidth, int xOffset, int yOffset);
    void showText (String text, int x, int y, TextSize size);
    void showSymbol (int gfxChar, int x, int y);
    void clear ();
    void repaint ();

  private:
    void logConsole (String msg);
    Adafruit_SSD1306* display = new  Adafruit_SSD1306(-1);  // -1 = no reset pin, reset pin not used on 4-pin OLED module    
};
#endif