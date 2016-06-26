cmake_minimum_required(VERSION 3.5)
project(Finance)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Payoff.cpp Option.cpp Option.h nameDef.h PricingEngine.cpp PricingEngine.h)
add_executable(Finance ${SOURCE_FILES})