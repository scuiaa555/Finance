#include <iostream>
#include "Instruments/EuropeanCall.h"
#include "Instruments/Forward.h"
#include "PricingEngines/AnalyticEuropeanEngine.h"
#include "PricingEngines/AnalyticForwardEngine.h"
#include "LEcuyerUniformRNG1.h"

using namespace std;
//using namespace boost;

int main() {
    /*shared_ptr<Payoff> vanillaCallPayoff(new VanillaCallPayoff(95.0));
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
    a = fwd.npv();*/

    LEcuyerUniformRNG1 rng(5);
    rng.SetSeed(100);
    cout << rng.next() << endl;
    cout << rng.next() << endl;


    cout << "Stone, fighting!" << endl;
    return 0;
}