//
// Created by CUI Shidong on 10/7/2016.
//

#ifndef FINANCE_FORWARD_H
#define FINANCE_FORWARD_H

#include "Instrument.h"


class Forward: public Instrument {
public:
    Forward() { }

    Forward(Time maturity, Quote strike, Quote spot);

    void SetupArguments(PricingEngine::Arguments *arg) const override;

    Money FetchResults(PricingEngine::Results *const res) override;

    //Time GetMaturity() const override;

    //void GetArguments() override;

    class Arguments : public PricingEngine::Arguments {
    public:
        Quote strike_;
        Time maturity_;
        Quote spot_;
    };

    class Results : public PricingEngine::Results {
    public:
        Money price_;
        //double delta_;
    };

    class engine;

    std::shared_ptr<Results> results_;
private:
    Quote strike_;
    Quote spot_;
    Time maturity_;

};

class Forward::engine : public GenericEngine<Forward::Arguments, Forward::Results> {
};



#endif //FINANCE_FORWARD_H
