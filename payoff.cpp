//
// Created by CUI Shidong on 26/6/2016.
//

#include "payoff.h"

VanillaCallPayoff::VanillaCallPayoff(double Strike_) : Strike(Strike_) { }

double VanillaCallPayoff::GetPayoff(double Spot) const {
    return Spot - Strike > 0 ?: Spot - Strike, 0;
}