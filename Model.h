//
// Created by CUI Shidong on 27/6/2016.
//

#ifndef FINANCE_MODEL_H
#define FINANCE_MODEL_H


#include <memory>
#include "nameDef.h"

class Model {
public:
    class ParameterSet {
    };

    virtual Quote GetSpot() const = 0;

    virtual ~Model() { }
};

class BSModel : public Model {
public:
    /**
     * @param r: riskfree rate
     * @param q: dividend rate
     * @param sigma: annualized volatility in percentage
     * @param spot: spot price of the underlying
     */
    BSModel(double r, double q, double sigma, double spot);


    Quote GetSpot() const override;

    Rate GetRiskFree() const;

    Rate GetDividend() const;

    Rate GetVolatility() const;

private:
    Quote spot_;
    Rate r_;
    Rate q_;
    Rate sigma_;

    /*class BSParameterSet : public virtual Model::ParameterSet {
    public:
        BSParameterSet(double r, double q, double sigma);

        double GetRiskFree() const;

        double GetDividend() const;

        double GetVolatility() const;

        double r_;
        double q_;
        double sigma_;
    };*/

//std::shared_ptr<BSParameterSet> GetParameterSet();

//private:
//std::shared_ptr<Model::ParameterSet> parameterSet_;

};


#endif //FINANCE_MODEL_H
