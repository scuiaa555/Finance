//
// Created by CUI Shidong on 16/7/2016.
//

#ifndef FINANCE_STOCHASTICPROCESS_H
#define FINANCE_STOCHASTICPROCESS_H

#include "nameDef.h"
#include "Model.h"
#include <vector>

using std::shared_ptr;
using std::vector;

class StochasticProcess {
public:
    /*!!! time-consuming issue: return type is a vector !!!*/
    /*!!! use move??                                    !!!*/
    virtual vector<Quote> evolve(Time t0, vector<Quote> x0, Time dt, double dw) const = 0;

//    virtual const std::vector<Quote> &GetInitial() const = 0;

//    virtual const std::vector<Quote> &G
//    mutable Quote x0_;

    virtual shared_ptr<Model> GetModel() const = 0;

//private:
    mutable std::vector<Quote> x0_;
};

class StochasticProcess1D : public StochasticProcess {
public:
    StochasticProcess1D(const shared_ptr<Model> &model) : model_(model) { }

    shared_ptr<Model> GetModel() const {
        x0_ = vector<Quote>(1, model_->getSpot());
        return model_;
    }

    void setModel(const shared_ptr<Model> model);

private:
    shared_ptr<Model> model_;
};

class BlackScholesProcess : public StochasticProcess1D {
public:
    BlackScholesProcess(shared_ptr<BSModel> model);

    BlackScholesProcess(double r, double q, double sigma, double spot);

    Quote evolve(Time t0, Quote x0, Time dt, double dw) const;

    vector<Quote> evolve(Time t0, vector<Quote> x0, Time dt, double dw) const override {
        return vector<Quote>{evolve(t0, x0[0], dt, dw)};
    };
};

#endif //FINANCE_STOCHASTICPROCESS_H
