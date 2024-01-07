#include "Display_1331.h"

Display_1331::Display_1331() {
  // initialize and clear display
  display->begin();
  clear();
 // display->display();
}

void Display_1331::clear () {
  display->fillScreen(BLACK);
 // display->display();
}

void Display_1331::repaint () {
  //display->display();
}

void Display_1331::showText (String text, int x, int y, TextSize size) {
  showText(text, x, y, size, White);
}
void Display_1331::showSymbol (int gfxChar, int x, int y) {
  showSymbol (gfxChar, x, y, White);
}


void Display_1331::showSymbol (int gfxChar, int x, int y, DisplayColor color) {
  display->setTextColor(get1331Color(color));   // Draw white text
  display->setCursor(x,y);
  display->write(gfxChar);
}


void Display_1331::showText (String text, int x, int y, TextSize size, DisplayColor color) {
  logConsole("Showing text: " + text);
  display->setTextSize(size);                
  display->setTextColor(get1331Color(color));
  display->setCursor(x,y);
  display->println(text);
}

void Display_1331::showThermal (float* frame, int resHeight, int resWidth, int xOffset, int yOffset) {
  int hotThreshold = 27;

  for (uint8_t h=0; h<resHeight; h++) {
    for (uint8_t w=0; w<resWidth; w++) {
      float t = frame[h*resWidth + w];
      if (t >= hotThreshold) {
        display->drawPixel(xOffset + w, yOffset + h, WHITE);
      }
    }
  }
}

uint16_t Display_1331::get1331Color(DisplayColor color) {
  switch (color) {
    case Black:
      return BLACK;
    case Blue:
      return BLUE;
    case Red:
      return RED;
    case Green:
      return GREEN;
    case Cyan:
      return CYAN;
    case Magenta:
      return MAGENTA;
    case Yellow:
      return YELLOW;
    default:
      return WHITE;
  }
}