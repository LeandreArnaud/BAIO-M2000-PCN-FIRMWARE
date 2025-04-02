#include "getLedValueFromNumber.h"

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
        default:
            return false;
    }
}