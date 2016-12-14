//
// Created by CUI Shidong on 16/7/2016.
//

#include "McModel.h"

McModel::McModel(
        const std::shared_ptr<PathGenerator<SingleRandom<NormalMarsagliaBrayRng<UniformLEcuyerRNG1> >>> &pathGenerator,
        const std::shared_ptr<PathPricer> pathPricer
)
        :

        pathGenerator_(pathGenerator), pathPricer_(pathPricer), sampleAccumulator_() {
}

void McModel::addSamples(unsigned long numSamples) {
    double price = 0.0;
    for (unsigned long j = 1; j <= numSamples; j++) {
        price += (*pathPricer_)(pathGenerator_->next());
    }
    price /= numSamples;
    sampleAccumulator_.add(numSamples, price);
}

const MCStatistics &McModel::getStatistics() const {
    return sampleAccumulator_;
}






