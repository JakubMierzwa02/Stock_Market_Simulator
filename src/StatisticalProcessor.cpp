#include "StatisticalProcessor.hpp"

namespace analyzer
{
    double StatisticalProcessor::calculateAverage(const std::vector<double> &data)
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

    double StatisticalProcessor::calculateVariance(const std::vector<double> &data)
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
}