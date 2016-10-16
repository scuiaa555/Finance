//
// Created by CUI Shidong on 16/7/2016.
//

#include "Path.h"

Path::Path(const vector<Time> &timeGrid, unsigned long dimensional) : timeGrid_(timeGrid), dimensional_(dimensional) {
    vals_.resize(timeGrid.size(), vector<Quote>(dimensional));
}

AntitheticPath::AntitheticPath(const vector<Time> &timeGrid, unsigned long dimensional) : Path(timeGrid, dimensional) {
    antiVals_.resize(timeGrid.size(), vector<Quote>(dimensional));
}

//
//Path::Path(const vector<Time> &timeGrid, vector<Time>::size_type N, bool isAntithetic) : timeGrid_(timeGrid),
//                                                                                         values_(N),
//                                                                                         isAntithetic_(isAntithetic) {
//    if (isAntithetic) {
//        antitheticValues_.resize(N);
//    }
//}
//
const vector<Time> &Path::getTimeGrid() const {
    return timeGrid_;
}

vector<vector<Quote> > &Path::getValues() {
    return vals_;
}

const vector<vector<Quote> > &Path::getValues() const {
    return vals_;
}

vector<vector<Quote> > &AntitheticPath::getAntitheticValues() {
    return antiVals_;
}

const vector<vector<Quote> > &AntitheticPath::getAntitheticValues() const {
    return antiVals_;
}

//const vector<Time> &Path::getTimeGrid() const {
//    return timeGrid_;
//}
//
//const vector<Quote> &Path::getValues() const {
//    return values_;
//}
//
//const vector<Quote> &Path::getAntitheticValues() const {
//    return antitheticValues_;
//}
//
