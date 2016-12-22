//
// Created by CUI Shidong on 25/10/2016.
//

#ifndef FINANCE_BSSTOCHASTICPROCESS_H
#define FINANCE_BSSTOCHASTICPROCESS_H

#include "StochasticProcesses/LogNormalProcess.h"

class BSStochasticProcess : public LogNormalProcess<SingleVol> {
public:
    /**
     * @param r: riskfree rate
     * @param q: dividend rate
     * @param sigma: annualized volatility in percentage
     * @param spot: spot price of the underlying
     */
    BSStochasticProcess(double r, double q, double sigma, double spot);

//    Quote getSpot() const override;
//
    Rate getRiskFree() const;

//
    Rate getDividend() const;

//
    Rate getVolatility() const;

    Rate getVolatility(Time t) const override { return LogNormalProcess<SingleVol>::getVolatility(t); };

//private:
//    Quote spot_;
    double r_;
    double q_;
    double sigma_;
};


#endif //FINANCE_BSSTOCHASTICPROCESS_H
