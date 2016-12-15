//
// Created by CUI Shidong on 16/7/2016.
//

#ifndef FINANCE_MCMODEL_H
#define FINANCE_MCMODEL_H

#include "PathGenerator.h"
#include "PathPricer.h"
#include "Statistics.h"
#include "RandNumGeneration/PseudoRandom.h"
#include "RandNumGeneration/Normal.h"

class McModel {
public:
    McModel(const std::shared_ptr<PathGenerator<SingleRandom<Normal<>>>> &pathGenerator,
            const std::shared_ptr<PathPricer> pathPricer);

    void addSamples(unsigned long numSamples);

    const MCStatistics &getStatistics() const;

private:
    std::shared_ptr<PathGenerator<SingleRandom<Normal<>>>> pathGenerator_;
    std::shared_ptr<PathPricer> pathPricer_;
    MCStatistics sampleAccumulator_;

};


#endif //FINANCE_MCMODEL_H
