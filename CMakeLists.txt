cmake_minimum_required(VERSION 3.10)

set(This StockMarketSimulator)

set(CMAKE_CXX_STANDARD 17)

set(BOOST_ROOT "${CMAKE_SOURCE_DIR}/boost_1_83_0")

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(This src/main.cpp)

target_link_libraries(This ${Boost_LIBRARIES})

add_library(${This} STATIC src/main.cpp)

enable_testing()
add_subdirectory(test)