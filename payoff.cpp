//
// Created by CUI Shidong on 26/6/2016.
//

#include "Payoff.h"

VanillaCallPayoff::VanillaCallPayoff(Quote strike) : strike_(strike) { }

Money VanillaCallPayoff::GetPayoff(Quote Spot) const {
    return Spot - strike_ > 0 ? Spot - strike_: 0;
}

Quote VanillaCallPayoff::GetStrike() const {
    return strike_;
}