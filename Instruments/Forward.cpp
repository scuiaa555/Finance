//
// Created by CUI Shidong on 10/7/2016.
//

#include "Forward.h"
#include <iostream>

Forward::Forward(Time maturity, Quote strike, Quote spot) : maturity_(maturity), strike_(strike), spot_(spot) {
}

void Forward::SetupArguments(PricingEngine::Arguments *arg) const {
    Forward::Arguments *arguments;
    arguments = dynamic_cast<Forward::Arguments *>(arg);
    arguments->strike_ = strike_;
    arguments->maturity_ = maturity_;
    arguments->spot_ = spot_;
}

Money Forward::FetchResults(PricingEngine::Results *const res) {
    Forward::Results *result = dynamic_cast<Forward::Results *>(res);
    //fully create another copy of the results from the pricing engine
    results_ = std::make_shared<Forward::Results>(*result);
    std::cout << results_->price_ << std::endl;
    return results_->price_;
}

