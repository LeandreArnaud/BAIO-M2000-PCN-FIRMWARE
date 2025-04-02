#include <Joystick.h>
#include "Adafruit_LEDBackpack.h"
#define DCSBIOS_DEFAULT_SERIAL
#include "DcsBios.h"

#include "writePCNDigits.h"
#include "scanPCN.h"


/********* PINs SETUP **********/
// const int PCN_SDA = 2;
// const int PCN_SCL = 3;

const int PCNlatchPin = 7;
const int PCNdataPin = 4;
const int PCNclockPin = 6;
// const byte registreLength = 8;
const byte PCNbacklightPin = 5;

const bool debug = true;



/********* INIT VALUES AND CST **********/
byte PCNvalues[4] = {255, 255, 255, 255};
const char* lat = "12.34.5";
const char* lon = "12.34.56";
uint8_t prep = 1;
uint8_t dest = 1;


bool isDCSinmission = false;

// bool mis = false;
// bool misp = false;
// bool mag = false;
// bool magp = false;
// bool par = false;

Joystick_ Joystick(
  0x06, // id of the gamepad, icrease in other pads to avoid conflict
  0x05, //Gamepad
  33, // button
  0, // hat
  false, // X
  false, // Y
  false, // Z
  false, // Rx
  false, // Ry
  false, // Rz
  false, // rudder
  false, // throttle
  false, // rudder
  false, // rudder
  false // steering
);

Adafruit_LEDBackpack matrix = Adafruit_LEDBackpack();








/********* SETUP **********/
void setup() {
  DcsBios::setup();

  matrix.begin(0x74);  // pass in the address 70 or 74
  matrix.setBrightness(1);
  matrix.setDisplayState(true);

  pinMode(PCNbacklightPin, OUTPUT);

  pinMode(PCNlatchPin, OUTPUT);
  pinMode(PCNclockPin, OUTPUT);
  pinMode(PCNdataPin, INPUT);

  Joystick.begin();

  if (debug) Serial.begin(9600);

  // init digits
  for (uint8_t i=0; i<8; i++) {
    matrix.displaybuffer[i] = 0b0000000000000000;
    delay(100);
  }
  matrix.writeDisplay();
  analogWrite(PCNbacklightPin, 255);
}










/********* LOOP **********/
void loop() {
  DcsBios::loop();

  scanPCN();
  delay(10);

  // delay(10);
  // writePCNDigits(bombeNumber, bombeMeters, mis, misp, mag, magp, par);
  // if (!isDCSinmission && bitRead(PCNvalues[0], 7)) {
  //   writePCNDigits(88, 88, 1, 1, 1, 1, 1);
  // } else {
  //   writePCNDigits(bombeNumber, bombeMeters, mis, misp, mag, magp, par);
  // }

  // writePCNDigits();
}
