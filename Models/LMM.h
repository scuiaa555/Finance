//
// Created by CUI Shidong on 25/10/2016.
//

#ifndef FINANCE_LMM_H
#define FINANCE_LMM_H

#include "Model.h"

/*! \brief Standard LMM model.
 *
 * This is the most standard Libor market model before financial crisis.
 * The log-normal processes without stochastic multipliers are imposed in the dynamics of the LMM model.
 *
 */

class LMM : public ModelND {
public:
    LMM() = default;

    /**
     * @param dimension: number of (riskfree) forward rates
     * @param initial: initial value at time 0
     * @param dimVol: volatility dimension of each dynamic
     * @param params: vector of needed parameters structure
     * @param tenor: tenor of forward rates, e.g. 1M(1/12), 3M(1/4), 6M(1/2), 12M(1)
     */
    LMM(unsigned long dimension, const std::vector<Quote> &initial, unsigned long dimVol,
        const std::vector<std::shared_ptr<Parameter> > &params, Time tenor);

    std::vector<Quote> evolve(Time t0, std::vector<Quote>& x0, Time dt, double dw) const override { }

private:
//    unsigned long dimension_
    Time tenor_;

};


#endif //FINANCE_LMM_H
