//
// Created by CUI Shidong on 10/7/2016.
//

#ifndef FINANCE_FORWARD_H
#define FINANCE_FORWARD_H

#include "Instrument.h"

/**
 * Forward contract class.
 * This Forward contract class is used for pricing forward contract.
 */
class Forward: public Instrument {
public:

    /**
     * Constructor.
     * @param maturity Maturity of forward contract.
     * @param strike Strike of forward contract.
     * @param spot Spot price of underlying.
     */
    Forward(Time maturity, Quote strike, Quote spot);

    //Time GetMaturity() const override;

    //void getArguments() override;

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

    void setupArguments(PricingEngine::Arguments *const arg) const override;

    Money fetchResults(PricingEngine::Results *const res) override;

};

class Forward::engine : public GenericEngine<Forward::Arguments, Forward::Results> {
};



#endif //FINANCE_FORWARD_H
