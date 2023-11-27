#ifndef TRADER_HPP
#define TRADER_HPP

#include "Order.hpp"
#include "LimitOrder.hpp"
#include "MarketOrder.hpp"
#include "OrderBook.hpp"
#include "Portfolio.hpp"

#include <string>
#include <vector>
#include <memory>
#include <iostream>

namespace transaction
{
    class OrderBook;
    class Portfolio;
    class Asset;
    
    class Trader
    {
    private:
        std::string traderId;
        portfolio::Portfolio portfolio;
        std::vector<std::shared_ptr<Order>> openOrders;
        OrderBook* orderBook;
        unsigned long long nextOrderId = 1;

    public:
        Trader(const std::string& id, double initialCash, OrderBook* book)
            : traderId(id), portfolio(), orderBook(book)
            {
                portfolio.addCash(initialCash);
            }

        std::string generateOrderId();
        void reserveFunds(double amount);
        void addFunds(double amount);
        void addAssets(const std::string& assetId, unsigned int quantity);
        void removeAssets(const std::string& assetId, unsigned int quantity);
        void placeLimitOrder(double price, unsigned int volume, bool isBuy);
        void placeMarketOrder(unsigned int volume, bool isBuy);
        void cancelOrder(const std::shared_ptr<Order>& order);

        // Getters / Setters
        std::string getTraderId() const;
        double getCashBalance() const;
        void setCashBalance(double newBalance);
        unsigned int getAssets() const;
        void setAssets(unsigned int newAmount);
    };
}

#endif