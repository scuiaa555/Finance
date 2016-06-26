//
// Created by CUI Shidong on 26/6/2016.
//

#ifndef FINANCE_PAYOFF_H
#define FINANCE_PAYOFF_H

#include "nameDef.h"

class Payoff {
public:
    virtual Money GetPayoff(Quote Spot) const = 0;
};

class VanillaCallPayoff : public Payoff {
public:
    VanillaCallPayoff(Quote Strike);

    Money GetPayoff(Quote Spot) const override;

private:
    Quote Strike_;

};

#endif //FINANCE_PAYOFF_H
