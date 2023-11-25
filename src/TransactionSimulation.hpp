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
        std::vector<Trader> traders;
    public:
        TransactionSimulation()
        {

        }

        void addTrader(double initialBalance)
        {
            traders.emplace_back(initialBalance, &orderBook);
        }

        void runSimulation()
        {
            
        }
    };
}

#endif