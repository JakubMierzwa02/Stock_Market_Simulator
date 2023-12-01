#ifndef DATAANALYZER_HPP
#define DATAANALYZER_HPP

#include "StatisticalProcessor.hpp"
#include "TechnicalIndicator.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

namespace analyzer
{
    struct MarketData
    {
        std::string date;
        std::string symbol;
        double open;
        double high;
        double low;
        double close;
        long volume;
    };

    class DataAnalyzer
    {
    private:
        std::vector<MarketData> marketData;
        StatisticalProcessor processor;
        //TechnicalIndicator indicator;

    public:
        DataAnalyzer(const std::vector<MarketData>& data) : marketData(data) { }

        void analyzeMarketData();
    };
}

#endif