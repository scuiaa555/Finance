//
// Created by CUI Shidong on 20/12/2016.
//

#ifndef FINANCE_MERTONJUMPMODEL_H
#define FINANCE_MERTONJUMPMODEL_H

#include "Model.h"
#include "StochasticProcesses/LogNormalwithNormalJump.h"
#include "RandNumGeneration/Normal.h"
#include "RandNumGeneration/CompoundPoisson.h"

class MertonJumpModel : public Model1D {
public:
    MertonJumpModel(std::shared_ptr<StochasticProcess> process);

    MertonJumpModel(double r, double q, double sigma, double lambda, double jumpMean, double jumpVariance, double spot);

    virtual Quote evolve(Time t0, Quote &x0, Time dt, vector<double> dw) const override;

    const vector<int> &getMCdimension() const override { return MCdimension_; }

    void setupArgument(Time t, Time dt, vector<GenericRandomVariableGenerator::Argument *> args) override;

private:
    vector<int> MCdimension_;
};

#endif //FINANCE_MERTONJUMPMODEL_H
