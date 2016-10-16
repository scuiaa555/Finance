//
// Created by CUI Shidong on 23/7/2016.
//

#include "PricingEngines/AsianPathPricer.h"
#include <numeric>
#include <cmath>

AsianPathPricer::AsianPathPricer(std::shared_ptr<Payoff> payoff, Rate discount,
                                 std::shared_ptr<vector<Time> > monitoredTimesPtr, AsianOption::AverageType averageType,
                                 bool isAntithetic)
        : payoff_(payoff),
          discount_(discount),
          monitoredTimesPtr_(monitoredTimesPtr),
          averageType_(averageType),
          monitoredTimesIters_(),
          isAntithetic_(isAntithetic) {
}

Money AsianPathPricer::onePathCalc(const vector<Time> &timeGrid, const vector<vector<Quote> > &values) const {
    vector<Time>::const_iterator iterNext = timeGrid.cbegin();
    vector<Time>::const_iterator iterTimeBegin = timeGrid.cbegin();
    vector<vector<Quote>>::const_iterator iterValueBegin = values.cbegin();
    if (monitoredTimesIters_.empty()) {
        for (vector<Time>::const_iterator iterMnt = (*monitoredTimesPtr_).cbegin();
             iterMnt != (*monitoredTimesPtr_).cend(); iterMnt++) {
            iterNext = std::find_if(iterNext, timeGrid.cend(), [iterMnt](
                    Time t) -> bool {    // lambda expression: [capture list](parameter list) -> return type {function body}
                return std::abs(t - (*iterMnt)) < 1e-10;
            });
            monitoredTimesIters_.push_back(iterNext);
        }
    }
    Money price;
    Quote spot;
    auto N = (*monitoredTimesPtr_).size();
    switch (averageType_) {
        case AsianOption::AverageType::arithmetic :
            spot = 0.0;
            std::for_each(monitoredTimesIters_.cbegin(), monitoredTimesIters_.cend(),
                          [&](vector<Time>::const_iterator iter) {
                              spot += (*(iterValueBegin + (iter - iterTimeBegin)))[0];
                          });
            spot /= N;
            break;
        case AsianOption::AverageType::geometric:
            spot = 1.0;
            std::for_each(monitoredTimesIters_.cbegin(), monitoredTimesIters_.cend(),
                          [&](vector<Time>::const_iterator iter) {
                              spot *= (*(iterValueBegin + (iter - iterTimeBegin)))[0];
                          });
            spot = std::pow(spot, 1.0 / N);
            break;
    }
    Rate discountFactor = exp(-discount_ * timeGrid.back());
    price = payoff_->getPayoff(spot) * discountFactor;
    return price;
}

Money AsianPathPricer::operator()(const Path &path) const {
    if (!isAntithetic_) {
        return onePathCalc(path.getTimeGrid(), path.getValues());
    }
    else {
        return (onePathCalc(path.getTimeGrid(), path.getValues()) +
                onePathCalc(path.getTimeGrid(), path.getAntitheticValues())) / 2.0;
    }

}



