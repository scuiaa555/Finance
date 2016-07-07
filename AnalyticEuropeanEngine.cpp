//
// Created by CUI Shidong on 4/7/2016.
//

#include "AnalyticEuropeanEngine.h"
#include <iostream>


void AnalyticEuropeanEngine::calculate() {
    EuropeanCall::Arguments *arguments;
    arguments = dynamic_cast<EuropeanCall::Arguments *>(this->GetArguments());
    std::cout << arguments->payoff_->GetPayoff(100.0) << std::endl;

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



