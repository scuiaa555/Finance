//
// Created by CUI Shidong on 25/10/2016.
//

#ifndef FINANCE_LMM_H
#define FINANCE_LMM_H

#include "Model.h"

class LMM : public ModelND {
public:
    LMM() = default;

    LMM(unsigned long dimensional, const std::vector<Quote> &initial, unsigned long dimVol,
        const std::vector<std::shared_ptr<Parameter> > &params, Time tenorTimeInterval);

    std::vector<Quote> evolve(Time t0, std::vector<Quote> x0, Time dt, double dw) const override { }

private:
    Time timeInterval_;

};


#endif //FINANCE_LMM_H
