//
// Created by CUI Shidong on 13/12/2016.
//

#include "MultiRandGenerator.h"

MultiRandGenerator::MultiRandGenerator(std::initializer_list<SingleRandSequenceGenerator> lst) : rsgs_(lst),
                                                                                                 dimension_(0) {
    for (std::initializer_list<SingleRandSequenceGenerator>::iterator iter = lst.begin(); iter != lst.end(); iter++) {
        dimension_ += iter->getDimension();
    }
    sequence_.reserve(dimension_);
}

const vector<double> &MultiRandGenerator::next() {
    sequence_.clear();
    sequence_.reserve(dimension_);
    for (vector<SingleRandSequenceGenerator>::iterator iter = rsgs_.begin(); iter != rsgs_.end(); ++iter) {
        iter->next();
        std::copy(iter->last().begin(), iter->last().end(), std::back_inserter(sequence_));
    }
    return sequence_;
}

