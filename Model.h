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
    /* acceptable when return a vector by value, since vector has move assignment operation */
    virtual std::vector<Quote> evolve(Time t0, std::vector<Quote> &x0, Time dt, double dw) const = 0;

//    virtual const std::vector<Quote> &GetInitial() const = 0;

//    virtual const std::vector<Quote> &G
//    mutable Quote x0_;
    virtual const std::shared_ptr<StochasticProcess> &getProcess() const = 0;

    virtual const std::shared_ptr<StochasticProcess> &getProcess(int i) const = 0;

    virtual unsigned long getDimensionality() const = 0;

    /* return i-th process */

    const std::vector<Quote> &getInitial() const { return x0_; }

protected:
    mutable std::vector<Quote> x0_;
};

/* 1D means that this model only has one driving stochastic process */
class Model1D : public Model {
public:
    Model1D(const std::shared_ptr<StochasticProcess> &process) : process_(process) {
        x0_ = std::vector<Quote>(1, process_->getSpot());
    }

    const std::shared_ptr<StochasticProcess> &getProcess() const override {
        return process_;
    }

    const std::shared_ptr<StochasticProcess> &getProcess(int i) const override {
        if (i != 0) throw ("This model only has one stochastic process.");
        return getProcess();
    }

    unsigned long getDimensionality() const override { return 1; }

    void setModel(const std::shared_ptr<StochasticProcess> &process) { process_ = process; }

protected:
    std::shared_ptr<StochasticProcess> process_;
};

class ModelND : public Model {
public:
    const std::shared_ptr<StochasticProcess> &getProcess() const override {
        throw ("This model is a multi-dimensional model. Which process must be specified.");
    }

    const std::shared_ptr<StochasticProcess> &getProcess(int i) const override {
        return processes_[i];
    }

    unsigned long getDimensionality() const override { return dimensional_; }

protected:
    std::vector<std::shared_ptr<StochasticProcess> > processes_;
    unsigned long dimensional_; /* number of 1D-processes */
};


#endif //FINANCE_STOCHASTICPROCESS_H
