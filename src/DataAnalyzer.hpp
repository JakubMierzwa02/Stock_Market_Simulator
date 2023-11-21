#ifndef DATAANALYZER_HPP
#define DATAANALYZER_HPP

#include <string>
#include <vector>
#include <iostream>

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

    class StatisticalProcessor
    {
    private:

    public:
        double calculateAverage(const std::vector<double>& data)
        {
            if (data.empty())
                return 0;
            double sum = 0.0;
            for (auto price : data)
            {
                sum += price;
            }
            return sum / data.size();
        }
    };

    class DataAnalyzer
    {
    private:
        std::vector<MarketData> marketData;
        StatisticalProcessor processor;
    public:
        DataAnalyzer(const std::vector<MarketData>& data) : marketData(data)
        {

        }

        void analyzeMarketData()
        {
            std::vector<double> closingPrices;
            for (auto& i : marketData)
            {
                closingPrices.push_back(i.close);
            }
            double averagePrice = processor.calculateAverage(closingPrices);
            std::cout << "Average closing price: " << averagePrice << std::endl;
        }
    };
}

#endif