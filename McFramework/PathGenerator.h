//
// Created by CUI Shidong on 16/7/2016.
//

#ifndef FINANCE_PATHGENERATOR_H
#define FINANCE_PATHGENERATOR_H

#include "RandNumGeneration/NormalMarsagliaBrayRng.h"
#include "McFramework/Path.h"
#include "Model.h"
#include "RandNumGeneration/MultiRandGenerator.h"
#include <type_traits>

template<typename RNG>
class PathGenerator {
public:
    typedef typename RNG::rng_return_type rng_return_type;
    typedef typename RNG::rng_type rng_type;
    typedef typename RNG::rng_argument_type rng_argument_type;

    PathGenerator(const std::shared_ptr<Model> model, const vector<Time> &timeGrid,
                  bool isAntithetic = 0);

    Path &next();

private:
    rng_type rng_;
    std::shared_ptr<Model> model_;
    /* the generator does not know the exact type of its path */
    std::shared_ptr<Path> next_;
    bool isAntithetic_;

//    template<typename ArgType>
//    void setRNGs(typename std::enable_if<std::is_same<ArgType, Model::Argument *>::value, Model::Argument *> args);
//
//    template<typename ArgType>
//    void setRNGs(
//            typename std::enable_if<std::is_same<ArgType, vector<Model::Argument *>>::value, vector<Model::Argument *>> args);
};

template<typename RNG>
PathGenerator<RNG>::PathGenerator(const std::shared_ptr<Model> model, const vector<Time> &timeGrid,
                                  bool isAntithetic)
        : rng_(), model_(model), isAntithetic_(isAntithetic) {
//    typename RNG::rng_argument_type arg;
//    setRNGs<typename RNG::rng_argument_type>(arg);
    if (isAntithetic) {
//        /*!!! dimension problem appeared here
//         *!!! should be implied by process/pathPricer */
        next_ = std::shared_ptr<Path>(new AntitheticPath(timeGrid, model->getDimensionality()));
    } else {
        next_ = std::shared_ptr<Path>(new Path(timeGrid, model->getDimensionality()));
    }
}

template<typename RNG>
Path &PathGenerator<RNG>::next() {
    if (!isAntithetic_) {
        vector<vector<Quote> >::iterator it_value = next_->getValues().begin();
        vector<Quote> x0 = model_->getInitial();
        *it_value = x0;
        for (vector<Time>::const_iterator it_time = next_->getTimeGrid().begin();
             it_time != next_->getTimeGrid().end() - 1; it_time++) {
            it_value++;
            Time dt = *(it_time + 1) - *it_time;
            model_->setupArgument(*it_time, dt, rng_.getArgument());
            *it_value = model_->evolve(*it_time, x0, dt, rng_.next());
            x0 = *it_value;
        }
    }
//    else {
//        vector<vector<Quote> >::iterator it_value = next_->getValues().begin();
//        vector<vector<Quote> >::iterator it_anti_value = next_->getAntitheticValues().begin();
//        vector<Quote> x0_val = model_->getInitial();
//        vector<Quote> x0_antiVal = x0_val;
//        *it_value = x0_val;
//        *it_anti_value = x0_antiVal;
//        for (vector<Time>::const_iterator it_time = next_->getTimeGrid().begin();
//             it_time != next_->getTimeGrid().end() - 1; it_time++) {
//            it_value++;
//            it_anti_value++;
//            Time dt = *(it_time + 1) - *it_time;
//            return_type dw = rng_.next() * sqrt(dt);
//            *it_value = model_->evolve(*it_time, x0_val, dt, dw);
//            *it_anti_value = model_->evolve(*it_time, x0_antiVal, dt, -dw);
//            x0_val = *it_value;
//            x0_antiVal = *it_anti_value;
//        }
//    }
    return *next_;
}

//template<typename RNG>
//void PathGenerator<RNG>::setRNGs() {
//    typename RNG::rng_argument_type arguments;
//
//}


#endif //FINANCE_PATHGENERATOR_H
