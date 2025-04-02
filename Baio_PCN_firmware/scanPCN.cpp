#include "scanPCN.h"
#include <Joystick.h>

extern const uint8_t PCNlatchPin;
extern const uint8_t PCNclockPin;
extern const uint8_t PCNdataPin;

const byte registreLength = 8;

extern const bool debug;
extern byte PCNvalues[4];
extern Joystick_ Joystick;


void scanPCN() {
  digitalWrite(PCNlatchPin,1);
  delayMicroseconds(20);
  digitalWrite(PCNlatchPin,0);

  for (int k=0; k<4; k++) {
    for (int i=7; i>=0; i--) {
      digitalWrite(PCNclockPin, 0);
      delayMicroseconds(2);
      bool value = digitalRead(PCNdataPin);
      
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

      digitalWrite(PCNclockPin, 1);
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