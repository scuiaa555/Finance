//
// Created by CUI Shidong on 20/12/2016.
//

#ifndef FINANCE_LOGNORMALJUMP_H
#define FINANCE_LOGNORMALJUMP_H

#include "StochasticProcesses/LogNormalProcess.h"

template<typename VolType>
class LogNormalWithNormalJump : protected LogNormalProcess<VolType>,  /* "has-a" relationship */
                                public virtual StochasticProcess {
public:

    typedef typename VolType::vol_return_type vol_return_type;
    typedef typename VolType::vol_ptr_type vol_ptr_type;

    LogNormalWithNormalJump() = default;

    LogNormalWithNormalJump(Quote x0, const shared_ptr<Parameter> &drift, unsigned long dimVol,
                            const vol_ptr_type volatility, const shared_ptr<Parameter> lambda,
                            const shared_ptr<Parameter> jumpMean, const shared_ptr<Parameter> jumpVariance);

    LogNormalWithNormalJump(Quote x0, double drift, double volatility, double lambda, double jumpMean,
                            double jumpVariance);

    virtual double getSpot() const override { return LogNormalProcess<VolType>::x0_; }

    shared_ptr<Parameter> getDrift() const { return LogNormalProcess<VolType>::drift_; }

    vol_ptr_type getVolatility() const { return LogNormalProcess<VolType>::volatility_; }

    shared_ptr<Parameter> getLambda() const { return lambda_; }

    shared_ptr<Parameter> getJumpMean() const { return jumpMean_; }

    shared_ptr<Parameter> getJumpVariance() const { return jumpVariance_; }

private:
    shared_ptr<Parameter> lambda_;
    shared_ptr<Parameter> jumpMean_;
    shared_ptr<Parameter> jumpVariance_;
};

template<typename VolType>
LogNormalWithNormalJump<VolType>::LogNormalWithNormalJump(Quote x0, const shared_ptr<Parameter> &drift,
                                                          unsigned long dimVol, const vol_ptr_type volatility,
                                                          const shared_ptr<Parameter> lambda,
                                                          const shared_ptr<Parameter> jumpMean,
                                                          const shared_ptr<Parameter> jumpVariance)
        : LogNormalProcess<VolType>(x0, drift, dimVol, volatility), lambda_(lambda), jumpMean_(jumpMean),
          jumpVariance_(jumpVariance) {
}


template<typename VolType>
LogNormalWithNormalJump<VolType>::LogNormalWithNormalJump(Quote x0, double drift, double volatility,
                                                          double lambda, double jumpMean, double jumpVariance)
        : LogNormalProcess<VolType>(x0, shared_ptr<Parameter>(new ConstantParameter(drift)),
                                    1, shared_ptr<Parameter>(new ConstantParameter(volatility))),
          lambda_(shared_ptr<Parameter>(new ConstantParameter(lambda))),
          jumpMean_(shared_ptr<Parameter>(new ConstantParameter(jumpMean))),
          jumpVariance_(shared_ptr<Parameter>(new ConstantParameter(jumpVariance))) {
}

#endif //FINANCE_LOGNORMALJUMP_H
