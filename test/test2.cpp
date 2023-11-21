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