//
// Created by CUI Shidong on 27/6/2016.
//

#ifndef FINANCE_MODEL_H
#define FINANCE_MODEL_H


#include <memory>

class Model {
public:
    class ParameterSet {
    };
};

class BSModel {
public:
    BSModel(double r, double q, double sigma);

    class BSParameterSet : public virtual Model::ParameterSet {
    public:
        BSParameterSet(double r, double q, double sigma);

        double GetRiskFree() const;

        double GetDividend() const;

        double GetVolatility() const;

        double r_;
        double q_;
        double sigma_;
    };

    //std::shared_ptr<BSParameterSet> GetParameterSet();

private:
    std::shared_ptr<Model::ParameterSet> parameterSet_;

};


#endif //FINANCE_MODEL_H
