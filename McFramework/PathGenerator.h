//
// Created by CUI Shidong on 16/7/2016.
//

#ifndef FINANCE_PATHGENERATOR_H
#define FINANCE_PATHGENERATOR_H

#include "RandNumGeneration/NormalMarsagliaBrayRng.h"
#include "McFramework/Path.h"
#include "Model.h"

template<typename NormRNG>
class PathGenerator {
public:
    PathGenerator(const std::shared_ptr<Model> model, const vector<Time> &timeGrid,
                  bool isAntithetic = 0);

    Path &next();

private:
    NormRNG normalRng_;
    std::shared_ptr<Model> model_;
    /* the generator does not know the exact type of its path */
    std::shared_ptr<Path> next_;
    bool isAntithetic_;
};

template<typename NormRNG>
PathGenerator<NormRNG>::PathGenerator(const std::shared_ptr<Model> model, const vector<Time> &timeGrid,
                                      bool isAntithetic)
        : model_(model), normalRng_(), isAntithetic_(isAntithetic) {
    if (isAntithetic) {
        /*!!! dimension problem appeared here
         *!!! should be implied by process/pathPricer */
//        next_ = std::dynamic_pointer_cast<Path>(std::shared_ptr<AntitheticPath>(new AntitheticPath(timeGrid, 1)));
        next_ = std::shared_ptr<Path>(new AntitheticPath(timeGrid, 1));
    }
    else {
        next_ = std::shared_ptr<Path>(new Path(timeGrid, 1));
    }
}

template<typename NormRNG>
Path &PathGenerator<NormRNG>::next() {
    if (!isAntithetic_) {
        vector<vector<Quote> >::iterator it_value = next_->getValues().begin();
        vector<Quote> x0 = model_->getInitial();
        *it_value = x0;
        for (vector<Time>::const_iterator it_time = next_->getTimeGrid().begin();
             it_time != next_->getTimeGrid().end() - 1; it_time++) {
            it_value++;
            Time dt = *(it_time + 1) - *it_time;
            double dw = normalRng_.next() * sqrt(dt);
            *it_value = model_->evolve(*it_time, x0, dt, dw);
            x0 = *it_value;
        }
    }
    else {
        vector<vector<Quote> >::iterator it_value = next_->getValues().begin();
        vector<vector<Quote> >::iterator it_anti_value = next_->getAntitheticValues().begin();
        vector<Quote> x0_val = model_->getInitial();
        vector<Quote> x0_antiVal = x0_val;
        *it_value = x0_val;
        *it_anti_value = x0_antiVal;
        for (vector<Time>::const_iterator it_time = next_->getTimeGrid().begin();
             it_time != next_->getTimeGrid().end() - 1; it_time++) {
            it_value++;
            it_anti_value++;
            Time dt = *(it_time + 1) - *it_time;
            double dw = normalRng_.next() * sqrt(dt);
            *it_value = model_->evolve(*it_time, x0_val, dt, dw);
            *it_anti_value = model_->evolve(*it_time, x0_antiVal, dt, -dw);
            x0_val = *it_value;
            x0_antiVal = *it_anti_value;
        }
    }
    return *next_;
}


#endif //FINANCE_PATHGENERATOR_H
