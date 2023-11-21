#include <gtest/gtest.h>
#include "../src/DataAnalyzer.hpp"

class DataAnalyzerTest : public ::testing::Test
{
protected:
    analyzer::StatisticalProcessor processor;
};

TEST_F(DataAnalyzerTest, CalculateAverage)
{
    EXPECT_DOUBLE_EQ(processor.calculateAverage({}), 0.0);
    EXPECT_DOUBLE_EQ(processor.calculateAverage({10}), 10.0);
    EXPECT_DOUBLE_EQ(processor.calculateAverage({10, 20, 30}), 20.0);
}

TEST_F(DataAnalyzerTest, CalculateVariance)
{
    EXPECT_DOUBLE_EQ(processor.calculateVariance({}), 0.0);
    EXPECT_DOUBLE_EQ(processor.calculateVariance({10}), 0.0);
    std::vector<double> data = {10, 20, 30};
    double mean = processor.calculateAverage(data);
    double variance = 0.0;
    for (double value : data) 
    {
        variance += (value - mean) * (value - mean);
    }
    variance /= (data.size() - 1);
    EXPECT_DOUBLE_EQ(processor.calculateVariance(data), variance);
}

TEST_F(DataAnalyzerTest, CalculateRSI)
{
    std::vector<double> continuousGains = {100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120, 122, 124, 126, 128};
    double rsiGains = analyzer::TechnicalIndicator::calculateRSI(continuousGains, continuousGains.size());
    EXPECT_GT(rsiGains, 70.0);

    std::vector<double> continuousLosses = {128, 126, 124, 122, 120, 118, 116, 114, 112, 110, 108, 106, 104, 102, 100};
    double rsiLosses = analyzer::TechnicalIndicator::calculateRSI(continuousLosses, continuousLosses.size());
    EXPECT_GT(rsiLosses, 30.0);
}