#ifndef USERINTERFACE_HPP
#define USERINTERFACE_HPP

#include "Trader.hpp"
#include "OrderBook.hpp"

#include <windows.h>
#include <memory>

namespace transaction
{
    class Trader;
    class OrderBook;

    class UserInterface
    {
    private:
        std::shared_ptr<Trader> trader;
        OrderBook& orderBook;

        void displayBalanceAndAssets();
        void placeLimitOrder();
        void placeMarketOrder();

    public:
        UserInterface(std::shared_ptr<Trader> t, OrderBook& o) : trader(t), orderBook(o) { }

        static void clearScreen()
        {
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
        }
        
        void displayMenu();
    };
}

#endif