//
// Created by CUI Shidong on 17/7/2016.
//

#include "Statistics.h"

Money MCStatistics::mean() const{
    Money mean = 0.0;
    for (std::vector<SampleResults>::const_iterator iter = sampleAccumulator_.begin();
         iter != sampleAccumulator_.end(); iter++) {
        mean += (double(iter->numSample_) / totalNum) * iter->price_;
    }
    return mean;
}

void MCStatistics::add(unsigned long numSample, Money price) {
    sampleAccumulator_.push_back(SampleResults(numSample, price));
    totalNum += numSample;
}



