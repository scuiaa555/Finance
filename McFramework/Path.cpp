//
// Created by CUI Shidong on 16/7/2016.
//

#include "Path.h"

Path::Path(const vector<Time> &timeGrid, vector<Time>::size_type N, bool isAntithetic) : timeGrid_(timeGrid),
                                                                                         values_(N),
                                                                                         isAntithetic_(isAntithetic) {
    if (isAntithetic) {
        antitheticValues_.resize(N);
    }
}

vector<Time> &Path::getTimeGrid() {
    return timeGrid_;
}

vector<Quote> &Path::getValues() {
    return values_;
}

vector<Quote> &Path::getAntitheticValues() {
    return antitheticValues_;
}

const vector<Time> &Path::getTimeGrid() const {
    return timeGrid_;
}

const vector<Quote> &Path::getValues() const {
    return values_;
}

const vector<Quote> &Path::getAntitheticValues() const {
    return antitheticValues_;
}

