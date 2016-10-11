//
// Created by CUI Shidong on 16/7/2016.
//

#ifndef FINANCE_PATH_H
#define FINANCE_PATH_H

#include <vector>
#include "nameDef.h"

using std::vector;

class Path {
//    Path(const vector<Time>&timeGrid, const vector<Quete>)
//private:
public:
    Path(const vector<Time> &timeGrid, vector<Time>::size_type N, bool isAntithetic = 0);

    vector<Time> &getTimeGrid();

    vector<Quote> &getValues();

    vector<Quote> &getAntitheticValues();

    const vector<Time> &getTimeGrid() const;

    const vector<Quote> &getValues() const;

    const vector<Quote> &getAntitheticValues() const;

private:

    vector<Time> timeGrid_;
    vector<Quote> values_;
    vector<Quote> antitheticValues_;
    bool isAntithetic_;
};

//class Path {
//public:
//    Path(const vector<Time> &timeGrid, const vector<Quote> &values);
//
//    vector<Time> timeGrid_;
//    vector<Quote> values_;
//};


#endif //FINANCE_PATH_H
