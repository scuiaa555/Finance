//
// Created by CUI Shidong on 17/7/2016.
//

#ifndef FINANCE_MCSIMULATION_H
#define FINANCE_MCSIMULATION_H

#include "McFramework/McModel.h"

/* any Monte Carlo pricing engine privately derives from this MsSimulation */
template<typename RNG>
class McSimulation {
public:
//    McSimulation(bool isAntithetic = 0);

    void calculate(unsigned long maxSamples, unsigned long minSamples);

    void value(unsigned long maxSamples, unsigned long minSamples);

    const MCStatistics &sampleAccumulator() const;


private:
    virtual std::shared_ptr<PathGenerator<RNG> > pathGenerator() = 0;

    virtual std::shared_ptr<PathPricer> pathPricer() = 0;

    virtual vector<Time> timeGrid() = 0;

    std::shared_ptr<McModel> mcModel_;

    bool isAntithetic_;
//    shared_ptr<StochasticProcess> process_;
};

template<typename RNG>
void McSimulation<RNG>::calculate(unsigned long maxSamples, unsigned long minSamples) {
    mcModel_ = std::shared_ptr<McModel>(new McModel(pathGenerator(), pathPricer()));
    value(maxSamples, minSamples);
}

template<typename RNG>
void McSimulation<RNG>::value(unsigned long maxSamples, unsigned long minSamples) {
    for (unsigned long j = 1; j <= maxSamples / minSamples; j++) {
        mcModel_->addSamples(minSamples);
    }
}

template<typename RNG>
const MCStatistics &McSimulation<RNG>::sampleAccumulator() const {
    return this->mcModel_->getStatistics();
}


#endif //FINANCE_MCSIMULATION_H
