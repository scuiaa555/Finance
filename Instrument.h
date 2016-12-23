//
// Created by CUI Shidong on 26/6/2016.
//

#ifndef FINANCE_OPTION_H
#define FINANCE_OPTION_H

#include "NameDef.h"
#include "Payoff.h"
#include "PricingEngine.h"
#include <memory>
#include <string>

/**
 * Base Instrument class.
 * This Instrument class is an abstract base class for any financial instruments, like options, forward, swap, swaption, etc.
 * There is always a set of PricingEngine associated to each kind of instrument that can be used to price.
 * Any inherited financial instrument classes should override the methods that are used to communicate the pricingEngines.
 *
 */
class Instrument {
public:

    /**
     * Calculate the net present value by using the attached pricing engine.
     * Implemented by template pattern. \n
     * Set the argument of PricingEngine first and then calculate the npv by calling the method of PricingEngine and finally
     * fetch the results back from the PricingEngine class.
     */
    Money npv();

    /**
     * Set the corresponding pricing engine.
     * \e Constness: Pricing engine will not change.
     * @param pricingEngine The pricing engine to be used for pricing. \n
     */
    void setPricingEngine(const std::shared_ptr<PricingEngine> pricingEngine);

protected:
    std::shared_ptr<PricingEngine> pricingEngine_;  /**< One pricing engine also can be used for other instrument, so shared_ptr is used here */

    /**
     * To be called in method npv() which is to setup all the arguments that are needed for pricing engine.
     * \e Constness: Const member function. Argument pointer arg itself is const, but it does not point to const object.
     * @param arg Arguments which are needed for pricing engine.
     */
    virtual void setupArguments(PricingEngine::Arguments *const arg) const = 0;

    /**
     * To be called in method npv() which is to get back the net present value after calculation.
     * \e Constness: Unlike setupArguments, it is not a const member function. Result pointer res itself is const, but it does not point to const object.
     * @param res Results to be fetched back.
     * @return Net present value after calculation. Other results are stored in the results class.
     */
    virtual Money fetchResults(PricingEngine::Results *const res) = 0;

};

#endif //FINANCE_OPTION_H
