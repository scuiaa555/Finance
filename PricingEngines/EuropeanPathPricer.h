//
// Created by CUI Shidong on 23/7/2016.
//

#ifndef FINANCE_EUROPEANPATHPRICER_H
#define FINANCE_EUROPEANPATHPRICER_H

#include "McFramework/PathPricer.h"
#include "Payoff.h"

class EuropeanPathPricer : public PathPricer {
public:
    EuropeanPathPricer(const std::shared_ptr<Payoff> &payoff, Rate discount);

    Money operator()(const Path &path) const override;

private:
    std::shared_ptr<Payoff> payoff_;
    Rate discount_;
};

#endif //FINANCE_EUROPEANPATHPRICER_H
