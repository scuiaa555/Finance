//
// Created by CUI Shidong on 13/12/2016.
//

#ifndef FINANCE_MULTIRANDGENERATOR_H
#define FINANCE_MULTIRANDGENERATOR_H

#include "SingleRandSequenceGenerator.h"

class MultiRandGenerator {
    MultiRandGenerator(std::initializer_list<SingleRandSequenceGenerator> lst);

    const vector<double> &next();

    const vector<double> &last() const { return sequence_; }


private:
    vector<SingleRandSequenceGenerator> rsgs_;
    vector<double> sequence_;
    unsigned long dimension_;
};

#endif //FINANCE_MULTIRANDGENERATOR_H
