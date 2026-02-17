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
 src/Strategies/StrategySMA.cpp
 src/Strategies/StrategyEngulfing.cpp
 src/Strategies/StrategyRegistry.cpp
 src/Wallet.cpp
 src/Reporter.cpp
 src/Menu.cpp
)
target_include_directories(backtester PRIVATE include)

option(BUILD_TESTING "Build tests" ON)
if(BUILD_TESTING)
	enable_testing()
	find_package(GTest REQUIRED)
	add_executable(unit_tests
		tests/DataManager.test.cpp
		src/DataManager.cpp
		tests/Wallet.test.cpp
		src/Wallet.cpp
		tests/PositionManager.test.cpp
		src/PositionManager.cpp
		tests/BacktestFlow.integration.test.cpp
	)
	target_include_directories(unit_tests PRIVATE include)

	target_link_libraries(unit_tests PRIVATE GTest::gtest_main)
	include(GoogleTest)
	gtest_discover_tests(unit_tests)
	target_compile_definitions(unit_tests PRIVATE PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")
endif()
