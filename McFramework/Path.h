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
    /* full copy of timeGrid is allowed here, which costs little typically */
    Path(const vector<Time> &timeGrid, unsigned long dimensional);

    Path() = default;

    const vector<Time> &getTimeGrid() const;

    vector<vector<Quote> > &getValues();

    const vector<vector<Quote> > &getValues() const;

    virtual vector<vector<Quote> > &getAntitheticValues() { throw ('This path has no antithetic path.'); }

    virtual const vector<vector<Quote> > &getAntitheticValues() const { throw ('This path has no antithetic path.'); }

    virtual ~Path() { }

private:

    vector<Time> timeGrid_;
    unsigned long dimensional_;
    vector<vector<Quote> > vals_;
};

/* no need to use decorator pattern */
class AntitheticPath : public Path {
public:
    AntitheticPath(const vector<Time> &timeGrid, unsigned long dimensional);

    vector<vector<Quote> > &getAntitheticValues() override;

    const vector<vector<Quote> > &getAntitheticValues() const override;

private:
    vector<vector<Quote> > antiVals_;
};



//class Path {
//public:
//    Path(const vector<Time> &timeGrid, const vector<Quote> &values);
//
//    vector<Time> timeGrid_;
//    vector<Quote> values_;
//};


#endif //FINANCE_PATH_H
