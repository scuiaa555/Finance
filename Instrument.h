//
// Created by CUI Shidong on 26/6/2016.
//

#ifndef FINANCE_OPTION_H
#define FINANCE_OPTION_H

#include "NameDef.h"
#include "Payoff.h"
#include "PricingEngine.h"
#include <memory>
#include <string>

//class PricingEngine;

//class PricingEngine::Arguments;

class Instrument {
public:
    Instrument() { }

    //virtual Time GetMaturity() const = 0;

    void setPricingEngine(const std::shared_ptr<PricingEngine> pricingEngine);

//    class Arguments : public PricingEngine::Arguments {
//        double b;
//    };

    Money npv();

    virtual void setupArguments(PricingEngine::Arguments *arg) const = 0;

    virtual Money fetchResults(PricingEngine::Results *const res) = 0;

    //void Calculate();

    //virtual void getArguments() = 0;

    //class Arguments : public PricingEngine::Arguments {
    //};
    //class Arguments;

protected:
    std::shared_ptr<PricingEngine> pricingEngine_;
    //std::shared_ptr<Arguments> arguments;
};

// class EuropeanCall : public Instrument {
//public:
//    EuropeanCall() { }
//
//    EuropeanCall(Time maturity, std::shared_ptr<Payoff> payoff);
//
//    EuropeanCall(Time maturity, Quote strike);
//
//    void SetupArguments(PricingEngine::Arguments *arg) const override;
//
//    Money FetchResults(PricingEngine::Results *const res) override;
//
//    //Time GetMaturity() const override;
//
//    //void getArguments() override;
//
//    class Arguments : public PricingEngine::Arguments {
//    public:
////        Arguments() { }
//
//        //Arguments(double a);
//
//        std::shared_ptr<Payoff> payoff_;
//        Time maturity_;
//
//        void print() override {
//            double b = 0;
//        }
//
////        double a_;
//
//        //~Arguments() { }
//    };
//
//    class Results : public PricingEngine::Results {
//    public:
////        Results() { }
//
//        Money price_;
//        double delta_;
//
//    };
//
//    class engine;
//
//    std::shared_ptr<Results> results_;
//private:
//    std::shared_ptr<Payoff> payoff_;
//    Time maturity_;
//
//};
//
//class EuropeanCall::engine : public GenericEngine<EuropeanCall::Arguments, EuropeanCall::Results> {
//};

#endif //FINANCE_OPTION_H
