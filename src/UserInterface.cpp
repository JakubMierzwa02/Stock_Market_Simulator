#include "UserInterface.hpp"

namespace transaction
{
    void UserInterface::displayBalanceAndAssets()
    {
        std::cout << "Balance: " << trader.getBalance() << std::endl;
        std::cout << "Assets: " << trader.getAssets() << std::endl;
    }

    void UserInterface::placeLimitOrder()
    {
        double price;
        unsigned int volume;
        char type;

        std::cout << "Enter price: ";
        std::cin >> price;
        std::cout << "Enter volume: ";
        std::cin >> volume;
        std::cout << "Buy (b) or Sell (s)?: ";
        std::cin >> type;

        bool isBuy = (type == 'b');
        trader.placeLimitOrder(price, volume, isBuy);
    }

    void UserInterface::placeMarketOrder()
    {
        unsigned int volume;
        char type;

        std::cout << "Enter volume: ";
        std::cin >> volume;
        std::cout << "Buy (b) or Sell (s)?: ";
        std::cin >> type;

        bool isBuy = (type == 'b');
        trader.placeMarketOrder(volume, isBuy);
    }

    void UserInterface::displayMenu()
    {
        std::string choice;
        do
        {
            orderBook.displayBook();
            displayBalanceAndAssets();
            std::cout << "\n*** Market simulator ***\n";
            std::cout << "1. Place limit order\n";
            std::cout << "2. Place market order\n";
            std::cout << "3. Exit\n";
            std::cout << "Select option: ";
            std::cin >> choice;

            if (choice == "1")
            {
                placeLimitOrder();
            }
            else if (choice == "2")
            {
                placeMarketOrder();
            }
        } while (choice != "3");
        clearScreen();
    }
}