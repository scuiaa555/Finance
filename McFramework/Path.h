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

    virtual const vector<Time> &getTimeGrid() const;

    virtual vector<vector<Quote> > &getValues();

    virtual const vector<vector<Quote> > &getValues() const;

    virtual vector<vector<Quote> > &getAntitheticValues() { throw ("This path has no antithetic path."); }

    virtual const vector<vector<Quote> > &getAntitheticValues() const { throw ("This path has no antithetic path."); }

//    virtual vector<vector<Quote >> &getControlValues() { throw ("This path has no control variable path."); }

//    virtual const vector<vector<Quote >> &getControlValues() const { throw ("This path has no control variable path."); }

    virtual ~Path() { }

private:
    vector<Time> timeGrid_;
    unsigned long dimensional_;
    vector<vector<Quote> > vals_;
};

/* decorator pattern */
class PathDecorator : public Path {
public:
    PathDecorator() = default;

    PathDecorator(std::unique_ptr<Path> &&innerPath) : innerPath_(std::move(innerPath)) { }

protected:
    std::unique_ptr<Path> innerPath_;
};

class AntitheticPath : public PathDecorator {
public:
    AntitheticPath(const vector<Time> &timeGrid, unsigned long dimensional);

    vector<vector<Quote> > &getAntitheticValues() override;

    const vector<vector<Quote> > &getAntitheticValues() const override;

    vector<vector<Quote> > &getValues() override;

    const vector<vector<Quote> > &getValues() const override;

    const vector<Time> &getTimeGrid() const override;

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
