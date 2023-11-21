#ifndef DATAANALYZER_HPP
#define DATAANALYZER_HPP

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

    class StatisticalProcessor
    {
    private:

    public:
        double calculateAverage(const std::vector<double>& data)
        {
            if (data.empty())
                return 0.0;
            double sum = 0.0;
            for (auto price : data)
            {
                sum += price;
            }
            return sum / data.size();
        }

        double calculateVariance(const std::vector<double>& data)
        {
            if (data.size() < 2)
                return 0.0;
            double mean = calculateAverage(data);
            double sumOfSquares = 0.0;
            for (auto price : data)
            {
                sumOfSquares += (price - mean) * (price - mean);
            }
            return sumOfSquares / (data.size() - 1);
        }
    };

    class TechnicalIndicator
    {
    private:

    public:
        static double calculateRSI(const std::vector<double>& data, int period /* = 14 */)
        {
            if (data.size() < period)
                return 0.0;
            double avgGain = 0.0, avgLoss = 0.0;

            for (int i = 1; i <= period; i++)
            {
                double change = data[i] - data[i - 1];
                avgGain += std::max(change, 0.0);
                avgGain += std::max(-change, 0.0);
            }
            avgGain /= period;
            avgLoss /= period;

            for (size_t i = period + 1; i < data.size(); i++)
            {
                double change = data[i] - data[i - 1];
                avgGain = (avgGain * (period - 1) + std::max(change, 0.0)) / period;
                avgLoss = (avgLoss * (period - 1) + std::max(-change, 0.0)) / period;
            }

            if (avgLoss == 0)
                return 100.0;
            
            double rs = avgGain / avgLoss;
            return 100.0 - (100.0 / (1.0 + rs));
        }
    };

    class DataAnalyzer
    {
    private:
        std::vector<MarketData> marketData;
        StatisticalProcessor processor;
        TechnicalIndicator indicator;

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
            double variance = processor.calculateVariance(closingPrices);
            std::cout << "Variance: " << variance << std::endl;
            double rsi = indicator.calculateRSI(closingPrices, closingPrices.size());
            std::cout << "RSI: " << rsi << std::endl;
        }
    };
}

#endif