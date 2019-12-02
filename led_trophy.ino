#include <Adafruit_NeoPixel.h>

#define LED_PIN 13
#define CYCLE_DELAY 50
#define LOOP_DELAY 0

int rows = 5;
int columns = 8;

#define OUTER_GAMMA_MIN 0
#define OUTER_GAMMA_MAX 65536
uint16_t outer_gamma = 0;

#define INNER_GAMMA_MIN 0
#define INNER_GAMMA_MAX 255
int inner_gamma = 255;
int inner_active = 0;
int inner_rows[] = {1,2,3};

Adafruit_NeoPixel strip(rows * columns, LED_PIN, NEO_GRB+NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  strip.begin();
  strip.show();
  strip.setBrightness(25);
}

void loop() {
  strip.clear();
  strip.fill(strip.ColorHSV(outer_gamma),0,8);
  strip.fill(strip.ColorHSV(outer_gamma),32,8);
  strip.fill(strip.Color(inner_gamma, inner_gamma, inner_gamma), inner_rows[inner_active]*columns, columns);
  strip.show();
  if (0 == outer_gamma%CYCLE_DELAY) {
    Serial.print("Cycling row ");
    Serial.println(outer_gamma);
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
