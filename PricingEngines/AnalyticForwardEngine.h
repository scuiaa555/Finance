//
// Created by CUI Shidong on 10/7/2016.
//

#ifndef FINANCE_ANALYTICFORWARDENGINE_H
#define FINANCE_ANALYTICFORWARDENGINE_H

#include "Instruments/Forward.h"

class AnalyticForwardEngine : public Forward::engine {
public:
    AnalyticForwardEngine(Rate r);

//    double test(double a) { return a; }

    void calculate() override;

private:
    Rate r_;
};


#endif //FINANCE_ANALYTICFORWARDENGINE_H
