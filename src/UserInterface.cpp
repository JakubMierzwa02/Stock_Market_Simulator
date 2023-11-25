#include "UserInterface.hpp"

namespace transaction
{
    // Function to display the current balance and assets of the trader
    void UserInterface::displayBalanceAndAssets()
    {
        std::cout << "Balance: " << trader->getBalance() << std::endl;
        std::cout << "Assets: " << trader->getAssets() << std::endl;
    }

    // Function to handle placing a limit order
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

        // Place the limit order through trader object
        trader->placeLimitOrder(price, volume, isBuy);
    }

    // Function to handle placing a market order
    void UserInterface::placeMarketOrder()
    {
        unsigned int volume;
        char type;

        std::cout << "Enter volume: ";
        std::cin >> volume;
        std::cout << "Buy (b) or Sell (s)?: ";
        std::cin >> type;

        bool isBuy = (type == 'b');

        // Place the market order through trader object
        trader->placeMarketOrder(volume, isBuy);
    }

    // Function to display the main menu of the user interface
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
            Sleep(1000);
        } while (choice != "3");
        clearScreen();
    }
}