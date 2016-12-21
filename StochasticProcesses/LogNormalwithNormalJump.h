//
// Created by CUI Shidong on 20/12/2016.
//

#ifndef FINANCE_LOGNORMALJUMP_H
#define FINANCE_LOGNORMALJUMP_H

#include "StochasticProcess.h"

class LogNormalWithNormalJump : public StochasticProcess {
public:

    LogNormalWithNormalJump() = default;

    LogNormalWithNormalJump(Quote x0, const shared_ptr<Parameter> &drift, unsigned long dimVol,
                            const std::vector<shared_ptr<Parameter> > &volatility, const shared_ptr<Parameter> jumpMean,
                            const shared_ptr<Parameter> jumpVariance);

    Quote getSpot() const override { return x0_; }

private:
    Quote x0_;
    shared_ptr<Parameter> drift_;
    unsigned long dimVol_;
    vector<std::shared_ptr<Parameter>> volatility_;
    shared_ptr<Parameter> jumpMean_;
    shared_ptr<Parameter> jumpVariance_;
};

#endif //FINANCE_LOGNORMALJUMP_H
