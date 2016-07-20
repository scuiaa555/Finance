//
// Created by CUI Shidong on 10/7/2016.
//

#include "EuropeanCall.h"
#include <memory>
#include <iostream>

using std::shared_ptr;

EuropeanCall::EuropeanCall(Time maturity, Quote strike) : maturity_(maturity) {
    payoff_ = shared_ptr<Payoff>(new VanillaCallPayoff(strike));
}

EuropeanCall::EuropeanCall(Time maturity, std::shared_ptr<Payoff> payoff) :
        maturity_(maturity), payoff_(payoff) { }

void EuropeanCall::SetupArguments(PricingEngine::Arguments *arg) const {
    EuropeanCall::Arguments *arguments;
    arguments = dynamic_cast<EuropeanCall::Arguments *>(arg);
    arguments->payoff_ = payoff_;
    arguments->maturity_ = maturity_;
}

Money EuropeanCall::FetchResults(PricingEngine::Results *const res) {
    EuropeanCall::Results *result = dynamic_cast<EuropeanCall::Results *>(res);
    //fully create another copy of the results from the pricing engine
    results_ = std::make_shared<EuropeanCall::Results>(*result);
    std::cout << results_->price_ << std::endl;
    return results_->price_;
}
