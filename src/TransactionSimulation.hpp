#ifndef TRANSACTIONSIMULATION_HPP
#define TRANSACTIONSIMULATION_HPP

#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <algorithm>

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
            std::cout << "Executing Limit Order: " << getOrderId() << std::endl;
            setStatus(OrderStatus::COMPLETED);
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
            std::cout << "Executing Market Order: " << getOrderId() << std::endl;
            setStatus(OrderStatus::COMPLETED);
        }
    };

    class OrderBook
    {
    private:
        std::list<std::shared_ptr<Order>> buyOrders;
        std::list<std::shared_ptr<Order>> sellOrders;
        unsigned long long nextTradeId = 1;

        std::string generateTradeId()
        {
            return "T" + std::to_string(nextTradeId++);
        }

        void matchOrders()
        {
            auto buyIter = buyOrders.begin();
            while (buyIter != buyOrders.end())
            {
                bool orderMatched = false;

                for (auto sellIter = sellOrders.begin(); sellIter != sellOrders.end();)
                {
                    if ((*buyIter)->getPrice() >= (*sellIter)->getPrice())
                    {
                        unsigned int tradeVolume = std::min((*buyIter)->getVolume(), (*sellIter)->getVolume());
                        double tradePrice = (*sellIter)->getPrice();

                        //Trade trade(generateTradeId(), (*buyIter)->getOrderId(), (*sellIter)->getOrderId(), tradePrice, tradeVolume);

                        (*buyIter)->setVolume((*buyIter)->getVolume() - tradeVolume);
                        (*sellIter)->setVolume((*sellIter)->getVolume() - tradeVolume);
                        
                        if ((*buyIter)->getVolume() == 0)
                        {
                            (*buyIter)->executeOrder();
                            buyIter = buyOrders.erase(buyIter);
                            orderMatched = true;
                        }
                        if ((*sellIter)->getVolume() == 0) 
                        {
                            (*sellIter)->executeOrder();
                            sellIter = sellOrders.erase(sellIter);
                            //orderMatched = true;
                        } 
                        else 
                        {
                            ++sellIter;
                        }

                        if (orderMatched)
                            break;
                    }
                    else
                        ++sellIter;
                }
                if (!orderMatched)
                    ++buyIter;
            }
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

        void removeOrder(const std::shared_ptr<Order>& order)
        {
            auto removeOrderFromList = [&order](std::list<std::shared_ptr<Order>>& orders)
            {
                auto it = std::find_if(orders.begin(), orders.end(), 
                               [&order](const std::shared_ptr<Order>& o) { return o->getOrderId() == order->getOrderId(); });
                if (it != orders.end()) 
                {
                    orders.erase(it);
                    return true;
                }
                return false;
            };
            if (!removeOrderFromList(buyOrders))
                removeOrderFromList(sellOrders);
        }

        void displayBook() const
        {
            std::cout << "------------------ Order Book ------------------" << std::endl;
            std::cout << "Buy Orders:" << std::endl;
            for (const auto& order : buyOrders) {
                std::cout << "ID: " << order->getOrderId() << ", Type: " << (order->getType() == OrderType::BUY ? "BUY" : "SELL") 
                        << ", Price: " << order->getPrice() << ", Volume: " << order->getVolume() 
                        << ", Status: " << (order->getStatus() == OrderStatus::PENDING ? "PENDING" : (order->getStatus() == OrderStatus::COMPLETED ? "COMPLETED" : "CANCELLED")) << std::endl;
            }

            std::cout << "Sell Orders:" << std::endl;
            for (const auto& order : sellOrders) {
                std::cout << "ID: " << order->getOrderId() << ", Type: " << (order->getType() == OrderType::BUY ? "BUY" : "SELL") 
                        << ", Price: " << order->getPrice() << ", Volume: " << order->getVolume() 
                        << ", Status: " << (order->getStatus() == OrderStatus::PENDING ? "PENDING" : (order->getStatus() == OrderStatus::COMPLETED ? "COMPLETED" : "CANCELLED")) << std::endl;
            }
            std::cout << "------------------------------------------------" << std::endl;    
        }
    };

    class Trader
    {
    private:
        double balance;
        std::vector<std::shared_ptr<Order>> openOrders;
        OrderBook& orderBook;
        unsigned long long nextOrderId = 1;

        std::string generateOrderId()
        {
            return "_O" + std::to_string(nextOrderId++);
        }

    public:
        Trader(double initialBalance, OrderBook& book)
            : balance(initialBalance), orderBook(book)
        {

        }

        void placeLimitOrder(double price, unsigned int volume, OrderType type)
        {
            auto order = std::make_shared<LimitOrder>(generateOrderId(), type, price, volume);
            openOrders.push_back(order);
            orderBook.addOrder(order);
        }

        void placeMarketOrder(unsigned int volume, OrderType type)
        {
            auto order = std::make_shared<MarketOrder>(generateOrderId(), type, volume);
            openOrders.push_back(order);
            orderBook.addOrder(order);
        }

        void cancelOrder(const std::shared_ptr<Order>& order)
        {
            auto it = std::find_if(openOrders.begin(), openOrders.end(),
                                    [&order](const std::shared_ptr<Order>& o) { return o->getOrderId() == order->getOrderId(); });

            if (it != openOrders.end())
            {
                orderBook.removeOrder(*it);
                openOrders.erase(it);
                std::cout << "Order " << order->getOrderId() << " cancelled." << std::endl;
            }
            else
            {
                std::cout << "Order " << order->getOrderId() << " not found." << std::endl;
            }
        }

        // Getters / Setters
        double getBalance() const { return balance; }
        void setBalance(double newBalance) { balance = newBalance; }
    };

    class Trade 
    {
    private:
        std::string tradeId;
        std::string buyOrderId;
        std::string sellOrderId;
        double tradePrice;
        unsigned int tradeVolume;

    public:
        Trade(std::string id, std::string buyId, std::string sellId, double price, unsigned int volume)
            : tradeId(id), buyOrderId(buyId), sellOrderId(sellId), tradePrice(price), tradeVolume(volume)
        {

        }

        // Getters
        std::string getTradeId() const { return tradeId; }
        std::string getBuyOrderId() const { return buyOrderId; }
        std::string getSellOrderId() const { return sellOrderId; }
        double getTradePrice() const { return tradePrice; }
        unsigned int getTradeVolume() const { return tradeVolume; }

        // Setters
        void setTradePrice(double newPrice) { tradePrice = newPrice; }
        void setTradeVolume(unsigned int newVolume) { tradeVolume = newVolume; }
    };

    class TransactionSimulation
    {
    private:
        OrderBook orderBook;
        std::vector<Trader> traders;
    public:
        TransactionSimulation()
        {

        }

        void addTrader(double initialBalance)
        {
            traders.emplace_back(initialBalance, orderBook);
        }

        void runSimulation()
        {
            addTrader(10000);
            addTrader(15000);
            addTrader(20000);
            
            traders[0].placeLimitOrder(100.0, 20, OrderType::BUY);
            traders[1].placeLimitOrder(90.0, 30, OrderType::SELL);
            orderBook.displayBook();
        }
    };
}

#endif