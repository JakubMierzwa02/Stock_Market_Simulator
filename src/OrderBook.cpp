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
        while (!buyOrders.empty() && !sellOrders.empty())
        {
            bool matched = false;
            auto buyIter = buyOrders.begin();

            while (buyIter != buyOrders.end())
            {
                auto buyOrder = *buyIter;
                if (buyOrder->getVolume() == 0)
                {
                    buyOrders.erase(buyIter++);
                    continue;
                }

                auto sellIter = sellOrders.begin();
                while (sellIter != sellOrders.end())
                {
                    auto sellOrder = *sellIter;
                    if (sellOrder->getVolume() == 0)
                    {
                        sellOrders.erase(sellIter++);
                        continue;
                    }

                    if (buyOrder->getType() == OrderType::MARKET)
                    {
                        buyOrder->setPrice(sellOrder->getPrice());
                    }

                    if (sellOrder->getType() == OrderType::MARKET)
                    {
                        sellOrder->setPrice(buyOrder->getPrice());
                    }

                    if (buyOrder->getPrice() >= sellOrder->getPrice())
                    {
                        executeTrade(buyOrder, sellOrder);
                        matched = true;
                        break;
                    }
                    else
                    {
                        ++sellIter;
                    }
                }
                ++buyIter;
            }
            if (!matched)
                break;
        }
    }

    // Function to execute a trade between two orders
    void OrderBook::executeTrade(const std::shared_ptr<Order> &order1, const std::shared_ptr<Order> &order2)
    {
        unsigned int tradeVolume = std::min(order1->getVolume(), order2->getVolume());
        double tradePrice = 0.0;

        if (order1->getType() == OrderType::MARKET)
            tradePrice = order1->getPrice();
        else if (order2->getType() == OrderType::MARKET)
            tradePrice = order2->getPrice();
        else
            tradePrice = order1->getPrice();

        setLastTradePrice(tradePrice);

        // Find the traders involved in the trade
        Trader *trader1 = findTraderById(order1->getTraderId());
        Trader *trader2 = findTraderById(order2->getTraderId());

        // Execute the trade and update trader balances and assets
        if (trader1 && trader2)
        {
            double tradeAmount = tradePrice * tradeVolume;
            if (order1->getIsBuyOrder())
            {
                trader1->addAssets("BTC", tradeVolume);
                trader1->setCashBalance(trader1->getCashBalance() - tradeAmount);
                trader2->addFunds(tradeAmount);
                trader2->removeAssets("BTC", tradeVolume);
            }
            else
            {
                trader2->addAssets("BTC", tradeVolume);
                trader2->setCashBalance(trader1->getCashBalance() - tradeAmount);
                trader1->addFunds(tradeAmount);
                trader1->removeAssets("BTC", tradeVolume);
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
    Trader *OrderBook::findTraderById(const std::string &traderId)
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
            buyOrders.insert(order);
        }
        else
        {
            sellOrders.insert(order);
        }
        matchOrders();
    }

    // Function to remove an order from the order book
    void OrderBook::removeOrder(const std::shared_ptr<Order> &order)
    {
        if (order->getIsBuyOrder())
        {
            buyOrders.erase(order);
        }
        else
        {
            sellOrders.erase(order);
        }
    }

    // Function to display the current state of the order book
    void OrderBook::displayBook() const
    {
        transaction::UserInterface::clearScreen();
        std::cout << "------------------ Order Book ------------------" << std::endl;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        std::cout << "Sell Orders:" << std::endl;
        // Set text color for sell orders
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);

        for (auto orderIter = sellOrders.rbegin(); orderIter != sellOrders.rend(); ++orderIter)
        {
            auto order = *orderIter;
            std::cout << "ID: " << order->getOrderId() << ", Type: " << (order->getIsBuyOrder() ? "BUY" : "SELL")
                      << ", Price: " << order->getPrice() << ", Volume: " << order->getVolume() << std::endl;
        }
        // Reset text color
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        std::cout << "Market price: " << lastTradePrice << std::endl;

        std::cout << "Buy Orders:" << std::endl;

        // Set text color for buy orders
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);

        for (const auto &order : buyOrders)
        {
            std::cout << "ID: " << order->getOrderId() << ", Type: " << (order->getIsBuyOrder() ? "BUY" : "SELL")
                      << ", Price: " << order->getPrice() << ", Volume: " << order->getVolume() << std::endl;
        }
        // Reset text color
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        std::cout << "------------------------------------------------" << std::endl;
    }

    double OrderBook::getLastTradePrice() const
    {
        return lastTradePrice;
    }

    void OrderBook::setLastTradePrice(double price)
    {
        lastTradePrice = price;
    }
}