//
// Created by CUI Shidong on 26/6/2016.
//

#include "Option.h"
#include <iostream>
//#include "PricingEngine.h"
//#include "Payoff.h"

using std::shared_ptr;

/*EuropeanCall::Arguments::Arguments(double a) : a_(a) {
    payoff_ = nullptr;
}*/

void Option::SetPricingEngine(std::shared_ptr<PricingEngine> pricingEngine) {
    pricingEngine_ = pricingEngine;
}

Money Option::npv() {
    //give option exercise to pricing engine
    //pricingEngine_->GetArguments(arguments);
    //SetupArguments(pricingEngine_->arguments_);
//    pricingEngine_->validate();
    SetupArguments(pricingEngine_->GetArguments());

    //let pricing engine to the calculations
    pricingEngine_->calculate();

    //fetch the results back to the option
    return FetchResults(pricingEngine_->GetResults());

}

EuropeanCall::EuropeanCall(Time maturity, Quote strike) : maturity_(maturity) {
    payoff_ = shared_ptr<Payoff>(new VanillaCallPayoff(strike));
}

EuropeanCall::EuropeanCall(Time maturity, std::shared_ptr<Payoff> payoff) :
        maturity_(maturity), payoff_(payoff) { }

void EuropeanCall::SetupArguments(PricingEngine::Arguments *arg) {
    EuropeanCall::Arguments *arguments;
    arguments = dynamic_cast<EuropeanCall::Arguments *>(arg);
    arguments->payoff_ = payoff_;
    arguments->maturity_ = maturity_;
}

Money EuropeanCall::FetchResults(PricingEngine::Results *res) {
    EuropeanCall::Results *result = dynamic_cast<EuropeanCall::Results *>(res);
    results_ = std::make_shared<EuropeanCall::Results>(*result);
    std::cout << results_->price_ << std::endl;
    return results_->price_;
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
