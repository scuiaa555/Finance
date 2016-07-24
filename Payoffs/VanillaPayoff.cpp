//
// Created by CUI Shidong on 21/7/2016.
//

#include "Payoffs/VanillaPayoff.h"

VanillaPayoff::VanillaPayoff(Quote strike, std::string type) : strike_(strike) {
    std::transform(type.begin(), type.end(), type.begin(), ::tolower);
    if (type == "call") type_ = 1.0; else {
        if (type == "put") type_ = -1.0; else throw ("VanillaPayoff has no such payoff type");
    }
}

Money VanillaPayoff::getPayoff(Quote Spot) const {
    return (Spot - strike_) * type_ > 0 ? (Spot - strike_) * type_ : 0;
}

Quote VanillaPayoff::getStrike() const {
    return strike_;
}

double VanillaPayoff::getType() const {
    return type_;
}

