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
        // uint16_t valToWrite = 0b0000000000000000;
        bitWrite(matrix.displaybuffer[i], 11, getLedValueFromNumber(prep / 10, i));
        bitWrite(matrix.displaybuffer[i], 12, getLedValueFromNumber(prep % 10, i));
        bitWrite(matrix.displaybuffer[i], 13, getLedValueFromNumber(dest / 10, i));
        bitWrite(matrix.displaybuffer[i], 14, getLedValueFromNumber(dest % 10, i));

        // write lat
        bitWrite(matrix.displaybuffer[i], 0, getLedValueFromNumber(lat[0] - '0', i));
        bitWrite(matrix.displaybuffer[i], 1, getLedValueFromNumber(lat[1] - '0', i));
        bitWrite(matrix.displaybuffer[i], 2, getLedValueFromNumber(lat[3] - '0', i));
        bitWrite(matrix.displaybuffer[i], 3, getLedValueFromNumber(lat[4] - '0', i));
        bitWrite(matrix.displaybuffer[i], 4, getLedValueFromNumber(lat[6] - '0', i));

        // write lon
        // bitWrite(matrix.displaybuffer[i], 5, getLedValueFromNumber(lon[0] - '0', i));
        // bitWrite(matrix.displaybuffer[i], 6, getLedValueFromNumber(lon[1] - '0', i));
        // bitWrite(matrix.displaybuffer[i], 7, getLedValueFromNumber(lon[3] - '0', i));
        // bitWrite(matrix.displaybuffer[i], 8, getLedValueFromNumber(lon[4] - '0', i));
        // bitWrite(matrix.displaybuffer[i], 9, getLedValueFromNumber(lon[6] - '0', i));
        // bitWrite(matrix.displaybuffer[i], 10, getLedValueFromNumber(lon[7] - '0', i));
    }
    // write dots
    bitWrite(matrix.displaybuffer[7], 1, 1);
    bitWrite(matrix.displaybuffer[7], 3, 1);
    bitWrite(matrix.displaybuffer[7], 6, 1);
    bitWrite(matrix.displaybuffer[7], 8, 1);

    matrix.writeDisplay();
}