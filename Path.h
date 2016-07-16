//
// Created by CUI Shidong on 16/7/2016.
//

#ifndef FINANCE_PATH_H
#define FINANCE_PATH_H

#include <vector>
#include "nameDef.h"

using std::vector;

class Path {
public:
    Path(const vector<Time> &timeGrid, const vector<Quote> &values);

    vector<Time> timeGrid_;
    vector<Quote> values_;
};


#endif //FINANCE_PATH_H