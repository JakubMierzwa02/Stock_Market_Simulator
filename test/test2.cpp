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

TEST_F(DataAnalyzerTest, CalculateSMA) 
{
    EXPECT_DOUBLE_EQ(analyzer::TechnicalIndicator::calculateSMA({1, 2, 3, 4, 5}, 3), 4.0);
    EXPECT_DOUBLE_EQ(analyzer::TechnicalIndicator::calculateSMA({1, 2, 3}, 5), 0.0);
    EXPECT_DOUBLE_EQ(analyzer::TechnicalIndicator::calculateSMA({}, 3), 0.0);
}

TEST_F(DataAnalyzerTest, CalculateEMA) 
{
    std::vector<double> prices = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    double ema5 = analyzer::TechnicalIndicator::calculateEMA(prices, 5);
    double ema10 = analyzer::TechnicalIndicator::calculateEMA(prices, 10);
    EXPECT_GT(ema5, ema10);
    EXPECT_DOUBLE_EQ(analyzer::TechnicalIndicator::calculateEMA({1, 2, 3}, 5), 0.0);
    EXPECT_DOUBLE_EQ(analyzer::TechnicalIndicator::calculateEMA({}, 3), 0.0);
}

TEST_F(DataAnalyzerTest, CalculateRSI)
{
    std::vector<double> continuousGains = {100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120, 122, 124, 126, 128};
    double rsiGains = analyzer::TechnicalIndicator::calculateRSI(continuousGains, 14);
    EXPECT_GT(rsiGains, 70.0);

    std::vector<double> continuousLosses = {128, 126, 124, 122, 120, 118, 116, 114, 112, 110, 108, 106, 104, 102, 100};
    double rsiLosses = analyzer::TechnicalIndicator::calculateRSI(continuousLosses, 14);
    EXPECT_LT(rsiLosses, 30.0);

    std::vector<double> exampleData = {120, 149, 114, 109, 131, 117, 143, 139, 110, 126, 140, 128, 141, 150, 127, 124, 101, 116, 123, 146, 125, 136, 122, 119, 102, 107, 106, 145, 130, 113, 100, 137, 103, 134, 147, 132, 138, 115, 148, 108};
    double rsiExample = analyzer::TechnicalIndicator::calculateRSI(exampleData, 14);
    EXPECT_NEAR(rsiExample, 50.0, 40.0);
}

TEST_F(DataAnalyzerTest, CalculateStochastic)
{
    std::vector<double> prices = { 100, 105, 110, 115, 120, 125, 130, 135, 140, 145 };

    int periodK = 5;
    int periodD = 3;

    auto stochastic = analyzer::TechnicalIndicator::calculateStochastic(prices, periodK, periodD);

    EXPECT_EQ(stochastic.K.size(), prices.size() - periodK + 1);
    EXPECT_EQ(stochastic.D.size(), prices.size() - periodK - periodD + 2);

    for (const auto& value : stochastic.K) 
    {
        EXPECT_GE(value, 0.0);
        EXPECT_LE(value, 100.0);
    }

    for (const auto& value : stochastic.D) 
    {
        EXPECT_GE(value, 0.0);
        EXPECT_LE(value, 100.0);
    }
}

TEST_F(DataAnalyzerTest, CalculateMACD)
{
    std::vector<double> prices = {145.69, 107.42, 187.66, 199.90, 124.81, 135.49, 152.30, 170.54, 103.04, 128.07,
                                    101.61, 150.08, 154.91, 162.03, 182.10, 151.29, 100.64, 198.63, 146.99, 122.62,
                                    115.54, 114.83, 105.03, 192.59, 156.49, 176.58, 180.14, 197.37, 183.11, 183.20,
                                    100.77, 171.42, 135.47, 111.07, 198.88, 131.29, 183.81, 115.57, 113.84, 164.75};
    auto macdResult = analyzer::TechnicalIndicator::calculateMACD(prices);

    EXPECT_EQ(macdResult.MACDLine.size(), prices.size() - 25);
    EXPECT_EQ(macdResult.SignalLine.size(), prices.size() - 33);
    EXPECT_EQ(macdResult.Histogram.size(), macdResult.SignalLine.size());

    for (const auto& value : macdResult.MACDLine)
    {
        EXPECT_GE(value, -200.0);
        EXPECT_LE(value, 200.0);
    }

    for (const auto& value : macdResult.SignalLine)
    {
        EXPECT_GE(value, -200.0);
        EXPECT_LE(value, 200.0);
    }

    for (const auto& value : macdResult.Histogram)
    {
        EXPECT_GE(value, -200.0);
        EXPECT_LE(value, 200.0);
    }
}