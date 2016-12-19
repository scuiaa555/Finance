//
// Created by CUI Shidong on 10/7/2016.
//

#ifndef FINANCE_EUROPEANCALL_H
#define FINANCE_EUROPEANCALL_H

#include "Instrument.h"
#include "Payoffs/VanillaPayoff.h"

/**
 * European option class.
 * This European option class is used for pricing option with European feature.
 */
class EuropeanOption: public Instrument {
public:

    /**
     * Constructor.
     * @param maturity Maturity of European option.
     * @param payoff Pay-off type of European option.
     */
    EuropeanOption(Time maturity, std::shared_ptr<Payoff> payoff);

    /**
     * Argument class of European option.
     * Accessory class which is used to interact with pricing engine. \n
     * Inherited from Arguments class of PricingEngine.
     */
    class Arguments : public PricingEngine::Arguments {
    public:
        std::shared_ptr<Payoff> payoff_;  /**< Pay-off type. */
        Time maturity_;                   /**< Maturity of option. */
    };

    /**
     * Result class of European option
     * Accessory class which is used to interact with pricing engine. \n
     * Inherited from Result class of PricingEngine.
     */
    class Results : public PricingEngine::Results {
    public:
        Money price_;   /**< Net present value of European option. */
        double delta_;  /**< Delta of European option. */
    };

    /**
     * Engine class of European option
     * Accessory class which is used to interact with pricing engine. \n
     * Inherited from GenericEngine which groups the Arguments and Results of Asian option together.
     */
    class engine;

private:
    std::shared_ptr<Payoff> payoff_;    /**< Pay-off type of European option. */
    Time maturity_;                     /**< Maturity of European option. */
    /* reason that here uses 'shared_ptr' refers to comments in EuropeanOption.cpp */
    std::shared_ptr<Results> results_;  /**< Results calculated by pricing engine. */

    void setupArguments(PricingEngine::Arguments *const arg) const override;

    Money fetchResults(PricingEngine::Results *const res) override;
};

class EuropeanOption::engine : public GenericEngine<EuropeanOption::Arguments, EuropeanOption::Results> {
};



#endif //FINANCE_EUROPEANCALL_H
