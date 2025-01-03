#include "Filter.h"

// Constructor implementation
Filter::Filter() {
    // Initialize the kernel to zero or any default value
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            _kernel[i][j] = 0.0;
        }
    }
}

// No other methods are implemented in the base class as all are pure virtual
