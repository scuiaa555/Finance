//
// Created by CUI Shidong on 16/7/2016.
//

#ifndef FINANCE_PATHPRICER_H
#define FINANCE_PATHPRICER_H

#include "NameDef.h"
#include "McFramework/Path.h"
//#include "Payoff.h"

/**
 * Base class for path pricers.
 * Any path pricers(e.g. McEuropeanPathPricer, AnalyticEuropeanPathPricer) will derive from this class.
 * @tparam PathType Path type that is consistent with the path pricer.
 *
 * \e How \e to \e use: \n
 * The derived class should know the exact path type that is needed. Also, it should implement the pure virtual operator()
 * which does the calculations of pricing based on a single path.
 */
template<typename PathType>
class PathPricer {
public:

    /**
     * Price on a single path.
     * @param path A single path that needs to be priced.
     * @return Price after calculations.
     */
    virtual Money operator()(const Path<PathType> &path) const = 0;

//private:
//    bool isAntithetic_;
};

//EuropeanPathPricer::EuropeanPathPricer(const std::shared_ptr<Payoff> &payoff, Rate discount) : payoff_(payoff),

//Money EuropeanPathPricer::operator()(const Path &path) const {
//    Money price;
////    price=path.values_.back();
//    price = payoff_->getPayoff(path.values_.back()) * discount_;
//    return price;
//}

#endif //FINANCE_PATHPRICER_H
