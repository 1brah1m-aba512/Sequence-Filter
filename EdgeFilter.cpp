#include "EdgeFilter.h"
#include <algorithm>  // For std::min and std::max

// Constructor initializing the edge detection filter
EdgeFilter::EdgeFilter() : Filter() {
    initializeKernel(); // Set up the edge detection kernel
}

// Initializes the kernel with values for edge detection
void EdgeFilter::initializeKernel() {
    _kernel[0][0] = -1; _kernel[0][1] = -1; _kernel[0][2] = -1;
    _kernel[1][0] = -1; _kernel[1][1] =  10; _kernel[1][2] = -1;
    _kernel[2][0] = -1; _kernel[2][1] = -1; _kernel[2][2] = -1;
}

// Applies the edge detection filter to the image
void EdgeFilter::applyFilter(CCImage& image, int numTimes) {
    int rows = image.getRows();
    int cols = image.getCols();

    // Temporary pixel storage
    RGBColour** tempPixels = new RGBColour*[rows];
    for (int i = 0; i < rows; ++i) {
        tempPixels[i] = new RGBColour[cols];
    }

    for (int pass = 0; pass < numTimes; ++pass) {
        for (int r = 1; r < rows - 1; ++r) {
            for (int c = 1; c < cols - 1; ++c) {
                double sumRed = 0.0, sumGreen = 0.0, sumBlue = 0.0;

                // Apply the kernel to the neighborhood pixels
                for (int i = -1; i <= 1; ++i) {
                    for (int j = -1; j <= 1; ++j) {
                        RGBColour color = image.getColour(r + i, c + j);
                        sumRed += color.intRed * _kernel[i + 1][j + 1];
                        sumGreen += color.intGreen * _kernel[i + 1][j + 1];
                        sumBlue += color.intBlue * _kernel[i + 1][j + 1];
                    }
                }

                // Clamp the values between 0 and 255
                tempPixels[r][c].intRed = std::min(std::max(static_cast<int>(sumRed), 0), 255);
                tempPixels[r][c].intGreen = std::min(std::max(static_cast<int>(sumGreen), 0), 255);
                tempPixels[r][c].intBlue = std::min(std::max(static_cast<int>(sumBlue), 0), 255);
            }
        }

        // Copy temporary results back to the image
        for (int r = 1; r < rows - 1; ++r) {
            for (int c = 1; c < cols - 1; ++c) {
                image.setPixelColour(r, c, tempPixels[r][c]);
            }
        }
    }

    // Deallocate temporary storage
    for (int i = 0; i < rows; ++i) {
        delete[] tempPixels[i];
    }
    delete[] tempPixels;
}
