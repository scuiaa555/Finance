//
// Created by CUI Shidong on 17/7/2016.
//

#ifndef FINANCE_MCSIMULATION_H
#define FINANCE_MCSIMULATION_H

#include "McFramework/McModel.h"

/**
 * Base class for all Monte Carlo pricing engines.
 * Any Monte Carlo pricing engine will be privately inherited(implement in terms of) from this class.\n
 * It will provide the mcModel class(its data member) with a specific path generator and a path pricer and control the calculation
 * procedure of mcModel.
 * @tparam RNG Generic random number generator(e.g. SingleRandom<Normal<>>, MultiRandom<Normal<>,Poisson>,...)
 */
template<typename RNG>
class McSimulation {
public:

    /**
     * Create its data member mcModel(shared_ptr) with corresponding path generator and path pricer and control the calculation
     * procedure.
     * \e Constness: data member mcModel will change, so it cannot be const member function.
     * @param maxSamples Maximum number of samples.
     * @param minSamples Number of samples for each valuation.
     */
    void calculate(unsigned long maxSamples, unsigned long minSamples);

protected:

    /**
     * Get all the statistics back from mcModel.
     * \e Accessibility: Protected, since other class except derived classes should not be able to get the statistics.\n
     * \e Constness: Return type is a const, since users should not modify this result.
     * @return All the statistics(mean, variance,...) after calculations.
     */
    const MCStatistics &sampleAccumulator() const;

private:

    std::shared_ptr<McModel<RNG>> mcModel_;  /**< Shared_ptr of McModel which contains the needed path generator and pricer. */
    bool isAntithetic_;                      /**< =1 indicates use of antithetic path; =0 makes no use of antithetic path. */
//    shared_ptr<StochasticProcess> process_;

    /**
     * Defer the implementation of pathGenerator to the derived class.
     * @return shared_ptr of path generator.
     */
    virtual std::shared_ptr<PathGenerator<RNG> > pathGenerator() = 0;

    /**
     * Defer the implementation of pathPricer to the derived class.
     * @return shared_ptr of path pricer.
     */
    virtual std::shared_ptr<PathPricer> pathPricer() = 0;

    /**
     * Defer the implementation of setting time grid to the derived class.
     * Time grid is a vector which is saved in the Path class.\n
     * \e Constness: Return by value, since it is a local variable.
     * @return Vector of time grid.
     */
    virtual const vector<Time> timeGrid() const = 0;

    /**
     * Call the McModel to do the valuation.
     * @param maxSamples Maximum number of samples.
     * @param minSamples Number of samples for each valuation.
     */
    void value(unsigned long maxSamples, unsigned long minSamples);
};

template<typename RNG>
void McSimulation<RNG>::calculate(unsigned long maxSamples, unsigned long minSamples) {
    mcModel_ = std::shared_ptr<McModel<RNG>>(new McModel<RNG>(pathGenerator(), pathPricer()));
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
