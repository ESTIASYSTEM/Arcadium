//gÃ©rer les nuances de couleurs
//https://www.carnetdumaker.net/articles/utiliser-des-leds-rgb-avec-une-carte-arduino-genuino/

//faire du software PWM
//https://www.baldengineer.com/software-pwm-with-millis.html

//bibliothÃ©que software PWM
#include "pwmWithMillis.h"

/* Broches */

#define PIN_LED_R 4
#define PIN_LED_G 3
#define PIN_LED_B 2

/*
  Control a RGB led with Hue, Saturation and Brightness (HSB / HSV )

  Hue is change by an analog input.
  Brightness is changed by a fading function.
  Saturation stays constant at 255

  getRGB() function based on <http://www.codeproject.com/miscctrl/CPicker.asp>
  dim_curve idea by Jims

  created 05-01-2010 by kasperkamperman.com
*/

/*
  dim_curve 'lookup table' to compensate for the nonlinearity of human vision.
  Used in the getRGB function on saturation and brightness to make 'dimming' look more natural.
  Exponential function used to create values below :
  x from 0 - 255 : y = round(pow( 2.0, x+64/40.0) - 1)
*/

const byte dim_curve[] = {
  0,   1,   1,   2,   2,   2,   2,   2,   2,   3,   3,   3,   3,   3,   3,   3,
  3,   3,   3,   3,   3,   3,   3,   4,   4,   4,   4,   4,   4,   4,   4,   4,
  4,   4,   4,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,   6,   6,   6,
  6,   6,   6,   6,   6,   7,   7,   7,   7,   7,   7,   7,   8,   8,   8,   8,
  8,   8,   9,   9,   9,   9,   9,   9,   10,  10,  10,  10,  10,  11,  11,  11,
  11,  11,  12,  12,  12,  12,  12,  13,  13,  13,  13,  14,  14,  14,  14,  15,
  15,  15,  16,  16,  16,  16,  17,  17,  17,  18,  18,  18,  19,  19,  19,  20,
  20,  20,  21,  21,  22,  22,  22,  23,  23,  24,  24,  25,  25,  25,  26,  26,
  27,  27,  28,  28,  29,  29,  30,  30,  31,  32,  32,  33,  33,  34,  35,  35,
  36,  36,  37,  38,  38,  39,  40,  40,  41,  42,  43,  43,  44,  45,  46,  47,
  48,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,
  63,  64,  65,  66,  68,  69,  70,  71,  73,  74,  75,  76,  78,  79,  81,  82,
  83,  85,  86,  88,  90,  91,  93,  94,  96,  98,  99,  101, 103, 105, 107, 109,
  110, 112, 114, 116, 118, 121, 123, 125, 127, 129, 132, 134, 136, 139, 141, 144,
  146, 149, 151, 154, 157, 159, 162, 165, 168, 171, 174, 177, 180, 183, 186, 190,
  193, 196, 200, 203, 207, 211, 214, 218, 222, 226, 230, 234, 238, 242, 248, 255,
};

int fadeVal   = 0; // value that changes between 0-255
int fadeSpeed = 1; // 'speed' of fading
bool fadeIncrease = true; // indicate if the brightness growth

// getRGB function stores RGB values in this array
// use these values for the red, blue, green led.
int rgb_colors[3];

// set HSB values
//HSB color Dark moderate violet
//HSV (or HSB)   267.3°, 67.3, 57.6
int hue        = 267;                               // hue is a number between 0 and 360
int saturation = 67;                                // saturation is a number between 0 - 255
int brightness = 165;                               // value is a number between 0 - 255


void setup() {
  Serial.begin(57600);

  //to the PWM
  setupPWMpins(PIN_LED_R, 0);
  setupPWMpins(PIN_LED_G, 0);
  setupPWMpins(PIN_LED_B, 0);

  pinMode(13, OUTPUT);
}

void loop()  {
  //to use the PWM
  // this is the magic for sw pwm
  // need to call this anytime you
  // have a long operation
  handlePWM();

  // check timer for fading pattern
  // this would be the same
  // if we used analogWrite()
  currentMillis = millis();
  if (currentMillis - previousMillis >= millisInterval) {
    // moved to own funciton for clarity
    //pwmFadePattern();

    if (fadeIncrease) {
      // fade from 0 - 255 and back with a certain speed
      fadeVal = fadeVal + fadeSpeed;         // change fadeVal by speed
      fadeVal = constrain(fadeVal, 0, brightness);  // keep fadeVal between 0 and 255
    }

    else {
      // fade from 0 - 255 and back with a certain speed
      fadeVal = fadeVal - fadeSpeed;         // change fadeVal by speed
      fadeVal = constrain(fadeVal, 0, brightness);  // keep fadeVal between 0 and 255

    }
    if (fadeVal == brightness || fadeVal == 0)    // change from up>down or down-up (negative/positive)
    { fadeIncrease = !fadeIncrease;
    }


    getRGB(hue, saturation, fadeVal, rgb_colors); // converts HSB to RGB
    setupPWMpins(PIN_LED_R, rgb_colors[0]);            // red value in index 0 of rgb_colors array
    setupPWMpins(PIN_LED_G, rgb_colors[1]);            // green value in index 1 of rgb_colors array
    setupPWMpins(PIN_LED_B, rgb_colors[2]);            // blue value in index 2 of rgb_colors array

    // setup clock for next tick
    previousMillis = currentMillis;
  }
  //end of the PWM part

}

void getRGB(int hue, int saturation, int brightness, int colors[3]) {
  /* convert hue, saturation and brightness ( HSB/HSV ) to RGB
     The dim_curve is used only on brightness/value and on saturation (inverted).
     This looks the most natural.
  */

  brightness = dim_curve[brightness];
  saturation = 255 - dim_curve[255 - saturation];

  int r;
  int g;
  int b;
  int base;

  if (saturation == 0) { // Acromatic color (gray). Hue doesn't mind.
    colors[0] = brightness;
    colors[1] = brightness;
    colors[2] = brightness;
  } else  {

    base = ((255 - saturation) * brightness) >> 8;

    switch (hue / 60) {
      case 0:
        r = brightness;
        g = (((brightness - base) * hue) / 60) + base;
        b = base;
        break;

      case 1:
        r = (((brightness - base) * (60 - (hue % 60))) / 60) + base;
        g = brightness;
        b = base;
        break;

      case 2:
        r = base;
        g = brightness;
        b = (((brightness - base) * (hue % 60)) / 60) + base;
        break;

      case 3:
        r = base;
        g = (((brightness - base) * (60 - (hue % 60))) / 60) + base;
        b = brightness;
        break;

      case 4:
        r = (((brightness - base) * (hue % 60)) / 60) + base;
        g = base;
        b = brightness;
        break;

      case 5:
        r = brightness;
        g = base;
        b = (((brightness - base) * (60 - (hue % 60))) / 60) + base;
        break;
    }

    colors[0] = r;
    colors[1] = g;
    colors[2] = b;
  }
}
