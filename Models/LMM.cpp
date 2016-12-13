//
// Created by CUI Shidong on 25/10/2016.
//

#include "LMM.h"
#include "StochasticProcesses/LogNormalProcess.h"

LMM::LMM(unsigned long dimensional, const std::vector<Quote> &initial, unsigned long dimVol,
         const std::vector<std::shared_ptr<Parameter> > &params, Time tenor):tenor_(tenor) {
    /*!
     * no check for the input */
    dimension_ = dimensional;
    processes_.resize(dimensional);
//    for (std::vector<std::shared_ptr<StochasticProcess> >::iterator iter = processes_.begin(); iter !=
    std::vector<std::shared_ptr<Parameter> >::const_iterator iter = params.begin();

    for (int k = 0; k < dimensional; k++) {
//        iter = params.begin() + k * dimVol;
        std::vector<std::shared_ptr<Parameter> > forthis(iter + k * dimVol, iter + (k + 1) * dimVol);
        processes_[k] = std::shared_ptr<StochasticProcess>(
                new LogNormalProcess(initial[k], std::shared_ptr<Parameter>(new NullParameter()), dimVol, forthis));
    }
}

