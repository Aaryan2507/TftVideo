//Necessary libraries and a frames.h file(that is in the same folder as the sketch)
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include "frames.h"

//Make the connections as follows:
#define TFT_CS   5
#define TFT_DC   2 //Sometimes also labelled A0
#define TFT_RST  4
// VCC -> 3V3
// GND -> GND
// LED/BL -> 3V3

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  tft.initR(INITR_BLACKTAB);   // Can also be INITR_144GREENTAB if colors don't match your og video
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
}

void loop() {
  for (int i = 0; i < FRAME_COUNT; i++) {
    uint32_t t0 = millis();
    tft.drawRGBBitmap(0, 0, frames[i], FRAME_W, FRAME_H);
    int32_t wait = 1000 / FRAME_FPS - (millis() - t0);
    if (wait > 0) delay(wait);
  }
}
