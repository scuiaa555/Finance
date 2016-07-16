#include <iostream>
#include "Instruments/EuropeanCall.h"
#include "Instruments/Forward.h"
#include "PricingEngines/AnalyticEuropeanEngine.h"
#include "PricingEngines/AnalyticForwardEngine.h"
#include "RandNumGeneration/RandomSequenceGenerator.h"
#include "RandNumGeneration/NormalMarsagliaBrayRng.h"
#include "StochasticProcess.h"
#include "PathGenerator.h"
#include "PathPricer.h"

using namespace std;
//using namespace boost;

int main() {
    double a;
    shared_ptr<Payoff> vanillaCallPayoff(new VanillaCallPayoff(95.0));
    EuropeanCall call(1.0, vanillaCallPayoff);

    shared_ptr<BSModel> bsModel(new BSModel(0.05, 0.01, 0.3, 100));
    shared_ptr<BlackScholesProcess> bsProcess(new BlackScholesProcess(0.05, 0.01, 0.3, 100));
    a = bsProcess->evolve(0, 100, 0.1, 0.2);
    vector<double> v1{1.0, 2.0, 3.0};
    vector<double> v2(3, 2.0);
    v2[2] = 102;
    Path path(v1, v2);
    path.timeGrid_[0] = 2.5;

    EuropeanPathPricer europeanPathPricer(vanillaCallPayoff, 1.0);
    a = europeanPathPricer(path);

    PathGenerator<NormalMarsagliaBrayRng<UniformLEcuyerRNG1>> pathGenerator(bsProcess, v1);
    pathGenerator.next();

//    BSModel bs(1, 2, 3, 4);
    shared_ptr<AnalyticEuropeanEngine> pricingEngine(new AnalyticEuropeanEngine(bsModel));

    call.SetPricingEngine(pricingEngine);
    a = call.npv();
    double b = call.results_->delta_;

    Forward fwd(1.0, 100, 100);
    shared_ptr<AnalyticForwardEngine> pricingFwd(new AnalyticForwardEngine(0.02));
    fwd.SetPricingEngine(pricingFwd);
    a = fwd.npv();

/*
    UniformLEcuyerRNG1 rng(5);
    rng.SetSeed(100);
//    cout << rng.next() << endl;
//    cout << rng.next() << endl;
    RandomSequenceGenerator<UniformLEcuyerRNG1> rsg(5, rng);
//    RandomSequenceGenerator rsg(5, rng);
    vector<double> a(rsg.nextSequence());
    a[0] = 1;

    NormalMarsagliaBrayRng<UniformLEcuyerRNG1> rngNormal;
    for (int i = 0; i < 15; i++)
        cout << rngNormal.next() << endl;
//    cout << rngNormal.next() << endl;
    RandomSequenceGenerator<NormalMarsagliaBrayRng<UniformLEcuyerRNG1> > rsg2(5, rngNormal);
    vector<double> b(rsg2.nextSequence());
*/

    cout << "Stone, fighting!" << endl;
    return 0;
}