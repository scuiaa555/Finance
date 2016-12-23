//
// Created by CUI Shidong on 16/7/2016.
//

#ifndef FINANCE_STOCHASTICPROCESS_H
#define FINANCE_STOCHASTICPROCESS_H

#include "NameDef.h"
#include "StochasticProcess.h"
#include <vector>
#include <RandNumGeneration/RandomVariableGenerator.h>

using std::vector;

template<typename Type_of_single_time>
class Model {
public:
    /* acceptable when return a vector by value, since vector has move assignment operation */
    virtual Type_of_single_time evolve(Time t0, Type_of_single_time &x0, Time dt, double dw) const {
        throw ("Random numbers type of generator and model do not match.");
    }

    virtual Type_of_single_time evolve(Time t0, Type_of_single_time &x0, Time dt, vector<double> dw) const {
        throw ("Random numbers type of generator and model do not match.");
    }

//    virtual const std::vector<Quote> &GetInitial() const = 0;

//    virtual const std::vector<Quote> &G
//    mutable Quote x0_;
    virtual const shared_ptr<StochasticProcess> &getProcess() const = 0;

    virtual const shared_ptr<StochasticProcess> &getProcess(int i) const = 0;

    virtual const vector<int> &getMCdimension() const = 0;

    virtual unsigned long getDimensionality() const = 0;

    /* return i-th process */

    const Type_of_single_time &getInitial() const { return x0_; }

//    class Argument {
//    public:
//        virtual ~Argument() { }
//    };

    virtual void setupArgument(Time t, Time dt, GenericRandomVariableGenerator::Argument *) {}

    virtual void setupArgument(Time t, Time dt, vector<GenericRandomVariableGenerator::Argument *>) {}

protected:
    mutable Type_of_single_time x0_;
};

/* 1D means that this model only has one driving stochastic process */
class Model1D : public Model<double> {
public:

    Model1D() = default;

    Model1D(const shared_ptr<StochasticProcess> &process) : process_(process) {
        x0_ = process_->getSpot();
    }

    const shared_ptr<StochasticProcess> &getProcess() const override {
        return process_;
    }

    const shared_ptr<StochasticProcess> &getProcess(int i) const override {
        if (i != 0) throw ("This model only has one stochastic process.");
        return getProcess();
    }

    unsigned long getDimensionality() const override { return 1; }

    void setModel(const shared_ptr<StochasticProcess> &process) { process_ = process; }

protected:
    shared_ptr<StochasticProcess> process_;
};

class ModelND : public Model<vector<double>> {
public:
    const shared_ptr<StochasticProcess> &getProcess() const override {
        throw ("This model is a multi-dimensional model. Which process must be specified.");
    }

    const shared_ptr<StochasticProcess> &getProcess(int i) const override {
        return processes_[i];
    }

    unsigned long getDimensionality() const override { return dimension_; }

protected:
    vector<shared_ptr<StochasticProcess> > processes_;
    unsigned long dimension_; /* number of 1D-processes */
};


#endif //FINANCE_STOCHASTICPROCESS_H
