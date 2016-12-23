//
// Created by CUI Shidong on 25/10/2016.
//

#include "BlackScholesModel.h"

BlackScholesModel::BlackScholesModel(shared_ptr<BSStochasticProcess> process) : Model1D(process) {
//    setModel(model);
}

BlackScholesModel::BlackScholesModel(double r, double q, double sigma, double spot) : Model1D(
        std::make_shared<BSStochasticProcess>(r, q, sigma, spot)) {
//    MCdimension_.resize(1, 1);
//    shared_ptr<BSModel> bsModel = std::make_shared<BSModel>(r, q, sigma, spot);
//    setModel(bsModel);
}

void BlackScholesModel::evolve(Time t0, Quote &x0, Time dt, double dw, double &value) const {
    shared_ptr<BSStochasticProcess> bsModel = std::dynamic_pointer_cast<BSStochasticProcess>(getProcess());
    Rate drift = bsModel->getDrift(t0);
    Rate sigma = bsModel->getVolatility(t0);
    value = x0 * exp((drift - sigma * sigma / 2.0) * dt + sigma * dw);
/*    should be compatible with different discretizations
    give full control to the discretization class (to be implemented)*/
}