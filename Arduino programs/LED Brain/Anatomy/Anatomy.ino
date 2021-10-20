#include <FastLED.h>

#define NUM_LEDS 100
#define toggle 4
int state = 0;
int track = 0;

#define DATA_PIN 6


// Define the array of leds
CRGB leds[NUM_LEDS];

//-----------------------------------------------------------------------------

void setup() {
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical

  Serial.begin(115200);

  
  
  black();
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(100,100,100);
    leds[i].fadeLightBy(225);
  }
    FastLED.show();
}

//-----------------------------------------------------------------------------


void loop() {
  stateRead();



  if ( state == 0 ) {
    cerrebellum();
    stem();
    occipital();
    parietal();
    prefrontal();
    temporal();
  }

  if (state == 1) {
      static uint8_t hue = 0;
        Serial.print("x");
        // First slide the led in one direction
        for(int i = 0; i < NUM_LEDS; i++) {
          // Set the i'th led to red 
          leds[i] = CHSV(hue++, 255, 255);
          // Show the leds
          FastLED.show(); 
          // now that we've shown the leds, reset the i'th led to black
          // leds[i] = CRGB::Black;
          fadeall();
          // Wait a little bit before we loop around and do it again
          delay(10);
        }
        Serial.print("x");
      
        // Now go in the other direction.  
        for(int i = (NUM_LEDS)-1; i >= 0; i--) {
          // Set the i'th led to red 
          leds[i] = CHSV(hue++, 255, 255);
          // Show the leds
          FastLED.show();
          // now that we've shown the leds, reset the i'th led to black
          // leds[i] = CRGB::Black;
          fadeall();
          // Wait a little bit before we loop around and do it again
          delay(10);
        }
        }


}

//-----------------------------------------------------------------------------

void stateRead() {
  state = digitalRead(toggle);
  Serial.print(state);
}

void black () {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
    }
    FastLED.show();
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }





void prefrontal(){    // 50-76
    for (int i = 50; i < 77; i++) {
      leds[i] = CRGB(255,0,0);
    }
  leds[74] = CRGB(0,0,255);
  leds[73] = CRGB(0,0,255);

      FastLED.show();
}

void parietal(){      //   37-49 +77 +78
      for (int i = 37; i < 50; i++) {
      leds[i] = CRGB(255,255,0);
    }
      leds[77] = CRGB(255,255,0);
      leds[78] = CRGB(255,255,0);
      FastLED.show();
  
}

void occipital(){     //25-36   -32
      for (int i = 25; i < 37; i++) {
      leds[i] = CRGB(51,255,255);
    }
  leds[32] = CRGB(0,0,255);
  leds[33] = CRGB(0,0,255);
      FastLED.show();
}


void cerrebellum(){   //9-24
    for (int i = 9; i < 25; i++) {
      leds[i] = CRGB(255,51,255);
    }
  leds[15] = CRGB(0,0,255);
      FastLED.show();
}

void temporal(){      // 79-100     +32
  
  
  for (int i = 79; i < 100; i++) {
      leds[i] = CRGB(0,0,255);
    }
  
  leds[32] = CRGB(0,0,255);
  leds[33] = CRGB(0,0,255);
  leds[15] = CRGB(0,0,255);
  leds[74] = CRGB(0,0,255);
  leds[73] = CRGB(0,0,255);
  FastLED.show();
}

void stem(){          //1-8
  for (int i = 0; i < 9; i++) {
      leds[i] = CRGB(10,200,10);
    }
      FastLED.show();
}
