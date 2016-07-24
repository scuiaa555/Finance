//
// Created by CUI Shidong on 23/7/2016.
//

#ifndef FINANCE_ASIANOPTION_H
#define FINANCE_ASIANOPTION_H

#include "Instrument.h"
#include "Payoffs/VanillaPayoff.h"
#include <vector>

class AsianOption : public Instrument {
public:

    enum AverageType {
        arithmetic = 0,
        geometric = 1
    };

    AsianOption(Time maturity, std::shared_ptr<Payoff> payoff, std::vector<Time> &monitoredTimes,
                AverageType averageType,
                bool isDiscretelyMonitored = 1);

    AsianOption(Time maturity, std::shared_ptr<Payoff> payoff, Time timeStep, AverageType averageType,
                bool isDiscretelyMonitored = 1);

    AsianOption(Time maturity, std::shared_ptr<Payoff> payoff, AverageType averageType,
                bool isContinuouslyMonitored = 1);

    void setupArguments(PricingEngine::Arguments *arg) const override;

    Money fetchResults(PricingEngine::Results *const res) override;

    class Arguments : public PricingEngine::Arguments {
    public:
        std::shared_ptr<Payoff> payoff_;
        std::vector<Time> monitoredTimes_;
        Time maturity_;
        AverageType averageType_;
    };

    class Results : public PricingEngine::Results {
    public:
        Money price_;
//        double delta_;
    };

    class engine;

private:
    Time maturity_;
    std::shared_ptr<Payoff> payoff_;
    std::vector<Time> monitoredTimes_;
    std::shared_ptr<Results> results_;
    AverageType averageType_;
};


class AsianOption::engine : public GenericEngine<AsianOption::Arguments, AsianOption::Results> {
};


#endif //FINANCE_ASIANOPTION_H
