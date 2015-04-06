#include "Adafruit_NeoPixel.h"
#define PIXEL_PIN    6    // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 16
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

int redPin = 6, greenPin = 5, bluePin = 3;
int delayLed = 10; // make the fade smoother

// last colour of each led
int red_old = 0, green_old = 0, blue_old = 0;

boolean isStrip  = true;

void setup() {

  Serial.begin(19200);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.println("Ready!");
  //strip.ledsetup();
  strip.begin();
}

void loop() {

  while (Serial.available() > 0) {
    digitalWrite(13, HIGH);
    int red = 0, green = 0, blue = 0;

    delayLed = Serial.parseInt();
    red = Serial.parseInt();
    green = Serial.parseInt();
    blue = Serial.parseInt();

    if (Serial.read() == '\n') {
    digitalWrite(13, LOW);
      //For common anode led, use ie: red = 255 - constrain(red, 0, 255);
      red = constrain(red, 0, 255);
      green = constrain(green, 0, 255);
      blue = constrain(blue, 0, 255);


      //Modify each led colour
      if (isStrip) {
        colorWipe(strip.Color(red, green, blue), delayLed); // Red
      } else {
        fade(redPin, red, red_old, delayLed);
        fade(greenPin, green, green_old, delayLed);
        fade(bluePin, blue, blue_old, delayLed);
      }

      //Store colour data
      red_old = red;
      green_old = green;
      blue_old = blue;
    }
  }
}

void fade(int pin, int newValue, int aktValue, int delayValue) {

  if (newValue > aktValue) {
    for (int i = aktValue; i <= newValue; i++) {
      analogWrite(pin, i);
      delay(delayValue);
    }
  } else if (newValue < aktValue) {
    for (int i = aktValue; i >= newValue; i--) {
      analogWrite(pin, i);
      delay(delayValue);
    }
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
