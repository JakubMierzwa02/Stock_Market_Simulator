#ifndef TECHNICALINDICATOR_HPP
#define TECHNICALINDICATOR_HPP

#include <vector>
#include <algorithm>

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

        struct StochasticOscillator
        {
            std::vector<double> K;
            std::vector<double> D;
        };

        static StochasticOscillator calculateStochastic(const std::vector<double>& prices, int periodK, int periodD)
        {
            StochasticOscillator stoch;

            if (prices.size() < periodK)
                return stoch;

            for (size_t i = periodK - 1; i < prices.size(); ++i)
            {
                double low = *std::min_element(prices.begin() + i - periodK + 1, prices.begin() + i + 1);
                double high = *std::max_element(prices.begin() + i - periodK + 1, prices.begin() + i + 1);
                double close = prices[i];

                double K = ((close - low) / (high - low)) * 100;
                stoch.K.push_back(K);
            }

            for (size_t i = periodD - 1; i < stoch.K.size(); ++i)
            {
                double sum = 0.0;
                for (size_t j = i - periodD + 1; j <= i; ++j)
                {
                    sum += stoch.K[j];
                }
                double D = sum / periodD;
                stoch.D.push_back(D);
            }

            return stoch;
        }
    };
}

#endif