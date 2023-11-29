#include "DataAnalyzer.hpp"

namespace analyzer
{
    void DataAnalyzer::analyzeMarketData()
    {
        std::vector<double> closingPrices;
        for (auto &i : marketData)
        {
            closingPrices.push_back(i.close);
        }
        double averagePrice = processor.calculateAverage(closingPrices);
        std::cout << "Average closing price: " << averagePrice << std::endl;
        double variance = processor.calculateVariance(closingPrices);
        std::cout << "Variance: " << variance << std::endl;
        double rsi = indicator.calculateRSI(closingPrices, 14);
        std::cout << "RSI: " << rsi << std::endl;
    }
}