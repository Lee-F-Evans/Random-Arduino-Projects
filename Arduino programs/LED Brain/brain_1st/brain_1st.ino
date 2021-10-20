#include <FastLED.h>

#define NUM_LEDS 100
#define toggle 4
int state = 0;
int track = 0;

#define DATA_PIN 6
int brightness = 250;
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
    NheartBeat();
  }

  if (state == 1) {
    FheartBeat();
  }


}

//-----------------------------------------------------------------------------

void FheartBeat() {
  assign(70, 0, 0); // panik red

  while (brightness > 90) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(R, G, B);
      leds[i].fadeLightBy(brightness);
    }
    brightness -= fadein;
    FastLED.show();
    delay(10);
  }

  stateRead();
  if (state == 0) {
    Fade();
    return;
  }

  while (brightness < 150) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(R, G, B);
      leds[i].fadeLightBy(brightness);
    }
    brightness += fadeout;
    FastLED.show();
    delay(6);
  }

  stateRead();
  if (state == 0) {
    Fade();
    return;
  }


  while (brightness > light) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(R, G, B);
      leds[i].fadeLightBy(brightness);
    }
    brightness -= fadein;
    FastLED.show();
    delay(10);
  }

  stateRead();
  if (state == 0) {
    Fade();
    return;
  }

  while (brightness < dark) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(R, G, B);
      leds[i].fadeLightBy(brightness);
    }
    brightness += fadeout;
    FastLED.show();

    delay(8);
  }

  stateRead();
  if (state == 0) {
    Fade();
    return;
  }


}

//-----------------------------------------------------------------------------

void Fade() {
  assign(70, 0, 0);
  for(int j = 0; j<15;j++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(R, G, B);
      leds[i].fadeLightBy(brightness);
    }
    R+=3;
    G+=1;
    B+=1;
    FastLED.show();
    delay(200);
  }
  assign(255, 15, 15); // pink
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(R + 3, G + 1, B + 1);
    leds[i].fadeLightBy(brightness);

  }
}

  //-----------------------------------------------------------------------------

  void NheartBeat() {
    assign(255, 15, 15); // pink

    while (brightness > 90) {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB(R, G, B);
        leds[i].fadeLightBy(brightness);
      }
      brightness -= fadein;
      FastLED.show();
      delay(15);
    }

    stateRead();
    if (state == 1) {
      Stress();
      return;
    }

    while (brightness < 150) {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB(R, G, B);
        leds[i].fadeLightBy(brightness);
      }
      brightness += fadeout;
      FastLED.show();
      delay(8);
    }

    stateRead();
    if (state == 1) {
      Stress();
      return;
    }


    while (brightness > light) {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB(R, G, B);
        leds[i].fadeLightBy(brightness);
      }
      brightness -= fadein;
      FastLED.show();
      delay(20);
    }

    stateRead();
    if (state == 1) {
      Stress();
      return;
    }

    while (brightness < dark) {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB(R, G, B);
        leds[i].fadeLightBy(brightness);
      }
      brightness += fadeout;
      FastLED.show();

      delay(40);
    }

    stateRead();
    if (state == 1) {
      Stress();
      return;
    }
  }



  //-----------------------------------------------------------------------------


  void intro () {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(R, G, B);
      delay(20);
      FastLED.show();
    }
  }

  //-----------------------------------------------------------------------------

  void black () {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
      leds[i].fadeLightBy(brightness);
    }
    FastLED.show();
  }

  //-----------------------------------------------------------------------------

  void Stress () {

    black();
    assign(255, 0, 0); // panik red

    // frontal lobe
    for (int i = 0; i < 7; i++) {
      while (brightness > light) {
        for (int i = 61; i < 75; i++) {
          leds[i] = CRGB(200, 0, 0);
          leds[i].fadeLightBy(brightness);
        }
        brightness -= fadein;
        FastLED.show();

        stateRead();
        if (state == 0) {
          Fade();
          return;
        }
        delay(3);
      }

      while (brightness < dark) {
        for (int i = 61; i < 75; i++) {
          leds[i] = CRGB(200, 0, 0);
          leds[i].fadeLightBy(brightness);
        }
        brightness += fadeout;
        FastLED.show();

        stateRead();
        if (state == 0) {
          Fade();
          return;
        }
        delay(3);
      }
    }

    //transition to mid brain
    assign(70, 0, 0); // less panik red
    for (int i = 0; i < 3; i++) {
      for (int i = 61; i < 92; i++) {
        leds[i] = CRGB(R, G, B);
        FastLED.show();

        stateRead();
        if (state == 0) {
          Fade();
          return;
        }
        
        delay(20);
      }
      black();
    }

    // mid brain active

    assign(0, 0, 0);
    for (int j = 0; j < 50; j++) {
      assign(R + 1, 0, 0);
      for (int i = 74; i < 92; i++) {
        leds[i] = CRGB(R, G, B);
      }
      FastLED.show();

      stateRead();
      if (state == 0) {
        Fade();
        return;
      }
      delay(40);
    }
    //spread
    assign(70, 0, 0);
    for (int i = 74; i < 92; i++) {
      leds[i] = CRGB(R, G, B);
    }

    leds[7] = CRGB(R, G, B);
    leds[15] = CRGB(R, G, B);
    leds[32] = CRGB(R, G, B);
    leds[41] = CRGB(R, G, B);
    leds[49] = CRGB(R, G, B);
    leds[55] = CRGB(R, G, B);
    leds[61] = CRGB(R, G, B);
    leds[66] = CRGB(R, G, B);
    leds[73] = CRGB(R, G, B);
    FastLED.show();
    
    stateRead();
    if (state == 0) {
      Fade();
      return;
    }
    delay(1000);

    leds[6] = CRGB(R, G, B);
    leds[8] = CRGB(R, G, B);
    leds[14] = CRGB(R, G, B);
    leds[33] = CRGB(R, G, B);
    leds[40] = CRGB(R, G, B);
    leds[42] = CRGB(R, G, B);
    leds[48] = CRGB(R, G, B);
    leds[56] = CRGB(R, G, B);
    leds[54] = CRGB(R, G, B);
    leds[62] = CRGB(R, G, B);
    leds[60] = CRGB(R, G, B);
    leds[67] = CRGB(R, G, B);
    leds[65] = CRGB(R, G, B);
    leds[72] = CRGB(R, G, B);
    FastLED.show();

    stateRead();
    if (state == 0) {
      Fade();
      return;
    }

    delay(1000);

    leds[5] = CRGB(R, G, B);
    leds[9] = CRGB(R, G, B);
    leds[16] = CRGB(R, G, B);
    leds[31] = CRGB(R, G, B);
    leds[34] = CRGB(R, G, B);
    leds[39] = CRGB(R, G, B);
    leds[50] = CRGB(R, G, B);
    leds[53] = CRGB(R, G, B);
    leds[57] = CRGB(R, G, B);
    leds[59] = CRGB(R, G, B);
    leds[64] = CRGB(R, G, B);
    leds[68] = CRGB(R, G, B);
    leds[71] = CRGB(R, G, B);
    leds[43] = CRGB(R, G, B);
    leds[47] = CRGB(R, G, B);

    leds[4] = CRGB(R, G, B);
    leds[3] = CRGB(R, G, B);
    leds[13] = CRGB(R, G, B);
    leds[17] = CRGB(R, G, B);
    leds[23] = CRGB(R, G, B);
    leds[24] = CRGB(R, G, B);
    leds[30] = CRGB(R, G, B);
    leds[35] = CRGB(R, G, B);
    leds[10] = CRGB(R, G, B);
    leds[11] = CRGB(R, G, B);
    leds[12] = CRGB(R, G, B);
    leds[18] = CRGB(R, G, B);
    leds[22] = CRGB(R, G, B);
    leds[25] = CRGB(R, G, B);
    leds[29] = CRGB(R, G, B);
    leds[36] = CRGB(R, G, B);
    leds[38] = CRGB(R, G, B);
    leds[44] = CRGB(R, G, B);
    leds[46] = CRGB(R, G, B);
    leds[51] = CRGB(R, G, B);
    FastLED.show();
    delay(1000);

    for (int i = 0; i < 92; i++) {
      leds[i] = CRGB(R, G, B);
    }
    FastLED.show();
    stateRead();
    if (state == 0) {
      Fade(); 
      return;
    }
    delay(1500);
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
  void stateRead() {
    state = digitalRead(toggle);
    Serial.print(state);
  }
