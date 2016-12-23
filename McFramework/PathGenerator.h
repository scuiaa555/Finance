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

/**
 * Non-base class which uses a random number generator to generate a path for pricing.
 * The information of path that needs to be generated is stored in its data member model_(shared_ptr).\n
 * @tparam RNG Random number generator (e.g., Single<Normal<>>).
 * @tparam PathType Type of path (SingleVariate or MultiVariate).
 *
 * \e How \e to \e use: \n
 * It cannnot be derived from since it has no virtual member functions, but the RNG type and PathType need to be provided
 * through template arguments and model_(information of model(e.g. LMM)) should be taken in through constructors.
 */
template<typename RNG, typename PathType>
class PathGenerator {
public:
    typedef typename RNG::rng_return_type rng_return_type;          /**< Return type of RNG (double or vector<double>). */
    typedef typename RNG::rng_type rng_type;                        /**< Internal specific type of RNG (e.g. Normal, MultiRandGenerator<Normal<>,Normal<>>). */
    typedef typename RNG::rng_argument_type rng_argument_type;      /**< Argument type for RNG (GenericRandomVariableGenerator::Argument* or vector<GenericRandomVariableGenerator::Argument*>). */
    typedef typename PathType::path_return_type path_return_type;                    /**< Return type of generated path (vector<double> or vector<vector<double>>). */
    typedef typename PathType::type_of_single_time path_return_type_of_single_time;  /**< Return type of path at a single time (double for 1-d, vector<double> for n-d). */

    /**
     * Constructor.
     * @param model Shared_ptr of model.
     * @param timeGrid Vector of monitored times.
     * @param isAntithetic =1 means to calculate antithetic path; =0 not to calculate antithetic path.
     */
    PathGenerator(const std::shared_ptr<Model<path_return_type_of_single_time>> model, const vector<Time> &timeGrid,
                  bool isAntithetic = 0);

    /**
     * Returns a newly-generated path.\n
     * \e Constness: Definitely it is not a const member function, since inside data member next_(shared_ptr) will be changed.
     * Return reference type is const, since logically users cannot modify the path by using this reference.
     * @return Reference of a path.
     */
    const Path<PathType> &next();

private:

    rng_type rng_;        /**< Random number generator(s). */
    std::shared_ptr<Model<path_return_type_of_single_time>> model_;  /**< Shared_ptr of model. */
    /* the generator does not know the exact type of its path */
    std::shared_ptr<Path<PathType>> next_;                           /**< Newly-generated path. */
    bool isAntithetic_;                                              /**< Antithetic variable indicator. */

//    template<typename ArgType>
//    void setRNGs(typename std::enable_if<std::is_same<ArgType, Model::Argument *>::value, Model::Argument *> args);
//
//    template<typename ArgType>
//    void setRNGs(
//            typename std::enable_if<std::is_same<ArgType, vector<Model::Argument *>>::value, vector<Model::Argument *>> args);
};

template<typename RNG, typename PathType>
PathGenerator<RNG, PathType>::PathGenerator(const std::shared_ptr<Model<path_return_type_of_single_time>> model,
                                            const vector<Time> &timeGrid,
                                            bool isAntithetic)
        : rng_(), model_(model), isAntithetic_(isAntithetic) {
//    if (isAntithetic) {
//        next_ = std::shared_ptr<Path>(new AntitheticPath(timeGrid, model->getDimensionality()));
//    } else {
    next_ = std::shared_ptr<Path<PathType>>(new Path<PathType>(timeGrid, model->getDimension()));
//    }
}


template<typename RNG, typename PathType>
const Path<PathType> &PathGenerator<RNG, PathType>::next() {
/**
 * Implementation involves several steps. \n
 * 1. It updates the initial value of path from model_; \n
 * 2. For each time t, model_ set up the arguments needed for the rng_(random number generator; \n
 * 3. rng_ generates a new sequence of random numbers; \n
 * 4. model_ evolves according to the random numbers.
 */
    if (!isAntithetic_) {
        typename PathGenerator<RNG, PathType>::path_return_type::iterator it_value = next_->getValues().begin();
        typename PathGenerator<RNG, PathType>::path_return_type_of_single_time x0 = model_->getInitial();
        *it_value = x0;
        for (vector<Time>::const_iterator it_time = next_->getTimeGrid().begin();
             it_time != next_->getTimeGrid().end() - 1; it_time++) {
            it_value++;
            Time dt = *(it_time + 1) - *it_time;
            model_->setupArgument(*it_time, dt, rng_.getArgument());
            model_->evolve(*it_time, x0, dt, rng_.next(), *it_value);
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
