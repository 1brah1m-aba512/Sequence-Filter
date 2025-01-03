#ifndef FILTER_H_INCLUDED
#define FILTER_H_INCLUDED

#include "CCImage.h"
#include "UtilLib.h"

class Filter {

protected:
    double _kernel[3][3];
    int _kernelSize = 3;

    virtual void initializeKernel() = 0; // Pure virtual function
public:
    Filter(); // Default constructor
    virtual void applyFilter(CCImage& image, int numTimes) = 0; // Pure virtual function
};

#endif // FILTER_H_INCLUDED
