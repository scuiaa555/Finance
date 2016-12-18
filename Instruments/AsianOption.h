//
// Created by CUI Shidong on 23/7/2016.
//

#ifndef FINANCE_ASIANOPTION_H
#define FINANCE_ASIANOPTION_H

#include "Instrument.h"
#include "Payoffs/VanillaPayoff.h"
#include <vector>

/**
 * Asian option class.
 * This Asian option class is used for pricing option with Asian feature. There are two possible averaging types, arithmetic
 * and geometric.
 */
class AsianOption : public Instrument {
public:

    /**
     * Averaging types.
     */
    enum AverageType {
        arithmetic = 0,
        geometric = 1
    };

    /**
     * Constructor.
     * @param maturity Maturity of asian option (in year), e.g. maturity=1 means maturity is one year from reference day.
     * @param payoff Pay-off type of asian option.
     * @param monitoredTimes Dates of monitoring. Stored in a vector.
     * @param averageType Averaging types, arithmetic or geometric.
     * @param isDiscretelyMonitored =1 if the option is discretely monitored; =0 if is continuously monitored.
     */
    AsianOption(Time maturity, std::shared_ptr<Payoff> payoff, std::vector<Time> &monitoredTimes,
                AverageType averageType,
                bool isDiscretelyMonitored = 1);

    /**
     * Constructor.
     * @param maturity Maturity of asian option (in year), e.g. maturity=1 means maturity is one year from reference day.
     * @param payoff Pay-off type of asian option.
     * @param timeStep Dates of monitoring is evenly spaced.
     * @param averageType Averaging types, arithmetic or geometric.
     * @param isDiscretelyMonitored =1 if the option is discretely monitored; =0 if is continuously monitored.
     */
    AsianOption(Time maturity, std::shared_ptr<Payoff> payoff, Time timeStep, AverageType averageType,
                bool isDiscretelyMonitored = 1);

    /**
     * Constructor.
     * @param maturity Maturity of asian option (in year), e.g. maturity=1 means maturity is one year from reference day.
     * @param payoff Pay-off type of asian option.
     * @param averageType Averaging types, arithmetic or geometric.
     * @param isContinuouslyMonitored =1 if the option is continuously monitored; =0 if is discretely monitored.
     */
    AsianOption(Time maturity, std::shared_ptr<Payoff> payoff, AverageType averageType,
                bool isContinuouslyMonitored = 1);

    /**
     * Argument class of Asian Option.
     * Accessory class which is used to interact with pricing engine. \n
     * Inherited from Arguments class of PricingEngine.
     */
    class Arguments : public PricingEngine::Arguments {
    public:
        std::shared_ptr<Payoff> payoff_;    /**< Pay-off type. */
        std::vector<Time> monitoredTimes_;  /**< Vector of monitoring dates. */
        Time maturity_;                     /**< Maturity of option. */
        AverageType averageType_;           /**< Averaging type of Asian option. */
    };

    /**
     * Results class of Asian Option
     * Accessory class which is used to interact with pricing engine. \n
     * Inherited from Result class of PricingEngine.
     */
    class Results : public PricingEngine::Results {
    public:
        Money price_;      /**< Net present value of Asian option. */
   /*     double delta_;*/
    };

    /**
     * Engine class of Asian Option
     * Accessory class which is used to interact with pricing engine. \n
     * Inherited from GenericEngine which group the Arguments and Results of Asian option together.
     */
    class engine;

private:
    Time maturity_;
    std::shared_ptr<Payoff> payoff_;
    std::vector<Time> monitoredTimes_;
    std::shared_ptr<Results> results_;
    AverageType averageType_;

    void setupArguments(PricingEngine::Arguments *const arg) const override;
    Money fetchResults(PricingEngine::Results *const res) override;
};


class AsianOption::engine : public GenericEngine<AsianOption::Arguments, AsianOption::Results> {
};


#endif //FINANCE_ASIANOPTION_H
