#include <gtest/gtest.h>
#include "../src/OrderBook.hpp"

class TransactionSimulationTest : public ::testing::Test
{
protected:
    transaction::OrderBook orderBook;
    std::shared_ptr<transaction::Order> buyOrder;
    std::shared_ptr<transaction::Order> sellOrder;
    std::shared_ptr<transaction::Trader> trader;

    void SetUp() override
    {
        trader = std::make_shared<transaction::Trader>("trader_id", 10000, &orderBook);
        buyOrder = std::make_shared<transaction::LimitOrder>("buy_order_id", "trader_id", true, 100, 50);
        sellOrder = std::make_shared<transaction::LimitOrder>("sell_order_id", "trader_id", false, 100, 50);
        orderBook.registerTrader(trader);
    }
};

TEST_F(TransactionSimulationTest, GenerateTradeId)
{
    std::string id1 = orderBook.generateTradeId();
    std::string id2 = orderBook.generateTradeId();
    EXPECT_NE(id1, id2);
}

TEST_F(TransactionSimulationTest, ExecuteTrade)
{
    //orderBook.executeTrade(buyOrder, sellOrder);
    orderBook.addOrder(buyOrder);
    orderBook.addOrder(sellOrder);
    EXPECT_EQ(buyOrder->getVolume(), 0);
    EXPECT_EQ(sellOrder->getVolume(), 0);
}

TEST_F(TransactionSimulationTest, RegisterAndFindTrader)
{
    auto foundTrader = orderBook.findTraderById("trader_id");
    EXPECT_NE(foundTrader, nullptr);
    EXPECT_EQ(foundTrader->getTraderId(), trader->getTraderId());
}

TEST_F(TransactionSimulationTest, GenerateOrderId)
{
    std::string id1 = trader->generateOrderId();
    std::string id2 = trader->generateOrderId();
    EXPECT_NE(id1, id2);
}

TEST_F(TransactionSimulationTest, ReserveFunds)
{
    double initialBalance = trader->getCashBalance();
    double reserveAmount = 500.0;
    trader->reserveFunds(reserveAmount);
    EXPECT_EQ(trader->getCashBalance(), initialBalance - reserveAmount);
}

TEST_F(TransactionSimulationTest, AddFunds)
{
    double initialBalance = trader->getCashBalance();
    double addAmount = 200.0;
    trader->addFunds(addAmount);
    EXPECT_EQ(trader->getCashBalance(), initialBalance + addAmount);
}

TEST_F(TransactionSimulationTest, AddAndRemoveAssets)
{
    unsigned int initialAssets = trader->getAssets();
    unsigned int addAmount = 10;
    trader->addAssets("BTC", addAmount);
    EXPECT_EQ(trader->getAssets(), initialAssets + addAmount);
    trader->removeAssets("BTC", 5);
    EXPECT_EQ(trader->getAssets(), initialAssets + addAmount - 5);
}