#include "scanPCN.h"
#include <Joystick.h>

// extern const int PPAlatchPin;
// extern const int PPAclockPin;
// extern const int PPAdataPin;
const int PPAlatchPin = 7;
const int PPAdataPin = 4;
const int PPAclockPin = 6;

const byte registreLength = 8;
const bool debug = true;
// extern const byte registreLength;
// extern const bool debug;

extern byte PCNvalues[4];
extern Joystick_ Joystick;


void scanPCN() {
  digitalWrite(PPAlatchPin,1);
  delayMicroseconds(20);
  digitalWrite(PPAlatchPin,0);

  for (int k=0; k<4; k++) {
    for (int i=7; i>=0; i--) {
      digitalWrite(PPAclockPin, 0);
      delayMicroseconds(2);
      bool value = digitalRead(PPAdataPin);
      
      // if value has changed
      if (value != bitRead(PCNvalues[k], i)) {
        bitWrite(PCNvalues[k], i, value);

        Joystick.setButton(registreLength*k+i, value);
        // debug
        // if (debug) Serial.println(registreLength*k+i);
        if (debug) Serial.println(k);
        if (debug) Serial.println(i);
        if (debug) Serial.println(value);
        if (debug) Serial.println("----");
      }

      digitalWrite(PPAclockPin, 1);
      delayMicroseconds(2);
    }

    // ROTATY NONE POSITION
    if (!bitRead(PCNvalues[0], 7) && !PCNvalues[1] && !bitRead(PCNvalues[2], 0) && !bitRead(PCNvalues[2], 1)) {
      Joystick.setButton(32, 1);
    } else {
      Joystick.setButton(32, 0);
    }
  }
}