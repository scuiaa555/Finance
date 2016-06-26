//
// Created by CUI Shidong on 26/6/2016.
//

#include "option.h"
#include "payoff.h"

using std::shared_ptr;

void Option::SetPricingEngine(std::shared_ptr<PricingEngine> pricingEngine) {
    pricingEngine_ = pricingEngine;
}

EuropeanCall::EuropeanCall(Time Maturity, Quote Strike) : Maturity_(Maturity) {
    payoff_ = shared_ptr<Payoff>(new VanillaCallPayoff(Strike));
}

EuropeanCall::EuropeanCall(Time Maturity, std::shared_ptr<Payoff> payoff) :
        Maturity_(Maturity), payoff_(payoff) { }

Time EuropeanCall::GetMaturity() const {
    return Maturity_;
}


