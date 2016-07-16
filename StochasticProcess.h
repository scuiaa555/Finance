//
// Created by CUI Shidong on 16/7/2016.
//

#ifndef FINANCE_STOCHASTICPROCESS_H
#define FINANCE_STOCHASTICPROCESS_H

#include "nameDef.h"
#include "Model.h"

using std::shared_ptr;

class StochasticProcess {
public:
    virtual Quote evolve(Time t0, Quote x0, Time dt, double dw) const = 0;
};

class StochasticProcess1D : public StochasticProcess {
public:
    shared_ptr<Model> GetModel() const {
        return model_;
    }
    void SetModel(const shared_ptr<Model> model);

private:
    shared_ptr<Model> model_;
};

class BlackScholesProcess : public StochasticProcess1D {
public:
    BlackScholesProcess(shared_ptr<BSModel> model);
    BlackScholesProcess(double r, double q, double sigma, double spot);
    Quote evolve(Time t0, Quote x0, Time dt, double dw) const override;
};

#endif //FINANCE_STOCHASTICPROCESS_H
