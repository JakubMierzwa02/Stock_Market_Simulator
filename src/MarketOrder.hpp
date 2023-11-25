#ifndef MARKETORDER_HPP
#define MARKETORDER_HPP

#include "Order.hpp"

namespace transaction
{
    class MarketOrder : public Order
    {
    private:

    public:
        MarketOrder(std::string id, std::string traderId, bool isBuy, unsigned int orderVolume)
            : Order(id, traderId, OrderType::MARKET, isBuy, 0.0, orderVolume)
            {

            }

        void executeOrder() override 
        {
            std::cout << "Executing Market Order: " << getOrderId() << std::endl;
            setStatus(OrderStatus::COMPLETED);
        }
    };
}

#endif