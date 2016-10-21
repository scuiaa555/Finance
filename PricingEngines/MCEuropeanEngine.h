//
// Created by CUI Shidong on 17/7/2016.
//

#ifndef FINANCE_MCEUROPEANENGINE_H
#define FINANCE_MCEUROPEANENGINE_H

#include "Instruments/EuropeanOption.h"
#include "McFramework/McSimulation.h"
#include "EuropeanPathPricer.h"
#include <iostream>

template<typename UnifRng= UniformLEcuyerRNG1>
class McEuropeanEngine : public EuropeanOption::engine, private McSimulation {
public:
    McEuropeanEngine(const std::shared_ptr<Model> model, Time timeStep, unsigned long maxSamples,
                     unsigned long minSamples);

    std::shared_ptr<PathGenerator<NormalMarsagliaBrayRng<UnifRng>>> pathGenerator() override;

    std::shared_ptr<PathPricer> pathPricer() override;

    vector<Time> timeGrid() override;

    void calculate() override;

private:
    std::shared_ptr<Model> model_;
    unsigned long minSamples_;
    unsigned long maxSamples_;
    Time timeStep_;
};

template<typename UnifRng>
McEuropeanEngine<UnifRng>::McEuropeanEngine(const std::shared_ptr<Model> model, Time timeStep,
                                            unsigned long maxSamples, unsigned long minSamples) :
        model_(model), timeStep_(timeStep), maxSamples_(maxSamples), minSamples_(minSamples) { }

template<typename UnifRng>
std::shared_ptr<PathGenerator<NormalMarsagliaBrayRng<UnifRng>>> McEuropeanEngine<UnifRng>::pathGenerator() {
    return std::shared_ptr<PathGenerator<NormalMarsagliaBrayRng<UnifRng>>>(
            new PathGenerator<NormalMarsagliaBrayRng<UnifRng>>(model_, timeGrid()));
}

template<typename UnifRng>
std::shared_ptr<PathPricer> McEuropeanEngine<UnifRng>::pathPricer() {
    EuropeanOption::Arguments *arguments;
    arguments = dynamic_cast<EuropeanOption::Arguments *>(this->getArguments());
    std::shared_ptr<VanillaPayoff> payoff = std::dynamic_pointer_cast<VanillaPayoff>(arguments->payoff_);
    /* problem here */
    Rate r = std::dynamic_pointer_cast<BSStochasticProcess>(model_->getProcess())->getRiskFree();
    /* problem here */
    return std::shared_ptr<EuropeanPathPricer>(new EuropeanPathPricer(payoff, r));
}

template<typename UnifRng>
vector<Time> McEuropeanEngine<UnifRng>::timeGrid() {
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

template<typename UnifRng>
void McEuropeanEngine<UnifRng>::calculate() {
    McSimulation::calculate(maxSamples_, minSamples_);
    EuropeanOption::Results *results;
    results = dynamic_cast<EuropeanOption::Results *> (this->getResults());
    double price = sampleAccumulator().mean();
    results->price_ = sampleAccumulator().mean();
    std::cout << "Succeed: Monte Carlo simulation engine for European option" << std::endl;
    std::cout << "European option price is " << price << "." << std::endl;
    results->delta_ = 1.0;
}

#endif //FINANCE_MCEUROPEANENGINE_H
