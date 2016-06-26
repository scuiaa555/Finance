//
// Created by CUI Shidong on 26/6/2016.
//

#ifndef FINANCE_PAYOFF_H
#define FINANCE_PAYOFF_H


class Payoff {
public:
    virtual double GetPayoff(double Spot) const = 0;
};

class VanillaCallPayoff : public Payoff {
public:
    VanillaCallPayoff(double Strike);

    double GetPayoff(double Spot) const override;

private:
    double Strike;

};

#endif //FINANCE_PAYOFF_H
