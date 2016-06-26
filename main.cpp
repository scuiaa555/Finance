#include <iostream>

//#include "payoff.h"
#include "Option.h"

using namespace std;

int main() {
    shared_ptr<Payoff> vanillaCallPayoff(new VanillaCallPayoff(5.0));
    EuropeanCall a(1.0, vanillaCallPayoff);
    cout << a.GetMaturity() << endl;
    //cout << payoff << endl;


    cout << "Stone, fighting!" << endl;
    return 0;
}