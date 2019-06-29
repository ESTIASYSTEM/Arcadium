//
// marquee_light
//

#include "FastLED.h"

#define DATA_PIN 3
#define COLUMNS 30
#define ROWS 4
#define NUM_LEDS (COLUMNS * ROWS)

CRGB leds[NUM_LEDS];

void setup()
{
   FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}


void loop()
{ 
  // Turn the LED on, then pause
  for(size_t i(0) ; i < NUM_LEDS ; ++i)
  {
    leds[i] = CRGB::Red;
  }
  
  FastLED.show();
  
  delay(500);
  // Now turn the LED off, then pause
  for(size_t i(0) ; i < NUM_LEDS ; ++i)
  {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  
  delay(500);
}

