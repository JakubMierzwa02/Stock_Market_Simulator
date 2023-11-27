#include <gtest/gtest.h>
#include "../src/OrderBook.hpp"

class OrderBookTest : public ::testing::Test
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

TEST_F(OrderBookTest, GenerateTradeId)
{
    std::string id1 = orderBook.generateTradeId();
    std::string id2 = orderBook.generateTradeId();
    EXPECT_NE(id1, id2);
}

TEST_F(OrderBookTest, MatchOrders)
{
    orderBook.addOrder(buyOrder);
    orderBook.addOrder(sellOrder);
    if (buyOrder->getStatus() == OrderStatus::PENDING)
    {
        std::cout<<"COMPLETED!!!!!!!"<<std::endl;
    }
    else
        std::cout<<"PENDING!!!!!"<<std::endl;
    EXPECT_EQ(buyOrder->getStatus(), OrderStatus::COMPLETED);
    EXPECT_EQ(sellOrder->getStatus(), OrderStatus::COMPLETED);
}

TEST_F(OrderBookTest, ExecuteTrade)
{
    //orderBook.executeTrade(buyOrder, sellOrder);
    orderBook.addOrder(buyOrder);
    orderBook.addOrder(sellOrder);
    EXPECT_EQ(buyOrder->getVolume(), 0);
    EXPECT_EQ(sellOrder->getVolume(), 0);
}

TEST_F(OrderBookTest, RegisterAndFindTrader)
{
    auto foundTrader = orderBook.findTraderById("trader_id");
    EXPECT_NE(foundTrader, nullptr);
    EXPECT_EQ(foundTrader->getTraderId(), trader->getTraderId());
}