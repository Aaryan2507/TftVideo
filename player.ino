// ESP32 + 1.44" ST7735 (128x128) frame player
// Library: "Adafruit ST7735 and ST7789 Library" (also installs Adafruit GFX)
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include "frames.h"

// Wiring (ESP32 default VSPI): SCK=18, MOSI(SDA)=23, plus these three
#define TFT_CS   5
#define TFT_DC   2
#define TFT_RST  4
// VCC -> 3V3, GND -> GND, LED/BL -> 3V3

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  tft.initR(INITR_144GREENTAB);   // 128x128. If colours look wrong try INITR_BLACKTAB
  tft.setRotation(0);
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
