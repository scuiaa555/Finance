//
// Created by CUI Shidong on 27/6/2016.
//

#ifndef FINANCE_MODEL_H
#define FINANCE_MODEL_H


#include <memory>
#include "nameDef.h"

class StochasticProcess {
public:
    class ParameterSet {
    };

    virtual Quote getSpot() const = 0;

    virtual ~StochasticProcess() { }
};

class BSStochasticProcess : public StochasticProcess {
public:
    /**
     * @param r: riskfree rate
     * @param q: dividend rate
     * @param sigma: annualized volatility in percentage
     * @param spot: spot price of the underlying
     */
    BSStochasticProcess(double r, double q, double sigma, double spot);

    Quote getSpot() const override;

    Rate getRiskFree() const;

    Rate getDividend() const;

    Rate getVolatility() const;

private:
    Quote spot_;
    Rate r_;
    Rate q_;
    Rate sigma_;

//    class BSParameterSet : public virtual Model::ParameterSet {
//    public:
//        BSParameterSet(double r, double q, double sigma);
//
//        double getRiskFree() const;
//
//        double getDividend() const;
//
//        double getVolatility() const;
//
//        double r_;
//        double q_;
//        double sigma_;
//    };

//std::shared_ptr<BSParameterSet> GetParameterSet();

//private:
//std::shared_ptr<Model::ParameterSet> parameterSet_;

};


#endif //FINANCE_MODEL_H
