#include <iostream>

//#include "payoff.h"
#include "Option.h"
#include "AnalyticEuropeanEngine.h"

using namespace std;

int main() {
    shared_ptr<Payoff> vanillaCallPayoff(new VanillaCallPayoff(5.0));
    EuropeanCall call(1.0, vanillaCallPayoff);

    shared_ptr<BSModel> bsModel(new BSModel(0.05, 0.01, 0.3));
    shared_ptr<AnalyticEuropeanEngine> pricingEngine(new AnalyticEuropeanEngine(bsModel));

    call.SetPricingEngine(pricingEngine);
    call.npv();

/*    call.SetPricingEngine(pricingEngine);
    double p = call.npv();


    cout << call.GetMaturity() << endl;*/
    //cout << payoff << endl;


    cout << "Stone, fighting!" << endl;
    return 0;
}