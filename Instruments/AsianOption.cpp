//
// Created by CUI Shidong on 23/7/2016.
//

#include "AsianOption.h"
#include <numeric>
#include <math.h>

AsianOption::AsianOption(Time maturity, std::shared_ptr<Payoff> payoff, std::vector<Time> &monitoredTimes,
                         AverageType averageType,
                         bool isDiscretelyMonitored) : maturity_(maturity), payoff_(payoff),
                                                       monitoredTimes_(monitoredTimes), averageType_(averageType) {
}

AsianOption::AsianOption(Time maturity, std::shared_ptr<Payoff> payoff, Time timeStep, AverageType averageType,
                         bool isDiscretelyMonitored)
        : maturity_(maturity), payoff_(payoff), averageType_(averageType) {
    monitoredTimes_.resize(rint(maturity / timeStep) + 1);
    std::iota(monitoredTimes_.begin(), monitoredTimes_.end(), 0);
    /* both for_each and transform succeed
     * lambda used here */
//    std::for_each(monitoredTimes_.begin(), monitoredTimes_.end(), [timeStep](Time &t) { t *= timeStep; });
    std::transform(monitoredTimes_.begin(), monitoredTimes_.end(), monitoredTimes_.begin(),
                   [=](Time t) -> Time { return t * timeStep; });
}

AsianOption::AsianOption(Time maturity, std::shared_ptr<Payoff> payoff, AverageType averageType,
                         bool isContinuouslyMonitored) : maturity_(
        maturity), payoff_(payoff), averageType_(averageType) { }

void AsianOption::setupArguments(PricingEngine::Arguments *arg) const {
    AsianOption::Arguments *arguments;
    arguments = dynamic_cast<AsianOption::Arguments *>(arg);
    arguments->payoff_ = payoff_;
    arguments->maturity_ = maturity_;
    arguments->monitoredTimes_ = monitoredTimes_;
    arguments->averageType_ = averageType_;
}

Money AsianOption::fetchResults(PricingEngine::Results *const res) {
    AsianOption::Results *result = dynamic_cast<AsianOption::Results *>(res);
    //fully create another copy of the results from the pricing engine
    results_ = std::make_shared<AsianOption::Results>(*result);
//    std::cout << results_->price_ << std::endl;
    return results_->price_;
}

