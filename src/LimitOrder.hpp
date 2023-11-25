#ifndef LIMITORDER_HPP
#define LIMITORDER_HPP

#include "Order.hpp"

namespace transaction
{
    class LimitOrder : public Order
    {
    private:

    public:
        LimitOrder(std::string id, std::string traderId, bool isBuy, double orderPrice, unsigned int orderVolume)
            : Order(id, traderId, OrderType::LIMIT, isBuy, orderPrice, orderVolume)
        {

        }

        void executeOrder() override
        {
            std::cout << "Executing Limit Order: " << getOrderId() << std::endl;
            setStatus(OrderStatus::COMPLETED);
        }
    };
}

#endif