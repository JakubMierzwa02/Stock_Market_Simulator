cmake_minimum_required(VERSION 3.10)

set(This StockMarketSimulatorTest)

add_subdirectory(googletest)

add_executable(StockMarketSimulatorTest
    test1.cpp
    test2.cpp
)

target_link_libraries(StockMarketSimulatorTest PUBLIC
    gtest_main
    StockMarketSimulator
)

enable_testing()

add_test(
    NAME ${This}
    COMMAND ${This}
)