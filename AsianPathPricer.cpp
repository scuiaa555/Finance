//
// Created by CUI Shidong on 23/7/2016.
//

#include "AsianPathPricer.h"
#include <numeric>
#include <cmath>

AsianPathPricer::AsianPathPricer(std::shared_ptr<Payoff> payoff, Rate discount,
                                 std::shared_ptr<vector<Time> > monitoredTimesPtr, AsianOption::AverageType averageType)
        : payoff_(payoff),
          discount_(discount),
          monitoredTimesPtr_(
                  monitoredTimesPtr), averageType_(averageType), monitoredTimesIters_() {
}

Money AsianPathPricer::operator()(const Path &path) const {
    /* time consuming */
    vector<Time>::const_iterator iterNext = path.timeGrid_.cbegin();
    vector<Time>::const_iterator iterTimeBegin = path.timeGrid_.cbegin();
    vector<Quote>::const_iterator iterValueBegin = path.values_.cbegin();
    if (monitoredTimesIters_.empty()) {
        for (vector<Time>::const_iterator iterMnt = (*monitoredTimesPtr_).cbegin();
             iterMnt != (*monitoredTimesPtr_).cend(); iterMnt++) {
            iterNext = std::find_if(iterNext, path.timeGrid_.cend(), [iterMnt](Time t) -> bool {
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
                              spot += (*(iterValueBegin + (iter - iterTimeBegin)));
                          });
            spot /= N;
            break;
        case AsianOption::AverageType::geometric:
            spot = 1.0;
            std::for_each(monitoredTimesIters_.cbegin(), monitoredTimesIters_.cend(),
                          [&](vector<Time>::const_iterator iter) {
                              spot *= (*(iterValueBegin + (iter - iterTimeBegin)));
                          });
            spot = std::pow(spot, 1.0 / N);
            break;
    }
    Rate discountFactor = exp(-discount_ * path.timeGrid_.back());
    price = payoff_->getPayoff(spot) * discountFactor;
    return price;
}



