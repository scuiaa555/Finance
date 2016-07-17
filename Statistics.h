//
// Created by CUI Shidong on 17/7/2016.
//

#ifndef FINANCE_STATISTICS_H
#define FINANCE_STATISTICS_H


#include <vector>
#include "nameDef.h"

class MCStatistics {
public:

    Money mean() const;

    void add(unsigned long numSample, Money price);

    class SampleResults {
    public:
        SampleResults(unsigned long numSample, Money price) : numSample_(numSample), price_(price) { }

        unsigned long numSample_;
        Money price_;
    };

private:
    std::vector<SampleResults> sampleAccumulator_;
    unsigned long totalNum;

};


#endif //FINANCE_STATISTICS_H
