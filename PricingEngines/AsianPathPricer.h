//
// Created by CUI Shidong on 23/7/2016.
//

#ifndef FINANCE_ASIANPATHPRICER_H
#define FINANCE_ASIANPATHPRICER_H

#include "McFramework/PathPricer.h"
#include "Payoff.h"
#include "Instruments/AsianOption.h"

class AsianPathPricer : public PathPricer<SingleVariate> {
public:
    AsianPathPricer(std::shared_ptr<Payoff> payoff, Rate discount, std::shared_ptr<vector<Time> > monitoredTimesPtr,
                    AsianOption::AverageType averageType, bool isAntithetic);

    Money operator()(const Path<SingleVariate> &path) const override;

private:
    std::shared_ptr<Payoff> payoff_;
    Rate discount_;
    std::shared_ptr<vector<Time> > monitoredTimesPtr_;
    AsianOption::AverageType averageType_;
    mutable vector<vector<Time>::const_iterator> monitoredTimesIters_;

    bool isAntithetic_;

    Money onePathCalc(const vector<Time> &timeGrid, const vector<vector<Quote> > &values) const;

};


#endif //FINANCE_ASIANPATHPRICER_H
