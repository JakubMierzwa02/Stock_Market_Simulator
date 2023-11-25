#ifndef ORDERBOOK_HPP
#define ORDERBOOK_HPP

#include "Order.hpp"
#include "Trader.hpp"
#include "Trade.hpp"
#include "UserInterface.hpp"

#include <string>
#include <map>
#include <list>
#include <memory>
#include <algorithm>

namespace transaction
{
    class Order;
    class Trader;

    class OrderBook
    {
    private:
        std::map<std::string, std::shared_ptr<Trader>> traders;
        std::list<std::shared_ptr<Order>> buyOrders;
        std::list<std::shared_ptr<Order>> sellOrders;
        unsigned long long nextTradeId = 1;

        std::string generateTradeId();
        void matchOrders();
        void executeTrade(std::shared_ptr<Order>& order1, std::shared_ptr<Order>& order2);

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