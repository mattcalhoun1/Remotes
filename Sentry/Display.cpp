#include "Display.h"

Display::Display() {
  // initialize and clear display
  display->begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display->clearDisplay();
  display->display();
}

void Display::clear () {
  display->clearDisplay();
  display->display();
}

void Display::repaint () {
  display->display();
}

void Display::showSymbol (int gfxChar, int x, int y) {
  display->setTextColor(SSD1306_WHITE);   // Draw white text
  display->setCursor(x,y);
  display->write(gfxChar);
}


void Display::showText (String text, int x, int y, TextSize size) {
  logConsole("Showing text: " + text);
  display->setTextSize(size);                
  display->setTextColor(SSD1306_WHITE);   // Draw white text
  display->setCursor(x,y);
  display->println(text);
}

void Display::showThermal (float* frame, int resHeight, int resWidth, int xOffset, int yOffset) {
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


void Display::logConsole (String msg) {
  if (LOG_ENABLED) {
    Serial.println(msg);
  }
}