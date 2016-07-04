//
// Created by CUI Shidong on 26/6/2016.
//

#include "Option.h"
//#include "PricingEngine.h"
//#include "Payoff.h"

using std::shared_ptr;

void Option::SetPricingEngine(std::shared_ptr<PricingEngine> pricingEngine) {
    pricingEngine_ = pricingEngine;
}

Money Option::npv() {
    //give option exercise to pricing engine
    //pricingEngine_->GetArguments(arguments);
    //SetupArguments(pricingEngine_->arguments_);
    SetupArguments(pricingEngine_->GetArguments());

    //let pricing engine to the calculations
    pricingEngine_->calculate();

    //fetch the results back
}

EuropeanCall::EuropeanCall(Time Maturity, Quote Strike) : Maturity_(Maturity) {
    payoff_ = shared_ptr<Payoff>(new VanillaCallPayoff(Strike));
}

EuropeanCall::EuropeanCall(Time Maturity, std::shared_ptr<Payoff> payoff) :
        Maturity_(Maturity), payoff_(payoff) { }

void EuropeanCall::SetupArguments(std::shared_ptr<PricingEngine::Arguments> arg) {
    std::shared_ptr<EuropeanCall::Arguments> arguments;
    arguments = std::dynamic_pointer_cast<EuropeanCall::Arguments>(arg);
    arguments->payoff_ = payoff_;

}





/*
 * Time EuropeanCall::GetMaturity() const {
    return Maturity_;
}*/

/*void Option::Calculate() {
    pricingEngine_->calculate();
}*/

/*
Money Option::npv() {
    GetArguments();
    Calculate();
    //FetchResults();
}*/

//class Option::Arguments : public PricingEngine::Arguments {
//public:
//    double a;
//};

/*class EuropeanCall::EuropeanCallArguments : public Option::Arguments {
public:
    EuropeanCallArguments(std::string type, std::shared_ptr<Payoff> payoff);

    std::string type_;
    std::shared_ptr<Payoff> payoff_;
};*/

/*

EuropeanCall::EuropeanCallArguments::EuropeanCallArguments(std::string type, std::shared_ptr<Payoff> payoff) :
        type_(type), payoff_(payoff) { }

void EuropeanCall::GetArguments() {
    pricingEngine_->GetArguments(shared_ptr<EuropeanCallArguments>(new EuropeanCallArguments("Call", payoff_)));
}*/
