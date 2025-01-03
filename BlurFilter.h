#ifndef BLURFILTER_H
#define BLURFILTER_H

#include "Filter.h"
#include "CCImage.h"

class BlurFilter : public Filter {
public:
    BlurFilter();
    void initializeKernel() override;
    void applyFilter(CCImage& image, int numTimes) override;

private:

    double _kernel[3][3];  // Assuming a 3x3 Gaussian kernel
};

#endif // BLURFILTER_H
