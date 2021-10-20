#include <FastLED.h>

#define NUM_LEDS 100
#define toggle 4
int state = 0;
int track = 0;

#define DATA_PIN 6
#define FadeBrightness 175
int fadein = 10;
int light = 0;

int R = 255;
int G = 15;
int B = 15;

int fadeout = 10;
int dark = 240;
// Define the array of leds
CRGB leds[NUM_LEDS];

//-----------------------------------------------------------------------------

void setup() {
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical

  Serial.begin(115200);
  black();

  intro();

  black();

}

//-----------------------------------------------------------------------------


void loop() {
  stateRead();

  if ( state == 0 ) {
    intro();
    black();
  }

  if (state == 1) {
    jingle();
    black();
  }


}

//-----------------------------------------------------------------------------

void stateRead() {
  state = digitalRead(toggle);
  Serial.print(state);
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

void jingle() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i % 2 == 0) {
      leds[i] = CRGB(255, 0, 0);
      leds[i].fadeLightBy(FadeBrightness);
    } else {
      leds[i] = CRGB(0, 200, 0);
      leds[i].fadeLightBy(FadeBrightness);
    }
  }
    FastLED.show();
    delay(500);

    for (int i = 0; i < NUM_LEDS; i++) {
      if (i % 2 != 0) {
        leds[i] = CRGB(255, 0, 0);
        leds[i].fadeLightBy(FadeBrightness);
      } else {
        leds[i] = CRGB(0, 200, 0);
        leds[i].fadeLightBy(FadeBrightness);
      }
    }
    FastLED.show();
    delay(500);
  }

  //-----------------------------------------------------------------------------


  void intro () {
    for (int i = 0; i < NUM_LEDS; i++) {
      if (i % 2 == 0) {
        leds[i] = CRGB(255, 0, 0);
        delay(40);
        FastLED.show();
      } else {
        leds[i] = CRGB(0, 255, 0);
        delay(40);
        FastLED.show();
      }
    }
    black();
  }

  //-----------------------------------------------------------------------------

  void black () {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
    }
    FastLED.show();
  }

  //-----------------------------------------------------------------------------

  void assign(int r, int g, int b) {
    if (r > 255) {
      R = 255;
    } else {
      R = r;
    }
    G = g;
    B = b;
  }
  //-----------------------------------------------------------------------------
