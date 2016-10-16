//
// Created by CUI Shidong on 10/7/2016.
//

#ifndef FINANCE_EUROPEANCALL_H
#define FINANCE_EUROPEANCALL_H

#include "Instrument.h"
#include "Payoffs/VanillaPayoff.h"

class EuropeanOption: public Instrument {
public:

    EuropeanOption(Time maturity, std::shared_ptr<Payoff> payoff);

    void setupArguments(PricingEngine::Arguments *arg) const override;

    Money fetchResults(PricingEngine::Results *const res) override;

    class Arguments : public PricingEngine::Arguments {
    public:
        std::shared_ptr<Payoff> payoff_;
        Time maturity_;
    };

    class Results : public PricingEngine::Results {
    public:
        Money price_;
        double delta_;
    };

    class engine;

private:
    std::shared_ptr<Payoff> payoff_;
    Time maturity_;
    /* reason that here uses 'shared_ptr' refers to comments in EuropeanOption.cpp */
    std::shared_ptr<Results> results_;
};

class EuropeanOption::engine : public GenericEngine<EuropeanOption::Arguments, EuropeanOption::Results> {
};



#endif //FINANCE_EUROPEANCALL_H
