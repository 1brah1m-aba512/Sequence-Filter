#ifndef EDGEFILTER_H_INCLUDED
#define EDGEFILTER_H_INCLUDED

#include "Filter.h"

class EdgeFilter : public Filter {
public:

    EdgeFilter();
    void initializeKernel() override;
    void applyFilter(CCImage& image, int numTimes) override;
};

#endif // EDGEFILTER_H_INCLUDED
