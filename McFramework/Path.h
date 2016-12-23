//
// Created by CUI Shidong on 16/7/2016.
//

#ifndef FINANCE_PATH_H
#define FINANCE_PATH_H

#include <vector>
#include "NameDef.h"

using std::vector;

/**
 * PathType for models of 1-d(e.g. Black-Scholes model for single stock).
 * A template trait for determining the path type which is composed of type of single path(vector<double>) and type of single path at single time(double).
 */
struct SingleVariate {
    typedef vector<double> path_return_type;  /**< Type of single path for single variable. */
    typedef double type_of_single_time;       /**< Type of single path for single vatiable at single time point. */
};

/**
 * PathType for models of multi-dimension(e.g. LMM).
 * A template trait for determining the path type which is composed of type of multiple paths(vector<vector<double>>) and type of multiple paths at single time(vector<double>).
 */
struct MultiVariate {
    typedef vector<vector<double>> path_return_type;  /**< Type of single path for multi variables. */
    typedef vector<double> type_of_single_time;       /**< Type of single path for multi vatiables at single time point. */
};

/**
 * Base class for a single path.
 * This Path class simply stores the information(e.g. time grid, stock price...) of a single path.
 * @tparam PathType Type of path(SingleVariate or MultiVariate).
 *
 * \e How \e to \e use: \n
 * The path with antithetic path or control variable path will be derived from this class by using decorator pattern. @todo
 */
template<typename PathType=SingleVariate>
class Path {
public:

    typedef typename PathType::path_return_type path_return_type;   /**< Type of single path for PathType. */

    /**
     * Constructor.
     * @param timeGrid Vector of time grid.
     * @param dimensional Dimension of a single path(i.e., 1 for SingleVariate, >1 for MultiVariate).
     */
    Path(const vector<Time> &timeGrid, unsigned long dimension);  /* full copy of timeGrid is allowed here, which costs little typically */

    Path() = default;

    /**
     * Return the vector of time grid.
     * @return Vector of time grid.
     */
    virtual const vector<Time> &getTimeGrid() const;

    /**
     * Return the values of path.
     * @return Vector of values of a single path.
     */
    virtual path_return_type &getValues();

    /**
     * Return the values of path.
     * \e Constness: There are two overloaded versions of this method in this class distinguished by constness. The const
     * member function prohibits the change of data member inside the function and only can call other const member function.
     * Const object can call const member function, where normal object can call both const and non-const member functions.
     * Two versions facilitates the call by both const object and non-const object.
     * @return Vector of values of a single path.
     */
    virtual const path_return_type &getValues() const;

//    virtual path_return_type &getAntitheticValues() { throw ("This path has no antithetic path."); }

//    virtual const path_return_type &getAntitheticValues() const { throw ("This path has no antithetic path."); }

//    virtual vector<vector<Quote >> &getControlValues() { throw ("This path has no control variable path."); }

//    virtual const vector<vector<Quote >> &getControlValues() const { throw ("This path has no control variable path."); }

    virtual ~Path() {}

private:
    vector<Time> timeGrid_;    /**< Vector of time grid. */
    unsigned long dimension_;  /**< Dimension of a single path. */
    path_return_type vals_;    /**< Vector of values of a single path. */

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
Path<PathType>::Path(const vector<Time> &timeGrid, unsigned long dimension) : timeGrid_(timeGrid),
                                                                                dimension_(dimension) {
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
