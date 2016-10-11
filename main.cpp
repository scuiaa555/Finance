#include <iostream>
#include "Instruments/EuropeanOption.h"
#include "StochasticProcess.h"
#include "Instruments/AsianOption.h"
#include "PricingEngines/McAsianEngine.h"
//#include <armadillo>

using namespace std;
//using namespace arma;
//using namespace boost;

int main() {

    double a, a1, a2;
    shared_ptr<Payoff> vanillaPayoff(new VanillaPayoff(95.0, "put"));
    shared_ptr<BSModel> bsModel(new BSModel(0.05, 0.0, 0.3, 100));
    shared_ptr<BlackScholesProcess> bsProcess(new BlackScholesProcess(bsModel));
    AsianOption asian(1.0, vanillaPayoff, 0.1, AsianOption::AverageType::geometric);
    shared_ptr<McAsianEngine<> > pricingAsianEngine(new McAsianEngine<>(bsProcess, 0.01, 20000, 1000,1));
    asian.setPricingEngine(pricingAsianEngine);
    a = asian.npv();


//    EuropeanOption call(1.0, vanillaPayoff);
//
//
//
//    shared_ptr<McEuropeanEngine<>> pricingEngine(new McEuropeanEngine<>(bsProcess, 1, 200000, 10000));
//    call.setPricingEngine(pricingEngine);
//    a1 = call.npv();
//
//    shared_ptr<AnalyticEuropeanEngine> pricingEngine2(new AnalyticEuropeanEngine(bsModel));
//
//    call.setPricingEngine(pricingEngine2);
//    a2 = call.npv();


//    a = bsProcess->evolve(0, 100, 0.1, 0.2);
//    vector<double> v1{1.0, 2.0, 3.0};
//    vector<double> v2(3, 2.0);
//    v2[2] = 102;
//    Path path(v1, v2);
//    path.timeGrid_[0] = 2.5;
//
//    shared_ptr<EuropeanPathPricer> europeanPathPricer(new EuropeanPathPricer(vanillaCallPayoff, 1.0));
////    a = (*europeanPathPricer)(path);
//
//    shared_ptr<PathGenerator<NormalMarsagliaBrayRng<UniformLEcuyerRNG1>>> pathGenerator(
//            new PathGenerator<NormalMarsagliaBrayRng<UniformLEcuyerRNG1>>(bsProcess, v1));
//    pathGenerator->next();
//    McModel mcModel(pathGenerator, europeanPathPricer);
//    mcModel.addSamples(10);
//    a = mcModel.getStatistics().mean();


//    BSModel bs(1, 2, 3, 4);

//    double b = call.results_->delta_;

//    Forward fwd(1.0, 100, 100);
//    shared_ptr<AnalyticForwardEngine> pricingFwd(new AnalyticForwardEngine(0.02));
//    fwd.SetPricingEngine(pricingFwd);
//    a = fwd.npv();

//    UniformLEcuyerRNG1 rng(5);
//    rng.setSeed(100);
////    cout << rng.next() << endl;
////    cout << rng.next() << endl;
//    RandomSequenceGenerator<UniformLEcuyerRNG1> rsg(5, rng);
////    RandomSequenceGenerator rsg(5, rng);
//    vector<double> a(rsg.nextSequence());
//    a[0] = 1;
//
//    NormalMarsagliaBrayRng<UniformLEcuyerRNG1> rngNormal;
//    for (int i = 0; i < 15; i++)
//        cout << rngNormal.next() << endl;
////    cout << rngNormal.next() << endl;
//    RandomSequenceGenerator<NormalMarsagliaBrayRng<UniformLEcuyerRNG1> > rsg2(5, rngNormal);
//    vector<double> b(rsg2.nextSequence());

    cout << "Stone, fighting!" << endl;
    return 0;
}