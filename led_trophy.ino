#include <Adafruit_NeoPixel.h>

#define LED_PIN 13
#define CYCLE_DELAY 50
#define LOOP_DELAY 0

#define ROWS 5
#define COLUMNS 8

#define OUTER_GAMMA_MIN 0
#define OUTER_GAMMA_MAX 65536
uint16_t outer_gamma = 0;

#define INNER_GAMMA_MIN 0
#define INNER_GAMMA_MAX 255
#define INNER_HUE 0
#define INNER_SATURATION 0
#define INNER_GAMMA 255
//int inner_gamma = 255;
int inner_active = 0;
int inner_rows[] = {1,2,3};

Adafruit_NeoPixel strip(ROWS * COLUMNS, LED_PIN, NEO_GRB+NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(10);
}

void loop() {
  strip.clear();
  strip.fill(strip.ColorHSV(outer_gamma),0,COLUMNS);
  strip.fill(strip.ColorHSV(outer_gamma),32,COLUMNS);
  strip.fill(strip.ColorHSV(INNER_HUE, INNER_SATURATION, INNER_GAMMA), inner_rows[inner_active]*COLUMNS, COLUMNS);
  strip.show();
  if (0 == outer_gamma%CYCLE_DELAY) {
    inner_active++;
  }
  if (inner_active >= (sizeof(inner_rows)/sizeof(inner_rows[0]))) {
    inner_active = 0;
  }
  outer_gamma++;
  if (outer_gamma > OUTER_GAMMA_MAX) {
    outer_gamma = OUTER_GAMMA_MIN;
  }
  delay(LOOP_DELAY);
}
