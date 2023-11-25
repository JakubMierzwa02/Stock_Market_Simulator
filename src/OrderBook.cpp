#include "OrderBook.hpp"

namespace transaction
{
    // Function to generate a unique trade ID for each trade
    std::string OrderBook::generateTradeId()
    {
        return "T" + std::to_string(nextTradeId++);
    }

    // Function to match buy and sell orders in the order book
    void OrderBook::matchOrders()
    {
        // Iterate through buy orders to find matches with sell orders
        auto buyIter = buyOrders.begin();
        while (buyIter != buyOrders.end())
        {
            bool matched = false;

            // Check if the buy order is a market order
            if ((*buyIter)->getType() == OrderType::MARKET)
            {
                auto sellIter = sellOrders.begin();
                while (sellIter != sellOrders.end() && (*buyIter)->getVolume() > 0)
                {
                    // Match with limit or market sell orders
                    if ((*sellIter)->getType() == OrderType::LIMIT || (*sellIter)->getType() == OrderType::MARKET)
                    {
                        executeTrade(*buyIter, *sellIter);
                        matched = true;

                        if ((*sellIter)->getVolume() == 0)
                        {
                            sellIter = sellOrders.erase(sellIter);
                        }
                        else
                        {
                            ++sellIter;
                        }
                    }
                    else
                    {
                        ++sellIter;
                    }
                }

                if (matched)
                {
                    buyIter = buyOrders.erase(buyIter);
                }
                else
                {
                    ++buyIter;
                }
            }
            else
            {
                ++buyIter;
            }
        }

        // Iterate through sell orders to find matches with buy orders
        auto sellIter = sellOrders.begin();
        while (sellIter != sellOrders.end())
        {
            bool matched = false;

            // Check if the sell order is a market order
            if ((*sellIter)->getType() == OrderType::MARKET)
            {
                auto buyIter = buyOrders.begin();
                while (buyIter != buyOrders.end() && (*sellIter)->getVolume() > 0)
                {
                    // Match with limit or market buy orders
                    if ((*buyIter)->getType() == OrderType::LIMIT || (*buyIter)->getType() == OrderType::MARKET)
                    {
                        executeTrade(*sellIter, *buyIter);
                        matched = true;

                        if ((*buyIter)->getVolume() == 0)
                        {
                            buyIter = buyOrders.erase(buyIter);
                        }
                        else
                        {
                            ++buyIter;
                        }
                    }
                    else
                    {
                        ++buyIter;
                    }
                }

                if (matched)
                {
                    sellIter = sellOrders.erase(sellIter);
                }
                else
                {
                    ++sellIter;
                }
            }
            else
            {
                ++sellIter;
            }
        }
    }

    // Function to execute a trade between two orders
    void OrderBook::executeTrade(std::shared_ptr<Order> &order1, std::shared_ptr<Order> &order2)
    {
        unsigned int tradeVolume = std::min(order1->getVolume(), order2->getVolume());
        double tradePrice = order2->getPrice();

        // Find the traders involved in the trade
        Trader* trader1 = findTraderById(order1->getTraderId());
        Trader* trader2 = findTraderById(order2->getTraderId());

        // Execute the trade and update trader balances and assets
        if (trader1 && trader2)
        {
            double tradeAmount = tradePrice * tradeVolume;
            if (order1->getIsBuyOrder())
            {
                trader1->addAssets(tradeVolume);
                trader2->addFunds(tradeAmount);
            }
            else
            {
                trader2->addAssets(tradeVolume);
                trader1->addFunds(tradeAmount);
            }

            // Record the trade and update order volumes
            Trade trade(generateTradeId(), order1->getOrderId(), order2->getOrderId(), tradePrice, tradeVolume);
            order1->setVolume(order1->getVolume() - tradeVolume);
            order2->setVolume(order2->getVolume() - tradeVolume);
        }
    }

    // Function to register a trader in the order book
    void OrderBook::registerTrader(const std::shared_ptr<Trader> &trader)
    {
        traders[trader->getTraderId()] = trader;
    }

    // Function to find a trader by their ID
    Trader* OrderBook::findTraderById(const std::string &traderId)
    {
        auto it = traders.find(traderId);
        if (it != traders.end())
        {
            return it->second.get();
        }
        return nullptr;
    }

    // Function to add an order to the order book
    void OrderBook::addOrder(std::shared_ptr<Order> order)
    {
        if (order->getIsBuyOrder())
        {
            buyOrders.push_back(order);
        }
        else
        {
            sellOrders.push_back(order);
        }
        matchOrders();
    }

    // Function to remove an order from the order book
    void OrderBook::removeOrder(const std::shared_ptr<Order> &order)
    {
        auto removeOrderFromList = [&order](std::list<std::shared_ptr<Order>> &orders)
        {
            auto it = std::find_if(orders.begin(), orders.end(),
                                   [&order](const std::shared_ptr<Order> &o)
                                   { return o->getOrderId() == order->getOrderId(); });
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

    // Function to display the current state of the order book
    void OrderBook::displayBook() const
    {
        transaction::UserInterface::clearScreen();
        std::cout << "------------------ Order Book ------------------" << std::endl;
        std::cout << "Buy Orders:" << std::endl;

        // Set text color for buy orders
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

        for (const auto &order : buyOrders)
        {
            std::cout << "ID: " << order->getOrderId() << ", Type: " << (order->getIsBuyOrder() ? "BUY" : "SELL")
                      << ", Price: " << order->getPrice() << ", Volume: " << order->getVolume()
                      << ", Status: " << (order->getStatus() == OrderStatus::PENDING ? "PENDING" : (order->getStatus() == OrderStatus::COMPLETED ? "COMPLETED" : "CANCELLED")) << std::endl;
        }
        // Reset text color
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        std::cout << "Sell Orders:" << std::endl;
        // Set text color for sell orders
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);

        for (const auto &order : sellOrders)
        {
            std::cout << "ID: " << order->getOrderId() << ", Type: " << (order->getIsBuyOrder() ? "BUY" : "SELL")
                      << ", Price: " << order->getPrice() << ", Volume: " << order->getVolume()
                      << ", Status: " << (order->getStatus() == OrderStatus::PENDING ? "PENDING" : (order->getStatus() == OrderStatus::COMPLETED ? "COMPLETED" : "CANCELLED")) << std::endl;
        }
        // Reset text color
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        std::cout << "------------------------------------------------" << std::endl;
    }
}