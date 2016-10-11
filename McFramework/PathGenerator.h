//
// Created by CUI Shidong on 16/7/2016.
//

#ifndef FINANCE_PATHGENERATOR_H
#define FINANCE_PATHGENERATOR_H

#include "RandNumGeneration/NormalMarsagliaBrayRng.h"
#include "McFramework/Path.h"
#include "StochasticProcess.h"

template<typename NormRNG>
class PathGenerator {
public:
    PathGenerator(const std::shared_ptr<StochasticProcess> process, const vector<Time> &timeGrid,
                  bool isAntithetic = 0);

    Path &next();

private:
    NormRNG normalRng_;
    std::shared_ptr<StochasticProcess> process_;
    Path next_;
    bool isAntithetic_;

};

template<typename NormRNG>
PathGenerator<NormRNG>::PathGenerator(const std::shared_ptr<StochasticProcess> process, const vector<Time> &timeGrid,
                                      bool isAntithetic)
        : process_(process), normalRng_(), next_(timeGrid, timeGrid.size(),isAntithetic), isAntithetic_(isAntithetic) { }

template<typename NormRNG>
Path &PathGenerator<NormRNG>::next() {
    if (!isAntithetic_) {
        vector<Quote>::iterator it_value = next_.getValues().begin();
        Quote x0 = process_->x0_;
        *it_value = x0;
        for (vector<Time>::const_iterator it_time = next_.getTimeGrid().begin();
             it_time != next_.getTimeGrid().end() - 1; it_time++) {
            it_value++;
            Time dt = *(it_time + 1) - *it_time;
            double dw = normalRng_.next() * sqrt(dt);
            *it_value = process_->evolve(*it_time, x0, dt, dw);
            x0 = *it_value;
        }
    }
    else {
        vector<Quote>::iterator it_value = next_.getValues().begin();
        vector<Quote>::iterator it_anti_value = next_.getAntitheticValues().begin();
        Quote x0_val = process_->x0_;
        Quote x0_antiVal = x0_val;
        *it_value = x0_val;
        *it_anti_value = x0_antiVal;
        for (vector<Time>::const_iterator it_time = next_.getTimeGrid().begin();
             it_time != next_.getTimeGrid().end() - 1; it_time++) {
            it_value++;
            it_anti_value++;
            Time dt = *(it_time + 1) - *it_time;
            double dw = normalRng_.next() * sqrt(dt);
            *it_value = process_->evolve(*it_time, x0_val, dt, dw);
            *it_anti_value = process_->evolve(*it_time, x0_antiVal, dt, -dw);
            x0_val = *it_value;
            x0_antiVal = *it_anti_value;
        }
    }
    return next_;
}


#endif //FINANCE_PATHGENERATOR_H
