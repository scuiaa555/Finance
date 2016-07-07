cmake_minimum_required(VERSION 3.5)
project(Finance)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Payoff.cpp Payoff.h Option.cpp Option.h nameDef.h Model.cpp Model.h PricingEngine.cpp PricingEngine.h AnalyticEuropeanEngine.cpp AnalyticEuropeanEngine.h)
add_executable(Finance ${SOURCE_FILES})