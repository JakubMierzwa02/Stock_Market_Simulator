#ifndef STATISTICALPROCESSOR_HPP
#define STATISTICALPROCESSOR_HPP

#include <vector>

namespace analyzer
{
    class StatisticalProcessor
    {
    private:

    public:
        double calculateAverage(const std::vector<double>& data);
        double calculateVariance(const std::vector<double>& data);
    };
}

#endif