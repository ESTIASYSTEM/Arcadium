//pwm-with-millis.ino
//https://www.baldengineer.com/software-pwm-with-millis.html

#ifndef pwmWithMillis_h
#define pwmWithMillis_h

// macros for LED state
#define ON true
#define OFF false

// variables for pattern timing
unsigned long currentMillis = millis();
unsigned long previousMillis = 0;
unsigned long millisInterval = 100;

// variables for software PWM
unsigned long currentMicros = micros();
unsigned long previousMicros = 0;
// this is the frequency of the sw PWM
// frequency = 1/(2 * microInterval)
unsigned long microInterval = 50;

const byte pwmMax = 100;

// fading (for the timing)
int fadeIncrement = 1;

// typedef for properties of each sw pwm pin
typedef struct pwmPins {
  int pin;
  int pwmValue;
  bool pinState;
  int pwmTickCount;
} pwmPin;

// create the sw pwm pins
// these can be any I/O pin
// that can be set to output!

const int pinCount = 8;
const byte pins[pinCount] = {2, 3, 5, 6, 9, 10, 11, 12};



pwmPin myPWMpins[pinCount];

// function to "setup" the sw pwm pin states
// modify to suit your needs
// this creates an alternating fade pattern
void setupPWMpins(int pinNo, int PWM) {
  myPWMpins[pinNo].pin = pinNo;
  myPWMpins[pinNo].pwmValue = PWM;
  myPWMpins[pinNo].pinState = ON;
  myPWMpins[pinNo].pwmTickCount = 0;

  // unlike analogWrite(), this is necessary
    pinMode(pinNo, OUTPUT);
}

void pwmFadePattern() {
  // go through each sw pwm pin, and increase
  // the pwm value. this would be like
  // calling analogWrite() on each hw pwm pin
  for (int index = 0; index < pinCount; index++) {
    myPWMpins[index].pwmValue += fadeIncrement;
    if (myPWMpins[index].pwmValue > 100)
      myPWMpins[index].pwmValue = 0;
  }
}


void handlePWM() {
  currentMicros = micros();
  // check to see if we need to increment our PWM counters yet
  if (currentMicros - previousMicros >= microInterval) {
    // Increment each pin's counter
    for (int index = 0; index < pinCount; index++) {
      // each pin has its own tickCounter
      myPWMpins[index].pwmTickCount++;

      // determine if we're counting on or off time
      if (myPWMpins[index].pinState == ON) {
        // see if we hit the desired on percentage
        // not as precise as 255 or 1024, but easier to do math
        if (myPWMpins[index].pwmTickCount >= myPWMpins[index].pwmValue) {
          myPWMpins[index].pinState = OFF;
        }
      } else {
        // if it isn't on, it is off
        if (myPWMpins[index].pwmTickCount >= pwmMax) {
          myPWMpins[index].pinState = ON;
          myPWMpins[index].pwmTickCount = 0;
        }
      }
      // could probably use some bitwise optimization here, digitalWrite()
      // really slows things down after 10 pins.
      digitalWrite(myPWMpins[index].pin, myPWMpins[index].pinState);
    }
    // reset the micros() tick counter.
    digitalWrite(13, !digitalRead(13));
    previousMicros = currentMicros;
  }
}

#endif

// Code from james@baldengineer.com
// email | twitter | www
// See more at: https://www.baldengineer.com/software-pwm-with-millis.html



