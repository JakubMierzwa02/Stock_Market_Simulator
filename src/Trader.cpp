#include "Trader.hpp"

namespace transaction
{
    // Function to generate a unique order ID for each new order
    std::string Trader::generateOrderId()
    {
        return traderId + "_O" + std::to_string(nextOrderId++);
    }

    // Function to reserve funds for an order, checks if balance is sufficient
    void Trader::reserveFunds(double amount)
    {
        if (portfolio.getCashBalance() >= amount)
        {
            portfolio.setCashBalance(portfolio.getCashBalance() - amount);
        }
        else
        {
            std::cout << "Insufficient funds." << std::endl;
        }
    }

    // Function to add funds to the trader's balance
    void Trader::addFunds(double amount)
    {
        portfolio.addCash(amount);
    }

    // Function to add assets to the trader's account
    void Trader::addAssets(const std::string& assetId, unsigned int quantity)
    {
        portfolio.addAsset(portfolio::Asset(assetId, quantity));
    }

    // Function to remove assets from the trader's account
    void Trader::removeAssets(const std::string& assetId, unsigned int quantity)
    {
        portfolio.updateAssetQuantity(assetId, -static_cast<int>(quantity));
    }

    // Function to place a limit order
    void Trader::placeLimitOrder(double price, unsigned int volume, bool isBuy)
    {
        // EDIT //
        if (!isBuy && portfolio.getAssetQuantity("BTC") < volume)
        {
            std::cout << "Error: Not enough assets to sell." << std::endl;
            return;
        }

        double amount = price * volume;
        if (isBuy)
        {
            reserveFunds(amount);
        }
        else
        {
            removeAssets("BTC", volume);
        }

        // Create a new limit order and add it to the order book
        auto order = std::make_shared<LimitOrder>(generateOrderId(), traderId, isBuy, price, volume);
        openOrders.push_back(order);
        orderBook->addOrder(order);
    }

    // Function to place a market order
    void Trader::placeMarketOrder(unsigned int volume, bool isBuy)
    {
        // Check if trader has enough assets to sell
        if (!isBuy && portfolio.getAssetQuantity("BTC") < volume)
        {
            std::cout << "Error: Not enough assets to sell." << std::endl;
            return;
        }
        
        if (!isBuy)
        {
            removeAssets("BTC", volume);
        }

        // Create a new market order and add it to the order book
        auto order = std::make_shared<MarketOrder>(generateOrderId(), traderId, isBuy, orderBook->getLastTradePrice(), volume);
        openOrders.push_back(order);
        orderBook->addOrder(order);
    }

    // Function to cancel an existing order
    void Trader::cancelOrder(const std::shared_ptr<Order> &order)
    {
        // Find the order in the list of open orders
        auto it = std::find_if(openOrders.begin(), openOrders.end(),
                               [&order](const std::shared_ptr<Order> &o)
                               { return o->getOrderId() == order->getOrderId(); });

        if (it != openOrders.end())
        {
            orderBook->removeOrder(*it);
            openOrders.erase(it);
            std::cout << "Order " << order->getOrderId() << " cancelled." << std::endl;
        }
        else
        {
            std::cout << "Order " << order->getOrderId() << " not found." << std::endl;
        }
    }

    // Getters / Setters
    std::string Trader::getTraderId() const
    { 
        return traderId; 
    }

    double Trader::getCashBalance() const 
    { 
        return portfolio.getCashBalance(); 
    }

    void Trader::setCashBalance(double newBalance) 
    {
        portfolio.setCashBalance(newBalance); 
    }

    unsigned int Trader::getAssets() const
    {
        return portfolio.getAssetQuantity("BTC");
    }
}
