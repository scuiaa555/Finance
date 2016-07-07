//
// Created by CUI Shidong on 26/6/2016.
//

#ifndef FINANCE_PAYOFF_H
#define FINANCE_PAYOFF_H

#include "nameDef.h"

class Payoff {
public:
    virtual Money GetPayoff(Quote spot) const = 0;
};

class VanillaCallPayoff : public Payoff {
public:
    VanillaCallPayoff(Quote strike);

    Money GetPayoff(Quote spot) const override;

    Quote GetStrike() const;

private:
    Quote strike_;

};

#endif //FINANCE_PAYOFF_H
