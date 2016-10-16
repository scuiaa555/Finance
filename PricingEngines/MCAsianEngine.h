//
// Created by CUI Shidong on 23/7/2016.
//

#ifndef FINANCE_MCASIANENGINE_H
#define FINANCE_MCASIANENGINE_H

#include "McFramework/McSimulation.h"
#include "AsianPathPricer.h"
#include <iostream>

template<typename UnifRng= UniformLEcuyerRNG1>
class McAsianEngine : public AsianOption::engine, private McSimulation {
public:
    McAsianEngine(const shared_ptr<StochasticProcess> process, Time timeStep, unsigned long maxSamples,
                  unsigned long minSamples, bool isAntithetic = 0);

    shared_ptr<PathGenerator<NormalMarsagliaBrayRng<UnifRng>>> pathGenerator() override;

    shared_ptr<PathPricer> pathPricer() override;

    vector<Time> timeGrid() override;

    void calculate() override;

private:
    shared_ptr<StochasticProcess> process_;
    unsigned long minSamples_;
    unsigned long maxSamples_;
    Time timeStep_;
    bool isAntithetic_;
};

template<typename UnifRng>
McAsianEngine<UnifRng>::McAsianEngine(const shared_ptr<StochasticProcess> process, Time timeStep,
                                      unsigned long maxSamples, unsigned long minSamples, bool isAntithetic) :
        process_(process),
        timeStep_(timeStep),
        maxSamples_(maxSamples),
        minSamples_(minSamples),
        isAntithetic_(isAntithetic) { }

template<typename UnifRng>
shared_ptr<PathGenerator<NormalMarsagliaBrayRng<UnifRng>>> McAsianEngine<UnifRng>::pathGenerator() {
    return shared_ptr<PathGenerator<NormalMarsagliaBrayRng<UnifRng>>>(
            new PathGenerator<NormalMarsagliaBrayRng<UnifRng>>(process_, timeGrid(), isAntithetic_));
}

template<typename UnifRng>
shared_ptr<PathPricer> McAsianEngine<UnifRng>::pathPricer() {
    AsianOption::Arguments *arguments;
    arguments = dynamic_cast<AsianOption::Arguments *>(this->getArguments());
    std::shared_ptr<VanillaPayoff> payoff = std::dynamic_pointer_cast<VanillaPayoff>(arguments->payoff_);
    /* !!!problem here */
    Rate r = std::dynamic_pointer_cast<BSModel>(process_->GetModel())->getRiskFree();
    std::shared_ptr<vector<Time> > monitorTimesPtr(new vector<Time>(arguments->monitoredTimes_));
    AsianOption::AverageType averageType = arguments->averageType_;
    /* !!!problem here */
    return shared_ptr<AsianPathPricer>(new AsianPathPricer(payoff, r, monitorTimesPtr, averageType, isAntithetic_));
}

template<typename UnifRng>
vector<Time> McAsianEngine<UnifRng>::timeGrid() {
    vector<Time> timeGrid;
    AsianOption::Arguments *arguments;
    arguments = dynamic_cast<AsianOption::Arguments *>(this->getArguments());
    Time maturity = arguments->maturity_;
    /* !!!error prone here */
    int numberStep = maturity / timeStep_;
    for (int j = 0; j <= numberStep; j++) {
        timeGrid.push_back(timeStep_ * j);
    }
    return timeGrid;
}

template<typename UnifRng>
void McAsianEngine<UnifRng>::calculate() {
    McSimulation::calculate(maxSamples_, minSamples_);
    AsianOption::Results *results;
    results = dynamic_cast<AsianOption::Results *> (this->getResults());
    double price = sampleAccumulator().mean();
    results->price_ = sampleAccumulator().mean();
    std::cout << "Succeed: Monte Carlo simulation engine for European Asian option" << std::endl;
    std::cout << "European Asian option price is " << price << "." << std::endl;
}


#endif //FINANCE_MCASIANENGINE_H
