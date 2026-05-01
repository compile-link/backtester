cmake_minimum_required(VERSION 3.15)
project(backtester LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TESTING "Build tests" ON)
option(ENABLE_ASAN "Enable AddressSanitizer in Debug mode" OFF)

add_library(backtester_core
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
target_include_directories(backtester_core PUBLIC include)

if(ENABLE_ASAN)
	target_compile_options(backtester_core PRIVATE
		$<$<CONFIG:Debug>:-fsanitize=address>)
	target_link_options(backtester_core PRIVATE
        $<$<CONFIG:Debug>:-fsanitize=address>
    )
endif()

add_executable(backtester src/main.cpp)
target_link_libraries(backtester PRIVATE backtester_core)

if(BUILD_TESTING)
	enable_testing()
	find_package(GTest REQUIRED)
	add_executable(unit_tests
		tests/DataManager.test.cpp
		tests/Wallet.test.cpp
		tests/PositionManager.test.cpp
		tests/BacktestFlow.integration.test.cpp
	)
	target_link_libraries(unit_tests PRIVATE backtester_core GTest::gtest_main)
	target_compile_definitions(unit_tests PRIVATE PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

	include(GoogleTest)
	gtest_discover_tests(unit_tests)
endif()
