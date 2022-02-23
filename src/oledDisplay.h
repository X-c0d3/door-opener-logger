#ifndef UELD_DISPLAY_H
#define ULED_DISPLAY_H

#include <ACROBOTIC_SSD1306.h>

void InitialOLED() {
    Wire.begin();
    oled.init();  // Initialze SSD1306 OLED display
    // oled.setInverseDisplay();
    oled.deactivateScroll();
    oled.clearDisplay();  // Clear screen
    oled.setFont(font5x7);
    // oled.setFont(font8x8);

    for (int i = 0; i < 8; i++) {
        oled.setTextXY(i, 1);
        oled.putString("                              ");
    }
}

void resetDisplay() {
    oled.clearDisplay();  // Clear screen
    oled.setFont(font5x7);
    for (int i = 0; i < 8; i++) {
        oled.setTextXY(i, 1);
        oled.putString(" ");
        // oled.putString("                                        ");
    }
}

bool clearDisplay(void *) {
    resetDisplay();
    return true;
}

#endif
