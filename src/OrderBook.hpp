#ifndef ORDERBOOK_HPP
#define ORDERBOOK_HPP

#include "Order.hpp"
#include "Trader.hpp"
#include "Trade.hpp"
#include "UserInterface.hpp"

#include <string>
#include <map>
#include <set>
#include <memory>
#include <algorithm>

namespace transaction
{
    class Order;
    class Trader;

    struct CompareBuyOrders
    {
        bool operator()(const std::shared_ptr<Order>& a, const std::shared_ptr<Order>& b) const
        {
            return a->getPrice() < b->getPrice();
        }
    };

    struct CompareSellOrders
    {
        bool operator()(const std::shared_ptr<Order>& a, const std::shared_ptr<Order>& b) const
        {
            return a->getPrice() < b->getPrice();
        }
    };

    class OrderBook
    {
    private:
        std::map<std::string, std::shared_ptr<Trader>> traders;
        std::multiset<std::shared_ptr<Order>, CompareBuyOrders> buyOrders;
        std::multiset<std::shared_ptr<Order>, CompareSellOrders> sellOrders;
        unsigned long long nextTradeId = 1;

        std::string generateTradeId();
        void matchOrders();
        void executeTrade(const std::shared_ptr<Order>& order1, const std::shared_ptr<Order>& order2);
        void updateOrderVolume(const std::shared_ptr<Order>& order, unsigned int tradeVolume);

    public:
        OrderBook() { }

        void registerTrader(const std::shared_ptr<Trader>& trader);
        Trader* findTraderById(const std::string& traderId);
        void addOrder(std::shared_ptr<Order> order);
        void removeOrder(const std::shared_ptr<Order>& order);
        void displayBook() const;
    };
}

#endif