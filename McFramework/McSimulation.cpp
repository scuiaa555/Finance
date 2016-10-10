//
// Created by CUI Shidong on 17/7/2016.
//

#include "McSimulation.h"

void McSimulation::calculate(unsigned long maxSamples, unsigned long minSamples) {
//    vector<double> v1(3);
//    shared_ptr<PathGenerator<NormalMarsagliaBrayRng<UniformLEcuyerRNG1>>> pathGenerator(
//            new PathGenerator<NormalMarsagliaBrayRng<UniformLEcuyerRNG1>>(process_, v1));
//    //shared_ptr<PathPricer> pathPricer_();
    mcModel_ = shared_ptr<McModel>(new McModel(pathGenerator(), pathPricer()));
    this->value(maxSamples, minSamples);
}

void McSimulation::value(unsigned long maxSamples, unsigned long minSamples) {
    for (unsigned long j = 1; j <= maxSamples / minSamples; j++) {
        mcModel_->addSamples(minSamples);
    }
}

const MCStatistics &McSimulation::sampleAccumulator() const {
    return this->mcModel_->getStatistics();
}



