//
// Created by CUI Shidong on 21/7/2016.
//

#ifndef FINANCE_VANILLAPAYOFF_H
#define FINANCE_VANILLAPAYOFF_H

#include "Payoff.h"


class VanillaPayoff : public Payoff {
public:
    VanillaPayoff(Quote strike, std::string type);

    Money getPayoff(Quote spot) const override;

    Quote getStrike() const;

    double getType() const;

private:
    Quote strike_;
    double type_;   //1 for call, -1 for put

};


#endif //FINANCE_VANILLAPAYOFF_H
