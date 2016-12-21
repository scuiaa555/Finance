//
// Created by CUI Shidong on 17/7/2016.
//

#ifndef FINANCE_MCEUROPEANENGINE_H
#define FINANCE_MCEUROPEANENGINE_H

#include "Instruments/EuropeanOption.h"
#include "McFramework/McSimulation.h"
#include "EuropeanPathPricer.h"
#include <iostream>
#include "RandNumGeneration/PseudoRandom.h"
#include "RandNumGeneration/Normal.h"

template<typename RNG, typename PathType=SingleVariate>
class McEuropeanEngine
        : public EuropeanOption::engine, private McSimulation<RNG, PathType> {
public:
    McEuropeanEngine(const std::shared_ptr<Model<double>> model, Time timeStep, unsigned long maxSamples,
                     unsigned long minSamples);

    void calculate() override;

private:
    std::shared_ptr<Model<double>> model_;
    unsigned long minSamples_;
    unsigned long maxSamples_;
    Time timeStep_;

    std::shared_ptr<PathGenerator<RNG, PathType>> pathGenerator() override;

    std::shared_ptr<PathPricer<PathType>> pathPricer() override;

    const vector<Time> timeGrid() const override;

};

template<typename RNG, typename PathType>
McEuropeanEngine<RNG, PathType>::McEuropeanEngine(const std::shared_ptr<Model<double>> model, Time timeStep,
                                                  unsigned long maxSamples, unsigned long minSamples) :
        model_(model), timeStep_(timeStep), maxSamples_(maxSamples), minSamples_(minSamples) {}

template<typename RNG, typename PathType>
std::shared_ptr<PathGenerator<RNG, PathType>> McEuropeanEngine<RNG, PathType>::pathGenerator() {
    return std::shared_ptr<PathGenerator<RNG, PathType>>(
            new PathGenerator<RNG, PathType>(model_, timeGrid()));
}

template<typename RNG, typename PathType>
std::shared_ptr<PathPricer<PathType>> McEuropeanEngine<RNG, PathType>::pathPricer() {
    EuropeanOption::Arguments *arguments;
    arguments = dynamic_cast<EuropeanOption::Arguments *>(this->getArguments());
    std::shared_ptr<VanillaPayoff> payoff = std::dynamic_pointer_cast<VanillaPayoff>(arguments->payoff_);
    /* problem here */
    Rate r = std::dynamic_pointer_cast<BSStochasticProcess>(model_->getProcess())->getRiskFree();
    /* problem here */
    return std::shared_ptr<EuropeanPathPricer>(new EuropeanPathPricer(payoff, r));
}

template<typename RNG,typename PathType>
const vector<Time> McEuropeanEngine<RNG,PathType>::timeGrid() const {
    vector<Time> timeGrid;
    EuropeanOption::Arguments *arguments;
    arguments = dynamic_cast<EuropeanOption::Arguments *>(this->getArguments());
    Time maturity = arguments->maturity_;
    /* error prone here */
    int numberStep = (int) (maturity / timeStep_);
    for (int j = 0; j <= numberStep; j++) {
        timeGrid.push_back(timeStep_ * j);
    }
    return timeGrid;
}

template<typename RNG,typename PathType>
void McEuropeanEngine<RNG,PathType>::calculate() {
    McSimulation<RNG,PathType>::calculate(maxSamples_, minSamples_);
    EuropeanOption::Results *results;
    results = dynamic_cast<EuropeanOption::Results *> (this->getResults());
    double price = this->sampleAccumulator().mean();
    results->price_ = this->sampleAccumulator().mean();
    std::cout << "Succeed: Monte Carlo simulation engine for European option" << std::endl;
    std::cout << "European option price is " << price << "." << std::endl;
    results->delta_ = 1.0;
}

#endif //FINANCE_MCEUROPEANENGINE_H
