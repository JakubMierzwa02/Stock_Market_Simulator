#ifndef MARKETORDER_HPP
#define MARKETORDER_HPP

#include "Order.hpp"

namespace transaction
{
    class MarketOrder : public Order
    {
    private:

    public:
        MarketOrder(std::string id, std::string traderId, bool isBuy, double orderPrice, unsigned int orderVolume)
            : Order(id, traderId, OrderType::MARKET, isBuy, orderPrice, orderVolume) { }
    };
}

#endif