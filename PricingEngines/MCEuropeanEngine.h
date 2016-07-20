//
// Created by CUI Shidong on 17/7/2016.
//

#ifndef FINANCE_MCEUROPEANENGINE_H
#define FINANCE_MCEUROPEANENGINE_H

#include "Instruments/EuropeanCall.h"
#include "McFramework/McSimulation.h"

template<typename UnifRng= UniformLEcuyerRNG1>
class MCEuropeanEngine : public EuropeanCall::engine, private McSimulation {
public:
    MCEuropeanEngine(const shared_ptr<StochasticProcess> process, Time timeStep, unsigned long maxSamples,
                     unsigned long minSamples);

    shared_ptr<PathGenerator<NormalMarsagliaBrayRng<UnifRng>>> pathGenerator() override;

    shared_ptr<PathPricer> pathPricer() override;

    vector<Time> timeGrid() override;

    void calculate() override;

private:
    shared_ptr<StochasticProcess> process_;
    unsigned long minSamples_;
    unsigned long maxSamples_;
    Time timeStep_;
};

template<typename UnifRng>
MCEuropeanEngine<UnifRng>::MCEuropeanEngine(const shared_ptr<StochasticProcess> process, Time timeStep,
                                            unsigned long maxSamples, unsigned long minSamples) :
        process_(process), timeStep_(timeStep), maxSamples_(maxSamples), minSamples_(minSamples) { }

template<typename UnifRng>
shared_ptr<PathGenerator<NormalMarsagliaBrayRng<UnifRng>>> MCEuropeanEngine<UnifRng>::pathGenerator() {
    return shared_ptr<PathGenerator<NormalMarsagliaBrayRng<UnifRng>>>(
            new PathGenerator<NormalMarsagliaBrayRng<UnifRng>>(process_, timeGrid()));
}

template<typename UnifRng>
shared_ptr<PathPricer> MCEuropeanEngine<UnifRng>::pathPricer() {
    EuropeanCall::Arguments *arguments;
    arguments = dynamic_cast<EuropeanCall::Arguments *>(this->GetArguments());
    std::shared_ptr<VanillaCallPayoff> payoff = std::dynamic_pointer_cast<VanillaCallPayoff>(arguments->payoff_);
    /* problem here */
    Rate r = std::dynamic_pointer_cast<BSModel>(process_->GetModel())->GetRiskFree();
    /* problem here */
    return shared_ptr<EuropeanPathPricer>(new EuropeanPathPricer(payoff, r));
}

template<typename UnifRng>
void MCEuropeanEngine<UnifRng>::calculate() {
    McSimulation::calculate(maxSamples_, minSamples_);
    EuropeanCall::Results *results;
    results = dynamic_cast<EuropeanCall::Results *> (this->GetResults());
    double price = sampleAccumulator().mean();
    results->price_ = sampleAccumulator().mean();
    results->delta_ = 1.0;
}

template<typename UnifRng>
vector<Time> MCEuropeanEngine<UnifRng>::timeGrid() {
    vector<Time> timeGrid;
    EuropeanCall::Arguments *arguments;
    arguments = dynamic_cast<EuropeanCall::Arguments *>(this->GetArguments());
    Time maturity = arguments->maturity_;
    /* error prone here */
    int numberStep = maturity / timeStep_;
    for (int j = 0; j <= numberStep; j++) {
        timeGrid.push_back(timeStep_ * j);
    }
    return timeGrid;
}


#endif //FINANCE_MCEUROPEANENGINE_H
