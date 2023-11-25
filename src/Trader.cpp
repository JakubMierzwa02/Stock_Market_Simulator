#include "Trader.hpp"

namespace transaction
{
    std::string Trader::generateOrderId()
    {
        return "_O" + std::to_string(nextOrderId++);
    }

    void Trader::reserveFunds(double amount)
    {
        if (balance >= amount)
        {
            balance -= amount;
        }
        else
        {
            throw std::runtime_error("Insufficient funds.");
        }
    }

    void Trader::addFunds(double amount)
    {
        balance += amount;
    }

    void Trader::addAssets(unsigned int amount)
    {
        assets += amount;
    }

    void Trader::removeAssets(unsigned int amount)
    {
        if (assets >= amount)
        {
            assets -= amount;
        }
        else
        {
            throw std::runtime_error("Insufficient assets.");
        }
    }

    void Trader::placeLimitOrder(double price, unsigned int volume, bool isBuy)
    {
        if (!isBuy && assets < volume)
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
            removeAssets(volume);
        }

        auto order = std::make_shared<LimitOrder>(generateOrderId(), traderId, isBuy, price, volume);
        openOrders.push_back(order);
        orderBook->addOrder(order);
    }

    void Trader::placeMarketOrder(unsigned int volume, bool isBuy)
    {
        if (!isBuy && assets < volume)
        {
            std::cout << "Error: Not enough assets to sell." << std::endl;
            return;
        }
        
        if (!isBuy)
        {
            removeAssets(volume);
        }

        auto order = std::make_shared<MarketOrder>(generateOrderId(), traderId, isBuy, volume);
        openOrders.push_back(order);
        orderBook->addOrder(order);
    }

    void Trader::cancelOrder(const std::shared_ptr<Order> &order)
    {
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

    std::string Trader::getTraderId() const
    { 
        return traderId; 
    }

    double Trader::getBalance() const 
    { 
        return balance; 
    }

    void Trader::setBalance(double newBalance) 
    {
        balance = newBalance; 
    }

    unsigned int Trader::getAssets() const
    {
        return assets;
    }

    void Trader::setAssets(unsigned int newAmount)
    {
        assets = newAmount;
    }
}
