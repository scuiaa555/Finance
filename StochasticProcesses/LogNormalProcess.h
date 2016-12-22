//
// Created by CUI Shidong on 25/10/2016.
//

#ifndef FINANCE_LOGNORMALPROCESS_H
#define FINANCE_LOGNORMALPROCESS_H

#include "StochasticProcess.h"
#include "Parameter.h"

struct SingleVol {
    typedef double vol_return_type;
    typedef shared_ptr<Parameter> vol_ptr_type;
};

struct MultiVol {
    typedef vector<double> vol_return_type;
    typedef vector<shared_ptr<Parameter>> vol_ptr_type;
};

template<typename VolType>
class LogNormalProcess : public virtual StochasticProcess {
public:

    typedef typename VolType::vol_return_type vol_return_type;
    typedef typename VolType::vol_ptr_type vol_ptr_type;

    LogNormalProcess() = default;

    LogNormalProcess(Quote x0, const shared_ptr<Parameter> &drift, unsigned long dimVol,
                     const vol_ptr_type &volatility);

    virtual double getSpot() const override { return x0_; }

    double getDrift(Time t) const;

    virtual vol_return_type getVolatility(Time t) const;

    unsigned long getVolDimension() const { return dimVol_; }


private:

    Quote x0_;
    shared_ptr<Parameter> drift_;
    unsigned long dimVol_;
    vol_ptr_type volatility_;

    double getVolHelper(const shared_ptr<Parameter> vol, Time t) const;

    vector<double> getVolHelper(const vector<shared_ptr<Parameter>> vols, Time t) const;

};

template<typename VolType>
LogNormalProcess<VolType>::LogNormalProcess(Quote x0, const shared_ptr<Parameter> &drift, unsigned long dimVol,
                                            const typename LogNormalProcess<VolType>::vol_ptr_type &volatility)
        :x0_(x0),
         drift_(drift),
         dimVol_(dimVol),
         volatility_(volatility) {
}

template<typename VolType>
double LogNormalProcess<VolType>::getDrift(Time t) const {
    return (*drift_)(t);
}

template<typename VolType>
typename LogNormalProcess<VolType>::vol_return_type LogNormalProcess<VolType>::getVolatility(Time t) const {
    if (dimVol_ == 1) {
        return getVolHelper(volatility_, t);
    } else {
        return getVolHelper(volatility_, t);
    }
}

template<typename VolType>
double LogNormalProcess<VolType>::getVolHelper(const shared_ptr<Parameter> vol, Time t) const {
    return (*vol)(t);
}

template<typename VolType>
vector<double> LogNormalProcess<VolType>::getVolHelper(const vector<shared_ptr<Parameter>> vols, Time t) const {
    vector<double> val;
    for (int i = 1; i < dimVol_; ++i) {
        val.push_back((*(vols[i]))(t));
    }
    return val;
}

#endif //FINANCE_LOGNORMALPROCESS_H
