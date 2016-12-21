//
// Created by CUI Shidong on 16/7/2016.
//

#ifndef FINANCE_PATH_H
#define FINANCE_PATH_H

#include <vector>
#include "NameDef.h"

using std::vector;

struct SingleVariate {
    typedef vector<double> path_return_type;
    typedef double type_of_single_time;
};

struct MultiVariate {
    typedef vector<vector<double>> path_return_type;
    typedef vector<double> type_of_single_time;
};

template<typename PathType=SingleVariate>
class Path {
//    Path(const vector<Time>&timeGrid, const vector<Quete>)
//private:
public:

    typedef typename PathType::path_return_type path_return_type;

    /* full copy of timeGrid is allowed here, which costs little typically */
    Path(const vector<Time> &timeGrid, unsigned long dimensional);

    Path() = default;

    virtual const vector<Time> &getTimeGrid() const;

    virtual path_return_type &getValues();

    virtual const path_return_type &getValues() const;

//    virtual path_return_type &getAntitheticValues() { throw ("This path has no antithetic path."); }

//    virtual const path_return_type &getAntitheticValues() const { throw ("This path has no antithetic path."); }

//    virtual vector<vector<Quote >> &getControlValues() { throw ("This path has no control variable path."); }

//    virtual const vector<vector<Quote >> &getControlValues() const { throw ("This path has no control variable path."); }

    virtual ~Path() {}

private:
    vector<Time> timeGrid_;
    unsigned long dimensional_;
    path_return_type vals_;
};

/* Antithetic part */
//* decorator pattern */
//class PathDecorator : public Path {
//public:
//    PathDecorator() = default;
//
//    PathDecorator(std::unique_ptr<Path> &&innerPath) : innerPath_(std::move(innerPath)) {}
//
//protected:
//    std::unique_ptr<Path> innerPath_;
//};
//
//class AntitheticPath : public PathDecorator {
//public:
//    AntitheticPath(const vector<Time> &timeGrid, unsigned long dimensional);
//
//    vector<vector<Quote> > &getAntitheticValues() override;
//
//    const vector<vector<Quote> > &getAntitheticValues() const override;
//
//    vector<vector<Quote> > &getValues() override;
//
//    const vector<vector<Quote> > &getValues() const override;
//
//    const vector<Time> &getTimeGrid() const override;
//
//private:
//    vector<vector<Quote> > antiVals_;
//};

//class Path {
//public:
//    Path(const vector<Time> &timeGrid, const vector<Quote> &values);
//
//    vector<Time> timeGrid_;
//    vector<Quote> values_;
//};

template<typename PathType>
Path<PathType>::Path(const vector<Time> &timeGrid, unsigned long dimensional) : timeGrid_(timeGrid),
                                                                                dimensional_(dimensional) {
    vals_.resize(timeGrid.size());
}

//AntitheticPath::AntitheticPath(const vector<Time> &timeGrid, unsigned long dimensional) :
//        PathDecorator(std::unique_ptr<Path>(new Path(timeGrid, dimensional))) {
//    antiVals_.resize(timeGrid.size(), vector<Quote>(dimensional));
//}

//
//Path::Path(const vector<Time> &timeGrid, vector<Time>::size_type N, bool isAntithetic) : timeGrid_(timeGrid),
//                                                                                         values_(N),
//                                                                                         isAntithetic_(isAntithetic) {
//    if (isAntithetic) {
//        antitheticValues_.resize(N);
//    }
//}
//
template<typename PathType>
const vector<Time> &Path<PathType>::getTimeGrid() const {
    return timeGrid_;
}

template<typename PathType>
typename Path<PathType>::path_return_type &Path<PathType>::getValues() {
    return vals_;
}

template<typename PathType>
const typename Path<PathType>::path_return_type &Path<PathType>::getValues() const {
    return vals_;
}

//vector<vector<Quote >> &AntitheticPath::getValues() {
//    return innerPath_->getValues();
//}
//
//const vector<vector<Quote> > &AntitheticPath::getValues() const {
//    return innerPath_->getValues();
//}
//
//const vector<Time> &AntitheticPath::getTimeGrid() const {
//    return innerPath_->getTimeGrid();
//}
//
//vector<vector<Quote> > &AntitheticPath::getAntitheticValues() {
//    return antiVals_;
//}
//
//const vector<vector<Quote> > &AntitheticPath::getAntitheticValues() const {
//    return antiVals_;
//}

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


#endif //FINANCE_PATH_H
