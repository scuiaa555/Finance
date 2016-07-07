cmake_minimum_required(VERSION 3.5)
project(Finance)

set(BOOST_ROOT "/opt/include/boost")
FIND_PACKAGE(Boost REQUIRED)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif()
IF (Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Payoff.cpp Payoff.h Option.cpp Option.h nameDef.h Model.cpp Model.h PricingEngine.cpp PricingEngine.h AnalyticEuropeanEngine.cpp AnalyticEuropeanEngine.h)
add_executable(Finance ${SOURCE_FILES})