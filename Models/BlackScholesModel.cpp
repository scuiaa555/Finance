//
// Created by CUI Shidong on 25/10/2016.
//

#include "BlackScholesModel.h"
#include <cmath>

BlackScholesModel::BlackScholesModel(std::shared_ptr<BSStochasticProcess> process):Model1D(process) {
//    setModel(model);
}

BlackScholesModel::BlackScholesModel(double r, double q, double sigma, double spot):Model1D(std::make_shared<BSStochasticProcess>(r, q, sigma, spot)) {
//    shared_ptr<BSModel> bsModel = std::make_shared<BSModel>(r, q, sigma, spot);
//    setModel(bsModel);
}

Quote BlackScholesModel::evolve(Time t0, Quote x0, Time dt, double dw) const {
    std::shared_ptr<BSStochasticProcess> bsModel = std::dynamic_pointer_cast<BSStochasticProcess>(getProcess());
    Rate r = bsModel->getRiskFree();
    Rate sigma = bsModel->getVolatility();
    Rate q = bsModel->getDividend();
    return x0 * exp((r - q - sigma * sigma / 2.0) * dt + sigma * dw);
/*    should be compatible with different discretizations
    give full control to the discretization class (to be implemented)*/
}