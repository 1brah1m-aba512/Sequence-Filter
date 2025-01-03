#ifndef UTILLIB_H_INCLUDED
#define UTILLIB_H_INCLUDED

#include <iostream>

struct RGBColour {
    int intRed;
    int intGreen;
    int intBlue;
};

// Constants
static constexpr RGBColour DEFAULT_COLOUR = {255, 255, 255};
static const int NUM_ROWS = 1;
static const int NUM_COLS = 1;

// Error Codes
enum StatusCode {
    SUCCESS,
    ERROR_INVALID_CMD_ARGS,
    ERROR_CONVERSION,
    ERROR_OUT_OF_BOUNDS,
    ERROR_PPM_FILE,
    ERROR_INVALID_FILTER_TYPE
};

class CCImage;

CCImage loadPPMImage(std::string strFileName);
int covStrToInt(char* chString);

#endif // UTILLIB_H_INCLUDED
