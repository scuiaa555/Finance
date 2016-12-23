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

/**
 * Base class for all models(Black-Scholes model, Merton's jump model).
 * It is divided into two sub base classes.  \n
 * One is Model1D simply for model which only contains 1-d underlying asset(e.g. Black-Scholes). \n
 * Another one is ModelND for multi-dimensional underlyings(e.g. LMM). \n
 * Any specific model class should derive from Model1D or ModelND due to its dimension.
 * @tparam Type_of_single_time Value type of one path(double or vector<double>).
 */
template<typename Type_of_single_time>
class Model {
public:

    /**
     * Interface of evolve() when the required random number is only 1-d.
     * @param t0 Last time point, consistent with x0.
     * @param x0 Value at time t0.
     * @param dt Time step.
     * @param dw Random number required.
     * @param value Results of model evolution return by this reference.
     *
     * \e Implementation: There are two versions of evolve() as interfaces, distinguished by type of random numbers dw.
     * Each derived class should only override one of them, so they cannot be declared as pure virtual function.
     * And they are supposed not to be called. If they are called by mistake, they should throw "mismatch" error.
     */
    /* acceptable when return a vector by value, since vector has move assignment operation @todo change it to be inside the arguments */
    virtual void evolve(Time t0, Type_of_single_time &x0, Time dt, double dw, Type_of_single_time &value) const {
        throw ("Random numbers type of generator and model do not match.");
    }

    /**
     * Interface of evolve() when the required random numbers is multi-dimensional.
     * @param t0 Last time point, consistent with x0.
     * @param x0 Value at time t0.
     * @param dt Time step.
     * @param dw Random numbers required.
     * @param value Results of model evolution return by this reference.
     */
    virtual void
    evolve(Time t0, Type_of_single_time &x0, Time dt, vector<double> dw, Type_of_single_time &value) const {
        throw ("Random numbers type of generator and model do not match.");
    }

//    virtual const std::vector<Quote> &GetInitial() const = 0;

//    virtual const std::vector<Quote> &G
//    mutable Quote x0_;

    /**
     * Setup all the arguments that random number generators RNG needed.
     * @param t Time.
     * @param dt Time step.
     * @param arg The arguments are set through this pointer.
     */
    virtual void setupArgument(Time t, Time dt, GenericRandomVariableGenerator::Argument *arg) {
        throw ("RNG arguments type are mismatch.");
    }

    /**
     * Setup all the arguments that random number generators RNG needed.
     * @param t Time.
     * @param dt Time step.
     * @param args The arguments are set through this vector of pointers.
     */
    virtual void setupArgument(Time t, Time dt, vector<GenericRandomVariableGenerator::Argument *> args) {
        throw ("RNG arguments type are mismatch.");
    }

    /**
     * Return the stochastic process stored in the model. (For Model1D only)
     * @return Shared_ptr of requested process.
     */
    virtual const shared_ptr<StochasticProcess> &getProcess() const {
        throw ("This model is a multi-dimensional model. The index of processes must be specified.");
    }

    /**
     * Return the ith stochastic process stored in the model. (For ModelND only)
     * @param i Index of process.
     * @return Shared_ptr of requested process.
     */
    virtual const shared_ptr<StochasticProcess> &getProcess(int i) const = 0;

//    virtual const vector<int> &getMCdimension() const = 0;

    /**
     * Get the number of driving processes of the model. 1 if it is Model1D, n if it is ModelND.
     * @return Number of driving processes.
     */
    virtual unsigned long getDimension() const = 0;

    /**
     * Get the initial value of underlyings.
     * @return Vector or single double of initial value.
     */
    const Type_of_single_time &getInitial() const { return x0_; }

//    class Argument {
//    public:
//        virtual ~Argument() { }
//    };

protected:
    mutable Type_of_single_time x0_;  /**< Initial value of driving processes. */
};


/**
 * Derived class of Model and base class for all 1-d model.
 * It derived from Model and is to be derived from any model that has only one driving stochastic process. \n
 * \e How \e to \e use: \n
 * Member functions evolve() and setupArgument() need to override.\n
 * Overriding member function evolve() is required, while overriding setupArgument() depends on whether the model
 * is designed to possibly be priced by Monte Carlo simulation.
 */
class Model1D : public Model<double> {
public:

    /**
     * Default constructor.
     */
    Model1D() = default;

    /**
     * Constructor.
     * @param process Shared_ptr of a single stochastic process.
     */
    Model1D(const shared_ptr<StochasticProcess> &process) : process_(process) {
        x0_ = process_->getSpot();
    }

    /**
     * Return the stochastic process stored in the model.
     * @return Shared_ptr of requested process.
     */
    const shared_ptr<StochasticProcess> &getProcess() const override {
        return process_;
    }

    /**
     * Return the ith process, but this is Model1D. So if i!=1, error message will be thrown.
     */
    const shared_ptr<StochasticProcess> &getProcess(int i) const override {
        if (i != 0) throw ("This model only has one stochastic process.");
        return getProcess();
    }

    /**
     * Return dimension 1 as it is Model1D.
     * @return Dimension 1.
     */
    unsigned long getDimension() const override { return 1; }

    void setModel(const shared_ptr<StochasticProcess> &process) { process_ = process; }

protected:
    shared_ptr<StochasticProcess> process_;  /**< Shared_ptr of stochastic process. */
};


/**
 * Derived class of Model and base class for all multi-dimensional(d!=1) model.
 * It derived from Model and is to be derived from any model that has more than one driving stochastic processes.
 * * \e How \e to \e use: \n
 * Member functions evolve() and setupArgument() need to override.\n
 * Overriding member function evolve() is required, while overriding setupArgument() depends on whether the model
 * is designed to possibly be priced by Monte Carlo simulation.
 */
class ModelND : public Model<vector<double>> {
public:

    /**
     * Return the ith stochastic process of the model.
     * @param i The index of stochastic process.
     * @return Shared_ptr of the requested process.
     */
    const shared_ptr<StochasticProcess> &getProcess(int i) const override {
        return processes_[i];
    }

    /**
     * Return the number of driving processes of the model.
     * @return Number of driving processes.
     */
    unsigned long getDimension() const override { return dimension_; }

protected:
    vector<shared_ptr<StochasticProcess> > processes_; /**< Vector of shared_ptr of different stochastic processes. */
    unsigned long dimension_;                          /**< Number of driving processes. */
};


#endif //FINANCE_STOCHASTICPROCESS_H
