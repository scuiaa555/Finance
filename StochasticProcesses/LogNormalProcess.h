//
// Created by CUI Shidong on 25/10/2016.
//

#ifndef FINANCE_LOGNORMALPROCESS_H
#define FINANCE_LOGNORMALPROCESS_H

#include "StochasticProcess.h"
#include "Parameter.h"

class LogNormalProcess : public StochasticProcess {
public:
    LogNormalProcess() = default;

    LogNormalProcess(Quote x0, const std::shared_ptr<Parameter> &drift, unsigned long dimVol,
                     const std::vector<std::shared_ptr<Parameter> > &volatility);

    Quote getSpot() const override;

private:
    Quote x0_;
    std::shared_ptr<Parameter> drift_;
    unsigned long dimVol_;
    std::vector<std::shared_ptr<Parameter> > volatility_;
};


#endif //FINANCE_LOGNORMALPROCESS_H
