//
// Created by CUI Shidong on 16/7/2016.
//

#ifndef FINANCE_STOCHASTICPROCESS_H
#define FINANCE_STOCHASTICPROCESS_H

#include "nameDef.h"
#include "Model.h"
#include <vector>

class StochasticProcess {
public:
    /* acceptable to return a vector by value, since vector has move assignment operation */
    virtual std::vector<Quote> evolve(Time t0, std::vector<Quote> x0, Time dt, double dw) const = 0;

//    virtual const std::vector<Quote> &GetInitial() const = 0;

//    virtual const std::vector<Quote> &G
//    mutable Quote x0_;

    virtual std::shared_ptr<Model> GetModel() const = 0;

    const std::vector<Quote> &getInitial() const { return x0_; }

protected:
    mutable std::vector<Quote> x0_;
};

class StochasticProcess1D : public StochasticProcess {
public:
    StochasticProcess1D(const std::shared_ptr<Model> &model) : model_(model) { }

    std::shared_ptr<Model> GetModel() const {
        x0_ = std::vector<Quote>(1, model_->getSpot());
        return model_;
    }

    void setModel(const std::shared_ptr<Model> model);

private:
    std::shared_ptr<Model> model_;
};

class BlackScholesProcess : public StochasticProcess1D {
public:
    BlackScholesProcess(std::shared_ptr<BSModel> model);

    BlackScholesProcess(double r, double q, double sigma, double spot);

    Quote evolve(Time t0, Quote x0, Time dt, double dw) const;

    std::vector<Quote> evolve(Time t0, std::vector<Quote> x0, Time dt, double dw) const override {
        return std::vector<Quote>{evolve(t0, x0[0], dt, dw)};
    };
};


#endif //FINANCE_STOCHASTICPROCESS_H
