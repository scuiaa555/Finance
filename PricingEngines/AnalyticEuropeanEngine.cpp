//
// Created by CUI Shidong on 4/7/2016.
//

#include "PricingEngines/AnalyticEuropeanEngine.h"
#include <iostream>
#include <boost/math/distributions/normal.hpp>
//#include <cmath>


void AnalyticEuropeanEngine::calculate() {
    EuropeanOption::Arguments *arguments;
    arguments = dynamic_cast<EuropeanOption::Arguments *>(this->getArguments());
    Quote spot = model_->getSpot();
    std::shared_ptr<VanillaPayoff> payoff = std::dynamic_pointer_cast<VanillaPayoff>(arguments->payoff_);
    Quote strike = payoff->getStrike();
    double type = payoff->getType();
    Rate r = model_->getRiskFree();
    Rate q = model_->getDividend();
    Rate sigma = model_->getVolatility();
    Time maturity = arguments->maturity_;
    boost::math::normal_distribution<> nd(0.0, 1.0);
    double d1 = (log(spot / strike) + (r - q + 0.5 * sigma * sigma) * maturity) / sigma / sqrt(maturity);
    double d2 = d1 - sigma * sqrt(maturity);
    double price = type * spot * exp(-q * maturity) * boost::math::cdf(nd, type * d1) -
                   type * strike * boost::math::cdf(nd, type * d2) * exp(-r * maturity);  //Black-Sholes formula
//    std::cout << arguments->payoff_->getPayoff(100.0) << std::endl;
    std::cout << "Succeed: Analytic European engine for European option" << std::endl;
    std::cout << "European option price is " << price << "." << std::endl;

    /* !!! improvement needed here: delta? */
    EuropeanOption::Results *results;
    results = dynamic_cast<EuropeanOption::Results *> (this->getResults());
    results->price_ = price;
    results->delta_ = 1.0;

}

//void AnalyticEuropeanEngine::validate() {
//    EuropeanCall::Arguments *arg;
//    this->getArguments()->;
//
//    //std::cout << ptr->a_;
//    //std::cout << this->getArguments()->a_;
//}

AnalyticEuropeanEngine::AnalyticEuropeanEngine(std::shared_ptr<BSModel> model) : model_(model) {
}



