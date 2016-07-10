#include <iostream>

//#include "payoff.h"
#include "Instruments/EuropeanCall.h"
#include "Instruments/Forward.h"
#include "PricingEngines/AnalyticEuropeanEngine.h"
#include "PricingEngines/AnalyticForwardEngine.h"
//#include <boost>
//#include "boost/align.hpp"

using namespace std;
//using namespace boost;

int main() {
    shared_ptr<Payoff> vanillaCallPayoff(new VanillaCallPayoff(95.0));
    EuropeanCall call(1.0, vanillaCallPayoff);

    shared_ptr<BSModel> bsModel(new BSModel(0.05, 0.01, 0.3, 100));
//    BSModel bs(1, 2, 3, 4);
    shared_ptr<AnalyticEuropeanEngine> pricingEngine(new AnalyticEuropeanEngine(bsModel));

    call.SetPricingEngine(pricingEngine);
    double a = call.npv();
    double b = call.results_->delta_;

    Forward fwd(1.0, 100, 100);
    shared_ptr<AnalyticForwardEngine> pricingFwd(new AnalyticForwardEngine(0.02));
    fwd.SetPricingEngine(pricingFwd);
    a = fwd.npv();

    cout << "Stone, fighting!" << endl;
    return 0;
}