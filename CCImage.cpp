#include "CCImage.h"
#include <sstream>

// Default constructor initializing the image with default dimensions
CCImage::CCImage() : CCImage(NUM_ROWS, NUM_COLS) {}

// Constructor initializing the image with specified dimensions
CCImage::CCImage(unsigned int intRows, unsigned int intCols) {
    allocMemory(intRows, intCols);
}

// Copy constructor creating a deep copy of the given CCImage object
CCImage::CCImage(const CCImage& objOriginal) : CCImage(objOriginal._intRows, objOriginal._intCols) {
    clone(objOriginal);
}

// Destructor releasing allocated memory
CCImage::~CCImage() {
    deallocMemory();
}

// Returns the number of rows in the image
unsigned int CCImage::getRows() const {
    return _intRows;
}

// Returns the number of columns in the image
unsigned int CCImage::getCols() const {
    return _intCols;
}

// Retrieves the color of a specific pixel
RGBColour CCImage::getColour(unsigned int intRow, unsigned int intCol) const {
    return _recPixels[intRow][intCol];
}

// Sets all pixels in the image to a specific color
void CCImage::setImageColour(RGBColour recColour) {
    for (int r = 0; r < _intRows; r++) {
        for (int c = 0; c < _intCols; c++) {
            _recPixels[r][c] = recColour;
        }
    }
}

// Sets the color of a specific pixel
void CCImage::setPixelColour(unsigned int intRow, unsigned int intCol, RGBColour recColour) {
    _recPixels[intRow][intCol] = recColour;
}

// Converts the image data to a PPM format string
std::string CCImage::toPPM() const {
    std::stringstream ssPPM;
    ssPPM << "P3" << std::endl
          << _intCols << " " << _intRows << std::endl
          << "255" << std::endl;
    for (unsigned int r = 0; r < _intRows; r++) {
        for (unsigned int c = 0; c < _intCols; c++) {
            ssPPM << _recPixels[r][c].intRed << " "
                  << _recPixels[r][c].intGreen << " "
                  << _recPixels[r][c].intBlue << " ";
        }
        ssPPM << std::endl;
    }
    return ssPPM.str();
}

// Allocates memory for the image and initializes pixels to a default color
void CCImage::allocMemory(unsigned int intRows, unsigned int intCols) {
    _intRows = intRows;
    _intCols = intCols;
    _recPixels = new RGBColour*[intRows];
    for (unsigned int r = 0; r < intRows; r++) {
        _recPixels[r] = new RGBColour[intCols];
        for (unsigned int c = 0; c < intCols; c++) {
            _recPixels[r][c] = DEFAULT_COLOUR;
        }
    }
}

// Deallocates memory used by the image
void CCImage::deallocMemory() {
    for (unsigned int r = 0; r < _intRows; r++) {
        delete[] _recPixels[r];
    }
    delete[] _recPixels;
    _recPixels = nullptr;
}

// Copies the pixel data from another CCImage object
void CCImage::clone(const CCImage& objOriginal) {
    for (unsigned int r = 0; r < _intRows; r++) {
        for (unsigned int c = 0; c < _intCols; c++) {
            _recPixels[r][c].intRed = objOriginal._recPixels[r][c].intRed;
            _recPixels[r][c].intGreen = objOriginal._recPixels[r][c].intGreen;
            _recPixels[r][c].intBlue = objOriginal._recPixels[r][c].intBlue;
        }
    }
}
