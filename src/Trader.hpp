#ifndef TRADER_HPP
#define TRADER_HPP

#include "Order.hpp"
#include "LimitOrder.hpp"
#include "MarketOrder.hpp"
#include "OrderBook.hpp"

#include <string>
#include <vector>
#include <memory>
#include <iostream>

namespace transaction
{
    class OrderBook;
    
    class Trader
    {
    private:
        std::string traderId;
        double balance;
        unsigned int assets;
        std::vector<std::shared_ptr<Order>> openOrders;
        OrderBook* orderBook;
        unsigned long long nextOrderId = 1;

        std::string generateOrderId();

    public:
        Trader(const std::string& id, double initialBalance, OrderBook* book)
            : traderId(id), balance(initialBalance), orderBook(book) { }

        void reserveFunds(double amount);
        void addFunds(double amount);
        void addAssets(unsigned int amount);
        void removeAssets(unsigned int amount);
        void placeLimitOrder(double price, unsigned int volume, bool isBuy);
        void placeMarketOrder(unsigned int volume, bool isBuy);
        void cancelOrder(const std::shared_ptr<Order>& order);

        // Getters / Setters
        std::string getTraderId() const;
        double getBalance() const;
        void setBalance(double newBalance);
        unsigned int getAssets() const;
        void setAssets(unsigned int newAmount);
    };
}

#endif