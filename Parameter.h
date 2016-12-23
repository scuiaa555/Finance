//
// Created by CUI Shidong on 25/10/2016.
//

#ifndef FINANCE_PARAMETER_H
#define FINANCE_PARAMETER_H

#include <vector>
#include "NameDef.h"

using std::vector;

/* Assume that Parameter is always 1-d.
 * If one stochastic process is multi-dimensional,
 * one way to handle this is contain a vector of Parameters */
class Parameter {
public:
    Parameter() = default;

    Parameter(const Parameter &) = default;

    Parameter &operator=(const Parameter &) = default;

    virtual double operator()(Time t) const = 0;

    /* for calibration */
    void setParam(int i, double newVal) { params_[i] = newVal; }

    unsigned long size() const { return params_.size(); }

protected:
//    Parameter(std::vector<double> &param) : params_(param) { }

    vector<double> params_;

};

class ConstantParameter : public Parameter {
public:
    ConstantParameter() = default;

    ConstantParameter(double param);

    double operator()(Time t) const override;

    double operator()() const { return params_[0]; }
};

class NullParameter : public ConstantParameter {
public:
    NullParameter() : ConstantParameter(0.0) {}
};

#endif //FINANCE_PARAMETER_H
