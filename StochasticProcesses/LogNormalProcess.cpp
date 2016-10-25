//
// Created by CUI Shidong on 25/10/2016.
//

#include "LogNormalProcess.h"

LogNormalProcess::LogNormalProcess(Quote x0, const std::shared_ptr<Parameter> &drift, unsigned long dimVol,
                                   const std::vector<std::shared_ptr<Parameter> > &volatility)
        : x0_(x0), drift_(drift), dimVol_(dimVol), volatility_(volatility) { }

Quote LogNormalProcess::getSpot() const {
    return x0_;
}



