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
        double rsi = analyzer::TechnicalIndicator::calculateRSI(closingPrices, 14);
        std::cout << "RSI: " << rsi << std::endl;

        int periodK = 5;
        int periodD = 3;

        analyzer::TechnicalIndicator::StochasticOscillator stochastic = analyzer::TechnicalIndicator::calculateStochastic(closingPrices, periodK, periodD);

        std::cout << "Stochastic Oscillator:" << std::endl;
        std::cout << "Line %K: ";
        for (const auto& K : stochastic.K) 
        {
            std::cout << K << " ";
        }
        std::cout << std::endl;

        std::cout << "Line %D: ";
        for (const auto& D : stochastic.D) 
        {
            std::cout << D << " ";
        }
        std::cout << std::endl;
    }
}