//
// Created by CUI Shidong on 16/7/2016.
//

#include "StochasticProcess.h"
#include <cmath>

void StochasticProcess1D::setModel(const std::shared_ptr<Model> model) {
    model_ = model;
}

BlackScholesProcess::BlackScholesProcess(std::shared_ptr<BSModel> model):StochasticProcess1D(model) {
//    setModel(model);
}

BlackScholesProcess::BlackScholesProcess(double r, double q, double sigma, double spot):StochasticProcess1D(std::make_shared<BSModel>(r, q, sigma, spot)) {
//    shared_ptr<BSModel> bsModel = std::make_shared<BSModel>(r, q, sigma, spot);
//    setModel(bsModel);
}

Quote BlackScholesProcess::evolve(Time t0, Quote x0, Time dt, double dw) const {
    std::shared_ptr<BSModel> bsModel = std::dynamic_pointer_cast<BSModel>(GetModel());
    Rate r = bsModel->getRiskFree();
    Rate sigma = bsModel->getVolatility();
    Rate q = bsModel->getDividend();
    return x0 * exp((r - q - sigma * sigma / 2.0) * dt + sigma * dw);
/*    should be compatible with different discretizations
    give full control to the discretization class (to be implemented)*/
}

