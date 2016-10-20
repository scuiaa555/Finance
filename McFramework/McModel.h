//
// Created by CUI Shidong on 16/7/2016.
//

#ifndef FINANCE_MCMODEL_H
#define FINANCE_MCMODEL_H

#include "PathGenerator.h"
#include "PathPricer.h"
#include "Statistics.h"

class McModel {
public:
    McModel(const std::shared_ptr<PathGenerator<NormalMarsagliaBrayRng<UniformLEcuyerRNG1> > > &pathGenerator,
            const std::shared_ptr<PathPricer> pathPricer);

    void addSamples(unsigned long numSamples);

    const MCStatistics &getStatistics() const;

private:
    std::shared_ptr<PathGenerator<NormalMarsagliaBrayRng<UniformLEcuyerRNG1> > > pathGenerator_;
    std::shared_ptr<PathPricer> pathPricer_;
    MCStatistics sampleAccumulator_;

};


#endif //FINANCE_MCMODEL_H
