//
// Created by CUI Shidong on 10/7/2016.
//

#include "AnalyticForwardEngine.h"
#include <iostream>
#include <cmath>

AnalyticForwardEngine::AnalyticForwardEngine(Rate r) : r_(r) {
}

void AnalyticForwardEngine::calculate() {
    Forward::Arguments *arguments;
    arguments = dynamic_cast<Forward::Arguments *>(this->GetArguments());
    Quote strike = arguments->strike_;
    Time maturity = arguments->maturity_;
    Rate r = r_;
    Quote spot = arguments->spot_;
    Money price = spot - strike * exp(-r * maturity);
    std::cout << "Forward price is " << price << "." << std::endl;
//    std::cout << arguments->payoff_->GetPayoff(100.0) << std::endl;
    std::cout << "Analytic Forward engine for Forward pricing succeeds" << std::endl;

    Forward::Results *results;
    results = dynamic_cast<Forward::Results *> (this->GetResults());
    results->price_ = price;
    //results->delta_ = 1.0;*/

}