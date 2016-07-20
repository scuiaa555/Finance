//
// Created by CUI Shidong on 16/7/2016.
//

#include "StochasticProcess.h"
#include <cmath>

void StochasticProcess1D::SetModel(const shared_ptr<Model> model) {
    model_ = model;
}

BlackScholesProcess::BlackScholesProcess(shared_ptr<BSModel> model):StochasticProcess1D(model) {
//    SetModel(model);
}

BlackScholesProcess::BlackScholesProcess(double r, double q, double sigma, double spot):StochasticProcess1D(std::make_shared<BSModel>(r, q, sigma, spot)) {
//    shared_ptr<BSModel> bsModel = std::make_shared<BSModel>(r, q, sigma, spot);
//    SetModel(bsModel);
}

Quote BlackScholesProcess::evolve(Time t0, Quote x0, Time dt, double dw) const {
    shared_ptr<BSModel> bsModel = std::dynamic_pointer_cast<BSModel>(GetModel());
    Rate r = bsModel->GetRiskFree();
    Rate sigma = bsModel->GetVolatility();
    Rate q = bsModel->GetDividend();
    return x0 * exp((r - q - sigma * sigma / 2.0) * dt + sigma * dw);
/*    should be compatible with different discretizations
    give full control to the discretization class (to be implemented)*/
}

