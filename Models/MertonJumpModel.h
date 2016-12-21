//
// Created by CUI Shidong on 20/12/2016.
//

#ifndef FINANCE_MERTONJUMPMODEL_H
#define FINANCE_MERTONJUMPMODEL_H

#include "Model.h"
#include "StochasticProcesses/LogNormalwithNormalJump.h"

class MertonJumpModel : public Model1D {
public:
    MertonJumpModel(std::shared_ptr<LogNormalWithNormalJump> process);

    MertonJumpModel(double r, double q, double sigma, double jumpMean, double jumpVariance, double spot);

    Quote evolve(Time t0, Quote x0, Time dt, vector<double> dw) const;

    vector<Quote> evolve(Time t0, std::vector<Quote> &x0, Time dt, vector<double> dw) const override {
        return std::vector<Quote>{evolve(t0, x0[0], dt, dw)};
    };

    const vector<int> &getMCdimension() const override { return MCdimension_; }

    void setupArgument(Time t, Time dt, GenericRandomVariableGenerator::Argument *arg) override {
        GenericNormal::Argument *argument = dynamic_cast<GenericNormal::Argument *>(arg);
        argument->mean_ = 0.0;
        argument->variance_ = dt;
    }

private:
    vector<int> MCdimension_;
};

#endif //FINANCE_MERTONJUMPMODEL_H
