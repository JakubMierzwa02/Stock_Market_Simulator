#ifndef ORDER_HPP
#define ORDER_HPP

#include <string>
#include <iostream>
#include <sstream>

enum class OrderType { LIMIT, MARKET };

namespace transaction
{
    class Order
    {
    protected:
        std::string orderId;
        std::string traderId;
        OrderType type;
        bool isBuyOrder;
        double price;
        unsigned int volume;

    public:
        Order(std::string id, std::string traderId, OrderType orderType, bool isBuy, double orderPrice, unsigned int orderVolume)
            : orderId(id), traderId(traderId), type(orderType), isBuyOrder(isBuy), price(orderPrice), volume(orderVolume) { }

        virtual ~Order() { }

        virtual std::string toString() const
        {
            std::ostringstream ss;
            ss << "Order ID: " << orderId 
                << ", Trader ID: " << traderId
                << ", Type: " << (isBuyOrder ? "Buy" : "Sell")
                << ", Price: " << price
                << ", Volume: " << volume;
            return ss.str();
        }

        // Getters
        std::string getOrderId() const { return orderId; }
        std::string getTraderId() const { return traderId; }
        OrderType getType() const { return type; }
        bool getIsBuyOrder() const { return isBuyOrder; }
        double getPrice() const { return price; }
        unsigned int getVolume() const { return volume; }

        // Setters
        void setPrice(double newPrice) { price = newPrice; }
        void setVolume(unsigned int newVolume) { volume = newVolume; }
    };
}

#endif