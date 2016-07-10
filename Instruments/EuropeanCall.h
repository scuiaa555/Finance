//
// Created by CUI Shidong on 10/7/2016.
//

#ifndef FINANCE_EUROPEANCALL_H
#define FINANCE_EUROPEANCALL_H

#include "Instrument.h"



class EuropeanCall: public Instrument {
public:
    EuropeanCall() { }

    EuropeanCall(Time maturity, std::shared_ptr<Payoff> payoff);

    EuropeanCall(Time maturity, Quote strike);

    void SetupArguments(PricingEngine::Arguments *arg) const override;

    Money FetchResults(PricingEngine::Results *const res) override;

    //Time GetMaturity() const override;

    //void GetArguments() override;

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

    std::shared_ptr<Results> results_;
private:
    std::shared_ptr<Payoff> payoff_;
    Time maturity_;

};

class EuropeanCall::engine : public GenericEngine<EuropeanCall::Arguments, EuropeanCall::Results> {
};



#endif //FINANCE_EUROPEANCALL_H
