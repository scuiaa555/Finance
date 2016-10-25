//
// Created by CUI Shidong on 25/10/2016.
//

#include "Parameter.h"

ConstantParameter::ConstantParameter(double param) {
    params_.resize(1,param);
}

double ConstantParameter::operator()(Time t) const {
    return params_[0];
}