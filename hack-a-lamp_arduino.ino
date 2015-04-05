
int redPin = 6, greenPin = 5, bluePin = 3;
int delayLed = 10; // make the fade smoother

// last colour of each led
int red_old = 0, green_old = 0, blue_old = 0; 

void setup() {

  Serial.begin(19200);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.println("Ready!");
}

void loop() {

  while (Serial.available() > 0) {
    
    int red = 0, green = 0, blue = 0;

    delayLed = Serial.parseInt();

    red = Serial.parseInt();
    
    green = Serial.parseInt();
    
    blue = Serial.parseInt();
    
    if (Serial.read() == '\n'){

      //For common anode led, use ie: red = 255 - constrain(red, 0, 255);
      red = constrain(red, 0, 255);
      green = constrain(green, 0, 255);
      blue = constrain(blue, 0, 255);

      //Modify each led colour
      fade(redPin, red, red_old,delayLed);
      fade(greenPin, green, green_old,delayLed);
      fade(bluePin, blue, blue_old,delayLed);
      
      
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