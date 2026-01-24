cmake_minimum_required(VERSION 3.15)
project(backtester LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	string(APPEND CMAKE_CXX_FLAGS_DEBUG " -O0")
#	add_compile_options(-fsanitize=address -g -O0)
#	add_link_options(-fsanitize=address)
endif()

add_executable(backtester 
 src/main.cpp
 src/Backtester.cpp
 src/DataManager.cpp
 src/PositionManager.cpp
 src/StrategySMA.cpp
 src/Wallet.cpp
 src/Reporter.cpp
)
target_include_directories(backtester PRIVATE include)
