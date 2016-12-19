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

template<typename RNG>
class McModel {
public:
    McModel(const std::shared_ptr<PathGenerator<RNG>> &pathGenerator,
            const std::shared_ptr<PathPricer> pathPricer);

    void addSamples(unsigned long numSamples);

    const MCStatistics &getStatistics() const;

private:
    std::shared_ptr<PathGenerator<RNG>> pathGenerator_;
    std::shared_ptr<PathPricer> pathPricer_;
    MCStatistics sampleAccumulator_;

};

template<typename RNG>
McModel<RNG>::McModel(
        const std::shared_ptr<PathGenerator<RNG>> &pathGenerator,
        const std::shared_ptr<PathPricer> pathPricer): pathGenerator_(pathGenerator), pathPricer_(pathPricer),
                                                       sampleAccumulator_() {
}

template<typename RNG>
void McModel<RNG>::addSamples(unsigned long numSamples) {
    double price = 0.0;
    for (unsigned long j = 1; j <= numSamples; j++) {
        price += (*pathPricer_)(pathGenerator_->next());
    }
    price /= numSamples;
    sampleAccumulator_.add(numSamples, price);
}

template<typename RNG>
const MCStatistics &McModel<RNG>::getStatistics() const {
    return sampleAccumulator_;
}


#endif //FINANCE_MCMODEL_H
