cmake_minimum_required(VERSION 3.5)
project(Finance)

set(BOOST_ROOT "/opt/include/boost")
FIND_PACKAGE(Boost REQUIRED)
if (NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif ()
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS("-DHAS_BOOST")
ENDIF ()

include_directories("/Users/CUI/Dropbox/C++/Finance")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Main.cpp Payoff.h Instrument.cpp
        Instrument.h NameDef.h StochasticProcess.h PricingEngine.cpp
        PricingEngine.h PricingEngines/AnalyticEuropeanEngine.cpp
        PricingEngines/AnalyticEuropeanEngine.h Instruments/EuropeanOption.cpp
        Instruments/EuropeanOption.h Instruments/Forward.cpp Instruments/Forward.h
        PricingEngines/AnalyticForwardEngine.cpp PricingEngines/AnalyticForwardEngine.h
        RandNumGeneration/UniformLEcuyerRNG1.cpp RandNumGeneration/UniformLEcuyerRNG1.h RandNumGeneration/SingleRandSequenceGenerator.h
        RandNumGeneration/NormalMarsagliaBrayRng.h Model.h
        McFramework/Path.cpp McFramework/Path.h McFramework/PathGenerator.h McFramework/PathPricer.h
        McFramework/McModel.h PricingEngines/EuropeanPathPricer.cpp Statistics.cpp Statistics.h
        McFramework/McSimulation.h PricingEngines/McEuropeanEngine.h
        Payoffs/VanillaPayoff.cpp Payoffs/VanillaPayoff.h Instruments/AsianOption.cpp Instruments/AsianOption.h
        PricingEngines/EuropeanPathPricer.h Parameter.cpp Parameter.h
        Models/BlackScholesModel.cpp Models/BlackScholesModel.h Models/LMM.cpp Models/LMM.h StochasticProcesses/BSStochasticProcess.cpp
        StochasticProcesses/BSStochasticProcess.h StochasticProcesses/LogNormalProcess.cpp StochasticProcesses/LogNormalProcess.h
        RandNumGeneration/MultiRandGenerator.h RandNumGeneration/PseudoRandom.h RandNumGeneration/RandomVariableGenerator.h RandNumGeneration/Normal.h RandNumGeneration/Poisson.h RandNumGeneration/PoissonInverse.h RandNumGeneration/CompoundPoisson.h)
add_executable(Finance ${SOURCE_FILES})