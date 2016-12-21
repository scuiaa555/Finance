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

template<typename RNG, typename PathType>
class McModel {
public:
    McModel(const std::shared_ptr<PathGenerator<RNG, PathType>> &pathGenerator,
            const std::shared_ptr<PathPricer<PathType>> pathPricer);

    void addSamples(unsigned long numSamples);

    const MCStatistics &getStatistics() const;

private:
    std::shared_ptr<PathGenerator<RNG, PathType>> pathGenerator_;
    std::shared_ptr<PathPricer<PathType>> pathPricer_;
    MCStatistics sampleAccumulator_;

};

template<typename RNG, typename PathType>
McModel<RNG, PathType>::McModel(
        const std::shared_ptr<PathGenerator<RNG, PathType>> &pathGenerator,
        const std::shared_ptr<PathPricer<PathType>> pathPricer): pathGenerator_(pathGenerator), pathPricer_(pathPricer),
                                                                 sampleAccumulator_() {
}

template<typename RNG, typename PathType>
void McModel<RNG, PathType>::addSamples(unsigned long numSamples) {
    double price = 0.0;
    for (unsigned long j = 1; j <= numSamples; j++) {
        price += (*pathPricer_)(pathGenerator_->next());
    }
    price /= numSamples;
    sampleAccumulator_.add(numSamples, price);
}

template<typename RNG, typename PathType>
const MCStatistics &McModel<RNG, PathType>::getStatistics() const {
    return sampleAccumulator_;
}


#endif //FINANCE_MCMODEL_H
