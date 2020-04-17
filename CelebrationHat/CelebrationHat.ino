/*
 * Waving flags with 2 servos - Celebration hat project for 1000 subscribers milestone on YouTueb
 * https://youtu.be/3ZiWmliV2Q8
 * 
 * This code is written by Blagojce Kolicoski
 * for the Taste The Code YouTube Channel
 * https://www.youtube.com/tastethecode
 */
#include <Servo.h>

Servo servo1;
Servo servo2;

const int buttonPin = 7;

int buttonState;
int lastButtonState = LOW;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin, INPUT);
  servo1.attach(9);
  servo2.attach(11);
  resetPos();
}

void loop() {
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        int action = random(1, 4);
        switch (action) {
          case 1:
            rndMove();
            break;
          case 2:
            sweep();
            break;
          case 3:
            reverseSweep();
            break;
        }
      }
    }
  }
  resetPos();
  lastButtonState = reading;
}

void resetPos() {
  servo1.write(90);
  servo2.write(90);
}

void rndMove() {
  int pos1, pos2;
  for (int r = 0; r <= 5; r += 1) {
    pos1 = random(5, 175);
    pos2 = random(5, 175);
  
    servo1.write(pos1);
    delay(500);
    servo2.write(pos2);
  
    delay(500);
  }
}

void sweep() {
  for (int r = 0; r <= 5; r += 1) {
    for (int pos = 30; pos <= 150; pos += 5) {
      servo1.write(pos);
      servo2.write(pos);
      delay(15);
    }
    for (int pos = 150; pos >= 30; pos -= 5) {
      servo1.write(pos);
      servo2.write(pos);
      delay(15);
    }
  }
}

void reverseSweep() {
  for (int r = 0; r <= 5; r += 1) {
    for (int pos = 30; pos <= 150; pos += 5) {
      servo1.write(pos);
      servo2.write(180 - pos);
      delay(15);
    }
    for (int pos = 150; pos >= 30; pos -= 5) {
      servo1.write(pos);
      servo2.write(180 - pos);
      delay(15);
    }
  }
}
