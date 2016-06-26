#include <iostream>

#include "payoff.h"

using namespace std;

int main() {
    VanillaCallPayoff vanillaCallPayoff(5.0);
    double payoff = vanillaCallPayoff.GetPayoff(3);
    cout << payoff;

    cout << "Hello, World!" << endl;
    return 0;
}