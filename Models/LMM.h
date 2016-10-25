//
// Created by CUI Shidong on 25/10/2016.
//

#ifndef FINANCE_LMM_H
#define FINANCE_LMM_H

#include "Model.h"

class LMM : public ModelND {
public:
    LMM() = default;

    LMM(const std::vector<Quote> &initial, std::vector<Parameter> params_, unsigned long dimensional,
        unsigned long dimStochProcess, Time timeInterval);

private:
    Time timeInterval_;

};


#endif //FINANCE_LMM_H
