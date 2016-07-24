//
// Created by CUI Shidong on 10/7/2016.
//

#include "EuropeanOption.h"
//#include <memory>
//#include <iostream>

using std::shared_ptr;

//EuropeanCall::EuropeanCall(Time maturity, Quote strike) : maturity_(maturity) {
//    payoff_ = shared_ptr<Payoff>(new VanillaPayoff(strike,"call"));
//}

EuropeanOption::EuropeanOption(Time maturity, std::shared_ptr<Payoff> payoff) :
        maturity_(maturity), payoff_(payoff) { }

void EuropeanOption::setupArguments(PricingEngine::Arguments *arg) const {
    EuropeanOption::Arguments *arguments;
    arguments = dynamic_cast<EuropeanOption::Arguments *>(arg);
    arguments->payoff_ = payoff_;
    arguments->maturity_ = maturity_;
}

Money EuropeanOption::fetchResults(PricingEngine::Results *const res) {
    EuropeanOption::Results *result = dynamic_cast<EuropeanOption::Results *>(res);
    //fully create another copy of the results from the pricing engine
    results_ = std::make_shared<EuropeanOption::Results>(*result);
//    std::cout << results_->price_ << std::endl;
    return results_->price_;
}
