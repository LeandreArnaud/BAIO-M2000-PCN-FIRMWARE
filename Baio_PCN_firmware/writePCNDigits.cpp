#include "writePCNDigits.h"
#include "getLedValueFromNumber.h"
#include <Adafruit_LEDBackpack.h>

extern Adafruit_LEDBackpack matrix;
extern const char* lat;
extern const char* lon;
extern uint8_t prep;
extern uint8_t dest;

void writePCNDigits() {
    for (uint8_t i = 0; i < 7; i++) {
        uint16_t valToWrite = 0b0000000000000000;
        bitWrite(valToWrite, 11, getLedValueFromNumber(prep / 10, i));
        bitWrite(valToWrite, 12, getLedValueFromNumber(prep % 10, i));
        bitWrite(valToWrite, 13, getLedValueFromNumber(dest / 10, i));
        bitWrite(valToWrite, 14, getLedValueFromNumber(dest % 10, i));

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