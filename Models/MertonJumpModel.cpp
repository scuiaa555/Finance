//
// Created by CUI Shidong on 20/12/2016.
//

#include "MertonJumpModel.h"

void MertonJumpModel::setupArgument(Time t, Time dt, vector<GenericRandomVariableGenerator::Argument *> args) {
    GenericCompoundPoisson::Argument *argCompoundPoisson = dynamic_cast<GenericCompoundPoisson::Argument *>(args[1]);
    argCompoundPoisson->argPtrPoisson_->lambda_=
    dynamic_cast<GenericCompoundPoisson::Argument *>(rng.getArgument())->argPtrPoisson_->lambda_ = 1.0;
    dynamic_cast<GenericNormal::Argument *>(dynamic_cast<GenericCompoundPoisson::Argument *>(rng.getArgument())->argPtrJump_)->mean_ = 0.0;
    dynamic_cast<GenericNormal::Argument *>(dynamic_cast<GenericCompoundPoisson::Argument *>(rng.getArgument())->argPtrJump_)->variance_ = 5.0;
}
