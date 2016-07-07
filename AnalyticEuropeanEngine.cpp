//
// Created by CUI Shidong on 4/7/2016.
//

#include "AnalyticEuropeanEngine.h"
#include <iostream>


void AnalyticEuropeanEngine::calculate() {
    std::cout << "Pricing succeeds" << std::endl;

}

/*void AnalyticEuropeanEngine::validate() {
    EuropeanCall::Arguments *arg;
    this->GetArguments()->;

    //std::cout << ptr->a_;
    //std::cout << this->GetArguments()->a_;
}*/

AnalyticEuropeanEngine::AnalyticEuropeanEngine(std::shared_ptr<BSModel> model) : model_(model) {
}



