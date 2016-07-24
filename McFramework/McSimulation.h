//
// Created by CUI Shidong on 17/7/2016.
//

#ifndef FINANCE_MCSIMULATION_H
#define FINANCE_MCSIMULATION_H

#include "McFramework/McModel.h"

/* any Monte Carlo pricing engine derives from this MsSimulation */
class McSimulation {
public:
    void calculate(unsigned long maxSamples, unsigned long minSamples);

    void value(unsigned long maxSamples, unsigned long minSamples);

    const MCStatistics &sampleAccumulator() const;


private:
    virtual shared_ptr<PathGenerator<NormalMarsagliaBrayRng<UniformLEcuyerRNG1>>> pathGenerator() = 0;

    virtual shared_ptr<PathPricer> pathPricer() = 0;

    virtual vector<Time> timeGrid() = 0;

    shared_ptr<McModel> mcModel_;
//    shared_ptr<StochasticProcess> process_;
};


#endif //FINANCE_MCSIMULATION_H