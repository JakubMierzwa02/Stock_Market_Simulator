cmake_minimum_required(VERSION 3.10)

set(This StockMarketSimulator)
project(${This})

set(CMAKE_CXX_STANDARD 17)

set(BOOST_ROOT "${CMAKE_SOURCE_DIR}/boost_1_83_0")

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

set(Sources
    src/main.cpp
    src/CSVImporter.cpp
    src/DataImporter.cpp
    src/DataValidator.cpp
    src/DataAnalyzer.cpp
    src/StatisticalProcessor.cpp
    src/Trader.cpp
    src/OrderBook.cpp
    src/UserInterface.cpp
    src/Portfolio.cpp
)

set(Headers
    src/CSVImporter.hpp
    src/DataImporter.hpp
    src/IDataImporter.hpp
    src/StockData.hpp
    src/DataValidator.hpp
    src/Trader.hpp
    src/OrderBook.hpp
    src/UserInterface.hpp
    src/Portfolio.hpp
)

add_executable(This ${Sources})

target_link_libraries(This ${Boost_LIBRARIES})

add_library(${This} STATIC ${Sources} ${Headers})

enable_testing()
add_subdirectory(test)