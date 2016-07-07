//
// Created by CUI Shidong on 4/7/2016.
//

#include "AnalyticEuropeanEngine.h"
#include <iostream>


void AnalyticEuropeanEngine::calculate() {
    EuropeanCall::Arguments *arguments;
    arguments = dynamic_cast<EuropeanCall::Arguments *>(this->GetArguments());
    Quote spot = model_->GetSpot();
    std::shared_ptr<VanillaCallPayoff> payoff = std::dynamic_pointer_cast<VanillaCallPayoff>(arguments->payoff_);
    Quote strike = payoff->GetStrike();
    Rate r = model_->GetRiskFree();
    Rate q = model_->GetDividend();
    Time maturity = arguments->maturity_;

//    std::cout << arguments->payoff_->GetPayoff(100.0) << std::endl;

    std::cout << "Analytic European engine for European option pricing succeeds" << std::endl;

}

/*void AnalyticEuropeanEngine::validate() {
    EuropeanCall::Arguments *arg;
    this->GetArguments()->;

    //std::cout << ptr->a_;
    //std::cout << this->GetArguments()->a_;
}*/

AnalyticEuropeanEngine::AnalyticEuropeanEngine(std::shared_ptr<BSModel> model) : model_(model) {
}



