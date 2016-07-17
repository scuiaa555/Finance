//
// Created by CUI Shidong on 17/7/2016.
//

#include "PathPricer.h"

EuropeanPathPricer::EuropeanPathPricer(const std::shared_ptr<Payoff> &payoff, Rate discount) : payoff_(payoff),
                                                                                               discount_(discount) { }

Money EuropeanPathPricer::operator()(const Path &path) const {
    Money price;
//    price=path.values_.back();
    price = payoff_->GetPayoff(path.values_.back()) * discount_;
    return price;
}
