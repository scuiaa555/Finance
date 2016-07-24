//
// Created by CUI Shidong on 26/6/2016.
//

#ifndef FINANCE_PAYOFF_H
#define FINANCE_PAYOFF_H

#include "nameDef.h"
#include <string>

class Payoff {
public:
    virtual Money getPayoff(Quote spot) const = 0;
};


#endif //FINANCE_PAYOFF_H
