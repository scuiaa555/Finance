//
// Created by CUI Shidong on 25/10/2016.
//

#ifndef FINANCE_BLACKSCHOLESMODEL_H
#define FINANCE_BLACKSCHOLESMODEL_H

#include "Model.h"
#include "StochasticProcesses/BSStochasticProcess.h"

class BlackScholesModel : public Model1D {
public:
    BlackScholesModel(std::shared_ptr<BSStochasticProcess> process);

    BlackScholesModel(double r, double q, double sigma, double spot);

    Quote evolve(Time t0, Quote x0, Time dt, double dw) const;

    std::vector<Quote> evolve(Time t0, std::vector<Quote> &x0, Time dt, double dw) const override {
        return std::vector<Quote>{evolve(t0, x0[0], dt, dw)};
    };

    const vector<int> &getMCdimension() const { return MCdimension_; }

private:
    vector<int> MCdimension_;
};


#endif //FINANCE_BLACKSCHOLESMODEL_H
