//
// Created by CUI Shidong on 16/7/2016.
//

#include "PathGenerator.h"

PathGenerator::PathGenerator(const std::shared_ptr<StochasticProcess> process, const vector<Time> &timeGrid) : process_(
        process), normalRng_(), next_(timeGrid, vector<double>(timeGrid.size())) { }

Path &PathGenerator::next() {
    vector<Quote>::iterator it_value = next_.values_.begin();
    Quote x0 = process_->x0_;
    *it_value = x0;
    for (vector<Time>::const_iterator it_time = next_.timeGrid_.begin();
         it_time != next_.timeGrid_.end() - 1; it_time++) {
        it_value++;
        Time dt = *(it_time + 1) - *it_time;
        double dw = normalRng_.next() * sqrt(dt);
        *it_value = process_->evolve(*it_time, x0, dt, dw);
        x0 = *it_value;
    }
    return next_;
}


