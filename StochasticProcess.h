//
// Created by CUI Shidong on 27/6/2016.
//

#ifndef FINANCE_MODEL_H
#define FINANCE_MODEL_H


#include <memory>
#include "NameDef.h"
#include "Parameter.h"

using std::shared_ptr;

class StochasticProcess {
public:
    class ParameterSet {
    };

    virtual Quote getSpot() const = 0;

    virtual ~StochasticProcess() {}
};

//class JumpComponent {
//public:
//    virtual ~JumpComponent() {}
//};
//
//class JumpDiffusionProcess : public StochasticProcess {
//protected:
//    shared_ptr<JumpComponent> jumpComponent_;
//};

#endif //FINANCE_MODEL_H
