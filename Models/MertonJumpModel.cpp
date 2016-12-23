//
// Created by CUI Shidong on 20/12/2016.
//

#include "MertonJumpModel.h"

MertonJumpModel::MertonJumpModel(std::shared_ptr<StochasticProcess> process) : Model1D(process) {
}

MertonJumpModel::MertonJumpModel(double r, double q, double sigma, double lambda, double jumpMean, double jumpVariance,
                                 double spot) : Model1D(shared_ptr<StochasticProcess>(
        new LogNormalWithNormalJump<SingleVol>(spot, r - q - lambda * jumpMean, sigma, lambda, jumpMean,
                                               jumpVariance))) {
}

void MertonJumpModel::evolve(Time t0, Quote &x0, Time dt, vector<double> dw, double &value) const {
    shared_ptr<LogNormalWithNormalJump<SingleVol>> process = std::dynamic_pointer_cast<LogNormalWithNormalJump<SingleVol>>(
            process_);
    double drift = (*std::dynamic_pointer_cast<ConstantParameter>(process->getDrift()))();
    double sigma = (*std::dynamic_pointer_cast<ConstantParameter>(process->getVolatility()))();
    value = x0 * exp(sigma * dw[0] + (drift - 0.5 * sigma * sigma) * dt + dw[1]);
}

void MertonJumpModel::setupArgument(Time t, Time dt, vector<GenericRandomVariableGenerator::Argument *> args) {
    shared_ptr<LogNormalWithNormalJump<SingleVol>> process = std::dynamic_pointer_cast<LogNormalWithNormalJump<SingleVol>>(
            process_);
    GenericNormal::Argument *argDiffNormal = dynamic_cast<GenericNormal::Argument *>(args[0]);
    GenericCompoundPoisson::Argument *argCompoundPoisson = dynamic_cast<GenericCompoundPoisson::Argument *>(args[1]);
    argDiffNormal->mean_ = 0.0;
    argDiffNormal->variance_ = dt;
    argCompoundPoisson->argPtrPoisson_->lambda_ = (*std::dynamic_pointer_cast<ConstantParameter>(
            process->getLambda()))();
    dynamic_cast<GenericNormal::Argument *>(argCompoundPoisson->argPtrJump_)->mean_ =
            (*std::dynamic_pointer_cast<ConstantParameter>(process->getJumpMean()))() + 1;
    dynamic_cast<GenericNormal::Argument *>(argCompoundPoisson->argPtrJump_)->variance_ = (*std::dynamic_pointer_cast<ConstantParameter>(
            process->getJumpVariance()))();
}

