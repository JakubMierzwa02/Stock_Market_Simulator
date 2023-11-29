#ifndef TECHNICALINDICATOR_HPP
#define TECHNICALINDICATOR_HPP

#include <vector>

namespace analyzer
{
    class TechnicalIndicator
    {
    private:
    
    public:
        static double calculateSMA(const std::vector<double> &prices, int period)
        {
            if (prices.size() < period)
                return 0.0;

            double sum = 0.0;
            for (int i = prices.size() - period; i < prices.size(); ++i)
            {
                sum += prices[i];
            }
            return sum / period;
        }

        static double calculateEMA(const std::vector<double> &prices, int period)
        {
            if (prices.size() < period)
                return 0.0;

            double ema = calculateSMA(prices, period);
            double multiplier = 2.0 / (period + 1.0);

            for (int i = prices.size() - period; i < prices.size(); ++i)
            {
                ema = (prices[i] - ema) * multiplier + ema;
            }

            return ema;
        }

        static double calculateRSI(const std::vector<double> &data, int period)
        {
            if (data.size() < period + 1)
                return 0.0;
            double avgGain = 0.0, avgLoss = 0.0;

            for (int i = 1; i <= period; i++)
            {
                double change = data[i] - data[i - 1];
                avgGain += std::max(change, 0.0);
                avgLoss += std::max(-change, 0.0);
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
}

#endif