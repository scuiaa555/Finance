//
// Created by CUI Shidong on 25/10/2016.
//

#include "BSStochasticProcess.h"

BSStochasticProcess::BSStochasticProcess(double r, double q, double sigma, double spot)
        : LogNormalProcess(spot,
                           shared_ptr<Parameter>(new ConstantParameter(r - q)),
                           1,
                           shared_ptr<Parameter>(new ConstantParameter(sigma))),
          r_(r), q_(q), sigma_(sigma) {
}
//
//double BSStochasticProcess::getSpot() const {
//    return spot_;
//}

double BSStochasticProcess::getRiskFree() const {
    return r_;
}

double BSStochasticProcess::getDividend() const {
    return q_;
}

double BSStochasticProcess::getVolatility() const {
    return sigma_;
}

//void BSModel::GetParameterSet() {
//    return;
//}
//
//BSModel::BSParameterSet::BSParameterSet(double r, double q, double sigma) :
//        r_(r), q_(q), sigma_(sigma) { }
//
//double BSModel::BSParameterSet::getRiskFree() const {
//    return r_;
//}
//
//double BSModel::BSParameterSet::getDividend() const {
//    return q_;
//}
//
//double BSModel::BSParameterSet::getVolatility() const {
//    return sigma_;
//}
