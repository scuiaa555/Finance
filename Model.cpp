//
// Created by CUI Shidong on 27/6/2016.
//

#include "Model.h"

BSModel::BSModel(double r, double q, double sigma, double spot) : r_(r), q_(q), sigma_(sigma), spot_(spot) {
}

double BSModel::getSpot() const {
    return spot_;
}

double BSModel::getRiskFree() const {
    return r_;
}

double BSModel::getDividend() const {
    return q_;
}

double BSModel::getVolatility() const {
    return sigma_;
}

/*
void BSModel::GetParameterSet() {
    return;
}

BSModel::BSParameterSet::BSParameterSet(double r, double q, double sigma) :
        r_(r), q_(q), sigma_(sigma) { }

double BSModel::BSParameterSet::getRiskFree() const {
    return r_;
}

double BSModel::BSParameterSet::getDividend() const {
    return q_;
}

double BSModel::BSParameterSet::getVolatility() const {
    return sigma_;
}
*/
