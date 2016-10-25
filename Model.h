//
// Created by CUI Shidong on 16/7/2016.
//

#ifndef FINANCE_STOCHASTICPROCESS_H
#define FINANCE_STOCHASTICPROCESS_H

#include "NameDef.h"
#include "StochasticProcess.h"
#include <vector>

class Model {
public:
    /* acceptable to return a vector by value, since vector has move assignment operation */
    virtual std::vector<Quote> evolve(Time t0, std::vector<Quote> x0, Time dt, double dw) const = 0;

//    virtual const std::vector<Quote> &GetInitial() const = 0;

//    virtual const std::vector<Quote> &G
//    mutable Quote x0_;

    virtual std::shared_ptr<StochasticProcess> getProcess() const = 0;

    const std::vector<Quote> &getInitial() const { return x0_; }

protected:
    mutable std::vector<Quote> x0_;
};

class Model1D : public Model {
public:
    Model1D(const std::shared_ptr<StochasticProcess> &process) : process_(process) { }

    std::shared_ptr<StochasticProcess> getProcess() const {
        x0_ = std::vector<Quote>(1, process_->getSpot());
        return process_;
    }

    void setModel(const std::shared_ptr<StochasticProcess> process);

private:
    std::shared_ptr<StochasticProcess> process_;
};

class ModelND : public Model {

};

class BlackScholesModel : public Model1D {
public:
    BlackScholesModel(std::shared_ptr<BSStochasticProcess> process);

    BlackScholesModel(double r, double q, double sigma, double spot);

    Quote evolve(Time t0, Quote x0, Time dt, double dw) const;

    std::vector<Quote> evolve(Time t0, std::vector<Quote> x0, Time dt, double dw) const override {
        return std::vector<Quote>{evolve(t0, x0[0], dt, dw)};
    };
};


#endif //FINANCE_STOCHASTICPROCESS_H
