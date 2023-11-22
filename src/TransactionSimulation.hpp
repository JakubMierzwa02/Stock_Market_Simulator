#ifndef TRANSACTIONSIMULATION_HPP
#define TRANSACTIONSIMULATION_HPP

#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <memory>

namespace transaction
{
    enum class OrderType { BUY, SELL };
    enum class OrderStatus { PENDING, COMPLETED, CANCELLED };

    class Order
    {
    protected:
        std::string orderId;
        OrderType type;
        double price;
        unsigned int volume;
        OrderStatus status;

    public:
        Order(std::string id, OrderType orderType, double orderPrice, unsigned int orderVolume)
            : orderId(id), type(orderType), price(orderPrice), volume(orderVolume), status(OrderStatus::PENDING)
        {

        }

        virtual ~Order()
        {

        }

        virtual void executeOrder() = 0;

        // Getters
        std::string getOrderId() const { return orderId; }
        OrderType getType() const { return type; }
        double getPrice() const { return price; }
        unsigned int getVolume() const { return volume; }
        OrderStatus getStatus() const { return status; }

        // Setters
        void setPrice(double newPrice) { price = newPrice; }
        void setVolume(unsigned int newVolume) { volume = newVolume; }
        void setStatus(OrderStatus newStatus) { status = newStatus; }
    };

    class LimitOrder : public Order
    {
    private:

    public:
        LimitOrder(std::string id, OrderType orderType, double orderPrice, unsigned int orderVolume)
            : Order(id, orderType, orderPrice, orderVolume)
        {

        }

        void executeOrder() override
        {

        }
    };

    class MarketOrder : public Order
    {
    private:

    public:
        MarketOrder(std::string id, OrderType orderType, unsigned int orderVolume)
            : Order(id, orderType, 0.0, orderVolume)
            {

            }

        void executeOrder() override 
        {

        }
    };

    class OrderBook
    {
    private:
        std::list<std::shared_ptr<Order>> buyOrders;
        std::list<std::shared_ptr<Order>> sellOrders;

        void matchOrders()
        {

        }

    public:
        OrderBook()
        {

        }

        void addOrder(std::shared_ptr<Order> order)
        {
            if (order->getType() == OrderType::BUY)
            {
                buyOrders.push_back(order);
            }
            else if (order->getType() == OrderType::SELL)
            {
                sellOrders.push_back(order);
            }
            matchOrders();
        }

        void removeOrder(const Order& order)
        {

        }

        void displayBook() const
        {

        }
    };

    class TransactionSimulation
    {
    private:
        OrderBook orderBook;
    public:

    };
}

#endif