#include "UtilLib.h"
#include "CCImage.h"
#include <fstream>
#include <sstream>

// Loads a PPM image file and returns it as a CCImage object
CCImage loadPPMImage(std::string strFileName) {
    std::ifstream iPPM(strFileName.c_str()); // Open the PPM file
    if (iPPM.fail()) {
        std::cerr << "Could not open PPM file." << std::endl;
        exit(ERROR_PPM_FILE); // Exit if file cannot be opened
    }

    std::string strMagicNum = "";
    iPPM >> strMagicNum; // Read the magic number
    if (strMagicNum != "P3") {
        std::cerr << "Expected P3 File" << std::endl;
        exit(ERROR_PPM_FILE); // Exit if the file is not P3 format
    }

    int intRows = 0, intCols = 0, intMaxVal = 0;
    iPPM >> intCols >> intRows >> intMaxVal; // Read image dimensions and max value
    if (intMaxVal > 255) {
        std::cerr << "Maximum value should be 255." << std::endl;
        exit(ERROR_PPM_FILE); // Exit if max value exceeds 255
    }

    CCImage objImage(intRows, intCols); // Create CCImage with the specified dimensions
    RGBColour recPixel;

    // Populate the CCImage object with pixel data
    for (int r = 0; r < intRows; r++) {
        for (int c = 0; c < intCols; c++) {
            iPPM >> recPixel.intRed >> recPixel.intGreen >> recPixel.intBlue;
            if (iPPM.fail()) {
                std::cerr << "Invalid Pixel data" << std::endl;
                exit(ERROR_PPM_FILE); // Exit if pixel data is invalid
            }
            objImage.setPixelColour(r, c, recPixel);
        }
    }

    iPPM.close(); // Close the file
    return objImage; // Return the loaded image
}

// Converts a C-string to an integer
int covStrToInt(char* chString) {
    std::stringstream ss{chString}; // Initialize stringstream with input string
    int intNum = 0;
    ss >> intNum; // Convert to integer
    if (ss.fail()) {
        std::cerr << "Failed to convert to Integer." << std::endl;
        exit(ERROR_CONVERSION); // Exit if conversion fails
    }
    return intNum; // Return the converted integer
}
