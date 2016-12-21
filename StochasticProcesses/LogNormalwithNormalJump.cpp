//
// Created by CUI Shidong on 20/12/2016.
//

#include "LogNormalwithNormalJump.h"

LogNormalWithNormalJump::LogNormalWithNormalJump(Quote x0, const shared_ptr<Parameter> &drift, unsigned long dimVol,
                                                 const std::vector<shared_ptr<Parameter> > &volatility,
                                                 const shared_ptr<Parameter> jumpMean,
                                                 const shared_ptr<Parameter> jumpVariance)
        : drift_(drift),
          dimVol_(dimVol),
          volatility_(volatility),
          jumpMean_(jumpMean),
          jumpVariance_(jumpVariance) {}

