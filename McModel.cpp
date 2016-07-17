//
// Created by CUI Shidong on 16/7/2016.
//

#include "McModel.h"

McModel::McModel(const shared_ptr<PathGenerator<NormalMarsagliaBrayRng<UniformLEcuyerRNG1> > > &pathGenerator,
                 const shared_ptr<PathPricer> pathPricer)
        : pathGenerator_(pathGenerator), pathPricer_(pathPricer) {
}

void McModel::addSamples(unsigned long numSamples) {
    double price;
    for (unsigned long j = 1; j <= numSamples; j++) {
        price += (*pathPricer_)(pathGenerator_->next());
    }
    price /= numSamples;
    sampleAccumulator_.add(numSamples, price);
}

const MCStatistics &McModel::GetStatistics() const {
    return sampleAccumulator_;
}






