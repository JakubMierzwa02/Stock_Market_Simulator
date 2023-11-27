#ifndef TRANSACTIONSIMULATION_HPP
#define TRANSACTIONSIMULATION_HPP

#include "Trader.hpp"
#include "OrderBook.hpp"

namespace transaction
{
    class TransactionSimulation
    {
    private:
        OrderBook orderBook;
        std::map<std::string, std::shared_ptr<Trader>> traders;
    public:
        TransactionSimulation()
        {

        }

        std::map<std::string, std::shared_ptr<Trader>> createTraders(int numberOfTraders) 
        {
            
        }

        void simulateMarket(int numberOfTraders, int duration)
        {
            
        }
    };
}

#endif