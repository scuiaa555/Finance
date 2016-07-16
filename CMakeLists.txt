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

set(SOURCE_FILES main.cpp Payoff.cpp Payoff.h Instrument.cpp
        Instrument.h nameDef.h Model.cpp Model.h PricingEngine.cpp
        PricingEngine.h PricingEngines/AnalyticEuropeanEngine.cpp
        PricingEngines/AnalyticEuropeanEngine.h Instruments/EuropeanCall.cpp
        Instruments/EuropeanCall.h Instruments/Forward.cpp Instruments/Forward.h
        PricingEngines/AnalyticForwardEngine.cpp PricingEngines/AnalyticForwardEngine.h
        RandNumGeneration/UniformLEcuyerRNG1.cpp RandNumGeneration/UniformLEcuyerRNG1.h RandNumGeneration/RandomSequenceGenerator.h
        RandNumGeneration/NormalMarsagliaBrayRng.h StochasticProcess.cpp StochasticProcess.h Path.cpp Path.h PathGenerator.cpp PathGenerator.h)
add_executable(Finance ${SOURCE_FILES})