cmake_minimum_required(VERSION 3.15)
project(backtester LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
add_executable(backtester 
 src/main.cpp
 src/Backtester.cpp
 src/DataManager.cpp
 src/PositionManager.cpp
 src/StrategyMA.cpp
)
target_include_directories(backtester PRIVATE include)
