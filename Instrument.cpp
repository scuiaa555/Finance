//
// Created by CUI Shidong on 26/6/2016.
//

#include "Instrument.h"
#include <iostream>
//#include "PricingEngine.h"
//#include "Payoff.h"

using std::shared_ptr;

void Instrument::setPricingEngine(const std::shared_ptr<PricingEngine> pricingEngine) {
    pricingEngine_ = pricingEngine;
}

/* template pattern */
Money Instrument::npv() {
    //give option exercise to pricing engine
    //pricingEngine_->getArguments(arguments);
    //SetupArguments(pricingEngine_->arguments_);
//    pricingEngine_->validate();
    setupArguments(pricingEngine_->getArguments());

    /* let pricing engine to the calculations */
    pricingEngine_->calculate();

    /* fetch the results back to the option */
    return fetchResults(pricingEngine_->getResults());

}

///*
//EuropeanCall::EuropeanCall(Time maturity, Quote strike) : maturity_(maturity) {
//    payoff_ = shared_ptr<Payoff>(new VanillaCallPayoff(strike));
//}
//
//EuropeanCall::EuropeanCall(Time maturity, std::shared_ptr<Payoff> payoff) :
//        maturity_(maturity), payoff_(payoff) { }
//
//void EuropeanCall::SetupArguments(PricingEngine::Arguments *arg) const {
//    EuropeanCall::Arguments *arguments;
//    arguments = dynamic_cast<EuropeanCall::Arguments *>(arg);
//    arguments->payoff_ = payoff_;
//    arguments->maturity_ = maturity_;
//}
//
//Money EuropeanCall::FetchResults(PricingEngine::Results *const res) {
//    EuropeanCall::Results *result = dynamic_cast<EuropeanCall::Results *>(res);
//    //fully create another copy of the results from the pricing engine
//    results_ = std::make_shared<EuropeanCall::Results>(*result);
//    std::cout << results_->price_ << std::endl;
//    return results_->price_;
//}
//*/
//
//
//
//
//
//
//
//
///*
// * Time EuropeanCall::GetMaturity() const {
//    return Maturity_;
//}*/
//
///*void Option::Calculate() {
//    pricingEngine_->calculate();
//}*/
//
///*
//Money Option::npv() {
//    getArguments();
//    Calculate();
//    //FetchResults();
//}*/
//
////class Option::Arguments : public PricingEngine::Arguments {
////public:
////    double a;
////};
//
///*class EuropeanCall::EuropeanCallArguments : public Option::Arguments {
//public:
//    EuropeanCallArguments(std::string type, std::shared_ptr<Payoff> payoff);
//
//    std::string type_;
//    std::shared_ptr<Payoff> payoff_;
//};*/
//
///*
//
//EuropeanCall::EuropeanCallArguments::EuropeanCallArguments(std::string type, std::shared_ptr<Payoff> payoff) :
//        type_(type), payoff_(payoff) { }
//
//void EuropeanCall::GetArguments() {
//    pricingEngine_->getArguments(shared_ptr<EuropeanCallArguments>(new EuropeanCallArguments("Call", payoff_)));
//}*/
