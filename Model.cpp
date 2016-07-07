//
// Created by CUI Shidong on 27/6/2016.
//

#include "Model.h"

BSModel::BSModel(double r, double q, double sigma, double spot) : r_(r), q_(q), sigma_(sigma), spot_(spot) {
}

double BSModel::GetSpot() const {
    return spot_;
}

double BSModel::GetRiskFree() const {
    return r_;
}

double BSModel::GetDividend() const {
    return q_;
}

double BSModel::GetVolatility() const {
    return sigma_;
}

/*
void BSModel::GetParameterSet() {
    return;
}

BSModel::BSParameterSet::BSParameterSet(double r, double q, double sigma) :
        r_(r), q_(q), sigma_(sigma) { }

double BSModel::BSParameterSet::GetRiskFree() const {
    return r_;
}

double BSModel::BSParameterSet::GetDividend() const {
    return q_;
}

double BSModel::BSParameterSet::GetVolatility() const {
    return sigma_;
}
*/
