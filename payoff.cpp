//
// Created by CUI Shidong on 26/6/2016.
//

#include "payoff.h"

VanillaCallPayoff::VanillaCallPayoff(Quote Strike) : Strike_(Strike) { }

Money VanillaCallPayoff::GetPayoff(Quote Spot) const {
    return Spot - Strike_ > 0 ? Spot - Strike_: 0;
}