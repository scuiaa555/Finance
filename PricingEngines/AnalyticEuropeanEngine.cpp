//
// Created by CUI Shidong on 4/7/2016.
//

#include "PricingEngines/AnalyticEuropeanEngine.h"
#include <iostream>
#include <boost/math/distributions/normal.hpp>
//#include <cmath>


void AnalyticEuropeanEngine::calculate() {
    EuropeanCall::Arguments *arguments;
    arguments = dynamic_cast<EuropeanCall::Arguments *>(this->GetArguments());
    Quote spot = model_->GetSpot();
    std::shared_ptr<VanillaCallPayoff> payoff = std::dynamic_pointer_cast<VanillaCallPayoff>(arguments->payoff_);
    Quote strike = payoff->GetStrike();
    Rate r = model_->GetRiskFree();
    Rate q = model_->GetDividend();
    Rate sigma = model_->GetVolatility();
    Time maturity = arguments->maturity_;
    boost::math::normal_distribution<> nd(0.0, 1.0);
    double d1 = (log(spot / strike) + (r - q + 0.5 * sigma * sigma) * maturity) / sigma / sqrt(maturity);
    double d2 = d1 - sigma * sqrt(maturity);
    double price = spot * exp(-q * maturity) * boost::math::cdf(nd, d1) -
                   strike * boost::math::cdf(nd, d2) * exp(-r * maturity);  //Black-Sholes formula
    std::cout << "European option price is " << price << "." << std::endl;
//    std::cout << arguments->payoff_->GetPayoff(100.0) << std::endl;
    std::cout << "Analytic European engine for European option pricing succeeds" << std::endl;

    /* need improvement */
    EuropeanCall::Results *results;
    results = dynamic_cast<EuropeanCall::Results *> (this->GetResults());
    results->price_ = price;
    results->delta_ = 1.0;

}

//void AnalyticEuropeanEngine::validate() {
//    EuropeanCall::Arguments *arg;
//    this->GetArguments()->;
//
//    //std::cout << ptr->a_;
//    //std::cout << this->GetArguments()->a_;
//}

AnalyticEuropeanEngine::AnalyticEuropeanEngine(std::shared_ptr<BSModel> model) : model_(model) {
}



