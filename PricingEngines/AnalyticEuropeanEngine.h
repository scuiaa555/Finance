//
// Created by CUI Shidong on 4/7/2016.
//

#ifndef FINANCE_ANALYTICEUROPEANENGINE_H
#define FINANCE_ANALYTICEUROPEANENGINE_H

#include "Instruments/EuropeanOption.h"
#include "StochasticProcess.h"
#include "StochasticProcesses/BSStochasticProcess.h"

class AnalyticEuropeanEngine : public EuropeanOption::engine {
public:
    AnalyticEuropeanEngine(std::shared_ptr<BSStochasticProcess> process);

//    double test(double a) { return a; }

    void calculate() override;

//    void validate() override;

//    class AnalyticBSResults : public virtual PricingEngine::Results {
//    public:
//        double delta;
//    };
//
//    class AnalyticBSArguments : public virtual PricingEngine::Arguments {
//    public:
//        std::shared_ptr<Payoff> payoff_;
//    };

private:
    std::shared_ptr<BSStochasticProcess> process_;
    //std::shared_ptr<AnalyticBSEngine::AnalyticBSResults> results_;
    //std::shared_ptr<AnalyticBSEngine::Arguments> arguments_;
};


#endif //FINANCE_ANALYTICEUROPEANENGINE_H
