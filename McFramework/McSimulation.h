//
// Created by CUI Shidong on 17/7/2016.
//

#ifndef FINANCE_MCSIMULATION_H
#define FINANCE_MCSIMULATION_H

#include "McFramework/McModel.h"

/* any Monte Carlo pricing engine privately derives from this MsSimulation */
class McSimulation {
public:
//    McSimulation(bool isAntithetic = 0);

    void calculate(unsigned long maxSamples, unsigned long minSamples);

    void value(unsigned long maxSamples, unsigned long minSamples);

    const MCStatistics &sampleAccumulator() const;


private:
    virtual std::shared_ptr<PathGenerator<NormalMarsagliaBrayRng<UniformLEcuyerRNG1> > > pathGenerator() = 0;

    virtual std::shared_ptr<PathPricer> pathPricer() = 0;

    virtual vector<Time> timeGrid() = 0;

    std::shared_ptr<McModel> mcModel_;

    bool isAntithetic_;
//    shared_ptr<StochasticProcess> process_;
};


#endif //FINANCE_MCSIMULATION_H
