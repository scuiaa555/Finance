//
// Created by CUI Shidong on 16/7/2016.
//

#ifndef FINANCE_PATHPRICER_H
#define FINANCE_PATHPRICER_H

#include "nameDef.h"
#include "McFramework/Path.h"
//#include "Payoff.h"

class PathPricer {
public:
    virtual Money operator()(const Path &path) const = 0;

//private:
//    bool isAntithetic_;
};

//EuropeanPathPricer::EuropeanPathPricer(const std::shared_ptr<Payoff> &payoff, Rate discount) : payoff_(payoff),

//Money EuropeanPathPricer::operator()(const Path &path) const {
//    Money price;
////    price=path.values_.back();
//    price = payoff_->getPayoff(path.values_.back()) * discount_;
//    return price;
//}

#endif //FINANCE_PATHPRICER_H
