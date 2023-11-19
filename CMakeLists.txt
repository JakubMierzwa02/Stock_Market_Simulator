cmake_minimum_required(VERSION 3.10)

project(StockMarketSimulator)

set(CMAKE_CXX_STANDARD 17)

set(BOOST_ROOT "${CMAKE_SOURCE_DIR}/boost_1_83_0")

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(StockMarketSimulator src/main.cpp)

target_link_libraries(StockMarketSimulator ${Boost_LIBRARIES})

#enable_testing()
#add_subdirectory(test)