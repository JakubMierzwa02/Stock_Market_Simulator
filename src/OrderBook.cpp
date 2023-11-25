#include "OrderBook.hpp"

namespace transaction
{
    std::string OrderBook::generateTradeId()
    {
        return "T" + std::to_string(nextTradeId++);
    }

    void OrderBook::matchOrders()
    {
        auto buyIter = buyOrders.begin();
        while (buyIter != buyOrders.end())
        {
            bool matched = false;

            if ((*buyIter)->getType() == OrderType::MARKET)
            {
                auto sellIter = sellOrders.begin();
                while (sellIter != sellOrders.end() && (*buyIter)->getVolume() > 0)
                {
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

        auto sellIter = sellOrders.begin();
        while (sellIter != sellOrders.end())
        {
            bool matched = false;

            if ((*sellIter)->getType() == OrderType::MARKET)
            {
                auto buyIter = buyOrders.begin();
                while (buyIter != buyOrders.end() && (*sellIter)->getVolume() > 0)
                {
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

    void OrderBook::executeTrade(std::shared_ptr<Order> &order1, std::shared_ptr<Order> &order2)
    {
        unsigned int tradeVolume = std::min(order1->getVolume(), order2->getVolume());
        double tradePrice = order2->getPrice();

        Trader* trader1 = findTraderById(order1->getTraderId());
        Trader* trader2 = findTraderById(order2->getTraderId());

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

            Trade trade(generateTradeId(), order1->getOrderId(), order2->getOrderId(), tradePrice, tradeVolume);
            order1->setVolume(order1->getVolume() - tradeVolume);
            order2->setVolume(order2->getVolume() - tradeVolume);
        }
    }

    void OrderBook::registerTrader(const std::shared_ptr<Trader> &trader)
    {
        traders[trader->getTraderId()] = trader;
    }

    Trader* OrderBook::findTraderById(const std::string &traderId)
    {
        auto it = traders.find(traderId);
        if (it != traders.end())
        {
            return it->second.get();
        }
        return nullptr;
    }

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

    void OrderBook::displayBook() const
    {
        system("cls");
        std::cout << "------------------ Order Book ------------------" << std::endl;
        std::cout << "Buy Orders:" << std::endl;
        for (const auto &order : buyOrders)
        {
            std::cout << "ID: " << order->getOrderId() << ", Type: " << (order->getIsBuyOrder() ? "BUY" : "SELL")
                      << ", Price: " << order->getPrice() << ", Volume: " << order->getVolume()
                      << ", Status: " << (order->getStatus() == OrderStatus::PENDING ? "PENDING" : (order->getStatus() == OrderStatus::COMPLETED ? "COMPLETED" : "CANCELLED")) << std::endl;
        }

        std::cout << "Sell Orders:" << std::endl;
        for (const auto &order : sellOrders)
        {
            std::cout << "ID: " << order->getOrderId() << ", Type: " << (order->getIsBuyOrder() ? "BUY" : "SELL")
                      << ", Price: " << order->getPrice() << ", Volume: " << order->getVolume()
                      << ", Status: " << (order->getStatus() == OrderStatus::PENDING ? "PENDING" : (order->getStatus() == OrderStatus::COMPLETED ? "COMPLETED" : "CANCELLED")) << std::endl;
        }
        std::cout << "------------------------------------------------" << std::endl;
    }
}