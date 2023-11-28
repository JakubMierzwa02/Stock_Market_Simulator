#ifndef STOCKDATA_HPP
#define STOCKDATA_HPP

#include <string>

namespace importer
{
    struct StockData
    {
        std::string date;
        std::string symbol;
        double open;
        double high;
        double low;
        double close;
        long volume;
    };
}

#endif