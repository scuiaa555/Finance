//
// Created by CUI Shidong on 16/7/2016.
//

#ifndef FINANCE_PATHGENERATOR_H
#define FINANCE_PATHGENERATOR_H

#include "RandNumGeneration/NormalMarsagliaBrayRng.h"
#include "Path.h"
#include "StochasticProcess.h"


class PathGenerator {
public:
    PathGenerator(const std::shared_ptr<StochasticProcess> process, const vector<Time> &timeGrid);

    Path &next();

private:
    NormalMarsagliaBrayRng<UniformLEcuyerRNG1> normalRng_;
    std::shared_ptr<StochasticProcess> process_;
    Path next_;

};


#endif //FINANCE_PATHGENERATOR_H
