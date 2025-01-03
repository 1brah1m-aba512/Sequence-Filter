#include "BlurFilter.h"
#include <cmath>

// Constructor for BlurFilter, initializing the base Filter class
BlurFilter::BlurFilter() : Filter()  {
    initializeKernel(); // Initializes the blur kernel
}

// Initializes the kernel with values to create a uniform blur effect
void BlurFilter::initializeKernel() {
    // Each element of the kernel is set to 1/9 to distribute the weight evenly
    _kernel[0][0] = 1.0 / 9; _kernel[0][1] = 1.0 / 9; _kernel[0][2] = 1.0 / 9;
    _kernel[1][0] = 1.0 / 9; _kernel[1][1] = 1.0 / 9; _kernel[1][2] = 1.0 / 9;
    _kernel[2][0] = 1.0 / 9; _kernel[2][1] = 1.0 / 9; _kernel[2][2] = 1.0 / 9;
}

// Applies the blur filter to the given image a specified number of times
void BlurFilter::applyFilter(CCImage& image, int numTimes) {
    int rows = image.getRows(); // Get the number of rows in the image
    int cols = image.getCols(); // Get the number of columns in the image

    // Perform the blur operation numTimes times for stronger effect
    for (int pass = 0; pass < numTimes; pass++) {
        CCImage tempImage = image; // Create a copy of the original image for processing

        // Iterate over each pixel, avoiding the boundary pixels
        for (int r = 1; r < rows - 1; r++) {
            for (int c = 1; c < cols - 1; c++) {
                double sumRed = 0.0;   // Accumulator for red channel
                double sumGreen = 0.0; // Accumulator for green channel
                double sumBlue = 0.0;  // Accumulator for blue channel

                // Apply the 3x3 kernel to the surrounding pixels
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        RGBColour color = tempImage.getColour(r + i, c + j); // Get the color of the neighboring pixel
                        sumRed += color.intRed * _kernel[i + 1][j + 1]; // Contribute to red channel
                        sumGreen += color.intGreen * _kernel[i + 1][j + 1]; // Contribute to green channel
                        sumBlue += color.intBlue * _kernel[i + 1][j + 1]; // Contribute to blue channel
                    }
                }

                // Create a new color with the computed values
                RGBColour newColor;
                newColor.intRed = static_cast<int>(sumRed);   // Convert red channel to integer
                newColor.intGreen = static_cast<int>(sumGreen); // Convert green channel to integer
                newColor.intBlue = static_cast<int>(sumBlue);  // Convert blue channel to integer

                // Update the pixel in the original image with the new color
                image.setPixelColour(r, c, newColor);
            }
        }
    }
}
