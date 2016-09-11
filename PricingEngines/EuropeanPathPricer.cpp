//
// Created by CUI Shidong on 17/7/2016.
//

#include "PricingEngines/EuropeanPathPricer.h"
#include <cmath>

EuropeanPathPricer::EuropeanPathPricer(const std::shared_ptr<Payoff> &payoff, Rate discount) : payoff_(payoff),
                                                                                               discount_(discount) { }

Money EuropeanPathPricer::operator()(const Path &path) const {
    Money price;
//    price=path.values_.back();
    Rate discountFactor = exp(-discount_ * path.timeGrid_.back());
    price = payoff_->getPayoff(path.values_.back()) * discountFactor;
    return price;
}
