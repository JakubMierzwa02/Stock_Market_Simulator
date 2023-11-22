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
    double rsiGains = analyzer::TechnicalIndicator::calculateRSI(continuousGains);
    EXPECT_GT(rsiGains, 70.0);

    std::vector<double> continuousLosses = {128, 126, 124, 122, 120, 118, 116, 114, 112, 110, 108, 106, 104, 102, 100};
    double rsiLosses = analyzer::TechnicalIndicator::calculateRSI(continuousLosses);
    EXPECT_LT(rsiLosses, 30.0);

    std::vector<double> exampleData = {120, 149, 114, 109, 131, 117, 143, 139, 110, 126, 140, 128, 141, 150, 127, 124, 101, 116, 123, 146, 125, 136, 122, 119, 102, 107, 106, 145, 130, 113, 100, 137, 103, 134, 147, 132, 138, 115, 148, 108};
    double rsiExample = analyzer::TechnicalIndicator::calculateRSI(exampleData);
    EXPECT_NEAR(rsiExample, 50.0, 40.0);
}