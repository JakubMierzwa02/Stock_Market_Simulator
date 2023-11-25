#ifndef ORDER_HPP
#define ORDER_HPP

#include <string>
#include <iostream>

enum class OrderType { LIMIT, MARKET };
enum class OrderStatus { PENDING, COMPLETED, CANCELLED };

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
        OrderStatus status;

    public:
        Order(std::string id, std::string traderId, OrderType orderType, bool isBuy, double orderPrice, unsigned int orderVolume)
            : orderId(id), traderId(traderId), type(orderType), isBuyOrder(isBuy), price(orderPrice), volume(orderVolume), status(OrderStatus::PENDING)
        {

        }

        virtual ~Order()
        {

        }

        virtual void executeOrder() = 0;

        // Getters
        std::string getOrderId() const { return orderId; }
        std::string getTraderId() const { return traderId; }
        OrderType getType() const { return type; }
        bool getIsBuyOrder() const { return isBuyOrder; }
        double getPrice() const { return price; }
        unsigned int getVolume() const { return volume; }
        OrderStatus getStatus() const { return status; }

        // Setters
        void setPrice(double newPrice) { price = newPrice; }
        void setVolume(unsigned int newVolume) { volume = newVolume; }
        void setStatus(OrderStatus newStatus) { status = newStatus; }
    };
}

#endif