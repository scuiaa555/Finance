//
// Created by CUI Shidong on 25/10/2016.
//

#ifndef FINANCE_PARAMETER_H
#define FINANCE_PARAMETER_H

#include <vector>
#include "NameDef.h"

/* Assume that Parameter is always 1-d.
 * If one stochastic process is multi-dimensional,
 * one way to handle is contain a vector of Parameters */
class Parameter {
public:
    Parameter() = default;

    Parameter(const Parameter &) = default;

    Parameter &operator=(const Parameter&) = default;

    virtual double operator()(Time t) const = 0;

    /* for calibration */
    void setParam(int i, double newVal) { params_[i] = newVal; }

    unsigned long size() const { return params_.size(); }

protected:
//    Parameter(std::vector<double> &param) : params_(param) { }

    std::vector<double> params_;

};

class ConstantParameter : public Parameter {
public:
    ConstantParameter() = default;

    ConstantParameter(double param);

    double operator()(Time t) const override;
};

class NullParameter : public ConstantParameter {
public:
    NullParameter() : ConstantParameter(0.0) { }
};

#endif //FINANCE_PARAMETER_H
