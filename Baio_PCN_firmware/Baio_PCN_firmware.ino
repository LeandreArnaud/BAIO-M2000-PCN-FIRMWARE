#include <Joystick.h>
#include "Adafruit_LEDBackpack.h"
#define DCSBIOS_DEFAULT_SERIAL
#include "DcsBios.h"


/********* PINs SETUP **********/
const int PPA_SDA = 2;
const int PPA_SCL = 3;
const int PPAlatchPin = 7;
const int PPAdataPin = 4;
const int PPAclockPin = 6;
const byte PPAbacklightPin = 5;

const bool debug = false;



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
  16, // button
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

  pinMode(PPAbacklightPin, OUTPUT);

  // pinMode(PPAlatchPin, OUTPUT);
  // pinMode(PPAclockPin, OUTPUT);
  // pinMode(PPAdataPin, INPUT);

  // Joystick.begin();

  if (debug) Serial.begin(9600);

  // init digits
  for (uint8_t i=0; i<8; i++) {
    matrix.displaybuffer[i] = 0b0000000000000000;
    delay(100);
  }
  matrix.writeDisplay();
  analogWrite(PPAbacklightPin, 255);
}










/********* LOOP **********/
void loop() {
  DcsBios::loop();

  // scanPPA();
  // delay(10);
  // writePPADigits(bombeNumber, bombeMeters, mis, misp, mag, magp, par);
  // if (!isDCSinmission && bitRead(PPAvalues[0], 7)) {
  //   writePPADigits(88, 88, 1, 1, 1, 1, 1);
  // } else {
  //   writePPADigits(bombeNumber, bombeMeters, mis, misp, mag, magp, par);
  // }

  writePCNDigits();
  delay(1000);
}








//            h   hd bd b bg hg mdl dot
bool zero[] = {1, 1, 1, 1, 1, 1, 0, 0};
bool one[] = {0, 1, 1, 0, 0, 0, 0, 0};
bool two[] = {1, 1, 0, 1, 1, 0, 1, 0};
bool three[] = {1, 1, 1, 1, 0, 0, 1, 0};
bool four[] = {0, 1, 1, 0, 0, 1, 1, 0};
bool five[] = {1, 0, 1, 1, 0, 1, 1, 0};
bool six[] = {1, 0, 1, 1, 1, 1, 1, 0};
bool seven[] = {1, 1, 1, 0, 0, 0, 0, 0};
bool eight[] = {1, 1, 1, 1, 1, 1, 1, 0};
bool nine[] = {1, 1, 1, 1, 0, 1, 1, 0};

bool getLedValueFromNumber(int number, int ledNumber) {
  switch (number) {
    case 0:
      return zero[ledNumber];
    case 1:
      return one[ledNumber];
    case 2:
      return two[ledNumber];
    case 3:
      return three[ledNumber];
    case 4:
      return four[ledNumber];
    case 5:
      return five[ledNumber];
    case 6:
      return six[ledNumber];
    case 7:
      return seven[ledNumber];
    case 8:
      return eight[ledNumber];
    case 9:
      return nine[ledNumber];
  }
}

void writePCNDigits() {
  for (uint8_t i=0; i<7; i++) {
    uint16_t valToWrite = 0b0000000000000000;
    bitWrite(valToWrite, 11, getLedValueFromNumber(prep/10, i));
    bitWrite(valToWrite, 12, getLedValueFromNumber(prep%10, i));
    bitWrite(valToWrite, 13, getLedValueFromNumber(dest/10, i));
    bitWrite(valToWrite, 14, getLedValueFromNumber(dest%10, i));

    // write lat
    bitWrite(valToWrite, 0, getLedValueFromNumber(lat[0] - '0', i));
    bitWrite(valToWrite, 1, getLedValueFromNumber(lat[1] - '0', i));
    bitWrite(valToWrite, 2, getLedValueFromNumber(lat[3] - '0', i));
    bitWrite(valToWrite, 3, getLedValueFromNumber(lat[4] - '0', i));
    bitWrite(valToWrite, 4, getLedValueFromNumber(lat[6] - '0', i));

    // write lon
    bitWrite(valToWrite, 5, getLedValueFromNumber(lon[0] - '0', i));
    bitWrite(valToWrite, 6, getLedValueFromNumber(lon[1] - '0', i));
    bitWrite(valToWrite, 7, getLedValueFromNumber(lon[3] - '0', i));
    bitWrite(valToWrite, 8, getLedValueFromNumber(lon[4] - '0', i));
    bitWrite(valToWrite, 9, getLedValueFromNumber(lon[6] - '0', i));
    bitWrite(valToWrite, 10, getLedValueFromNumber(lon[7] - '0', i));

    matrix.displaybuffer[i] = valToWrite;
    delay(10);
  }

  // write dots
  uint16_t valToWrite = 0b0000000000000000;
  bitWrite(valToWrite, 1, 1);
  bitWrite(valToWrite, 3, 1);
  bitWrite(valToWrite, 6, 1);
  bitWrite(valToWrite, 8, 1);
  matrix.displaybuffer[7] = valToWrite;

  matrix.writeDisplay();
  
}

