//
// Created by CUI Shidong on 17/7/2016.
//

#include "McSimulation.h"

//McSimulation::McSimulation(bool isAntithetic) : isAntithetic_(isAntithetic) { }

void McSimulation::calculate(unsigned long maxSamples, unsigned long minSamples) {
    mcModel_ = shared_ptr<McModel>(new McModel(pathGenerator(), pathPricer()));
    value(maxSamples, minSamples);
}

void McSimulation::value(unsigned long maxSamples, unsigned long minSamples) {
    for (unsigned long j = 1; j <= maxSamples / minSamples; j++) {
        mcModel_->addSamples(minSamples);
    }
}

const MCStatistics &McSimulation::sampleAccumulator() const {
    return this->mcModel_->getStatistics();
}



