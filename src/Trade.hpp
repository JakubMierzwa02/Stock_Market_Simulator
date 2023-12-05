#ifndef TRADE_HPP
#define TRADE_HPP

#include <string>

namespace transaction
{
    class Trade 
    {
    private:
        std::string tradeId;
        std::string buyOrderId;
        std::string sellOrderId;
        double tradePrice;
        unsigned int tradeVolume;

    public:
        Trade(std::string id, std::string buyId, std::string sellId, double price, unsigned int volume)
            : tradeId(id), buyOrderId(buyId), sellOrderId(sellId), tradePrice(price), tradeVolume(volume)
        {

        }

        // Getters
        std::string getTradeId() const { return tradeId; }
        std::string getBuyOrderId() const { return buyOrderId; }
        std::string getSellOrderId() const { return sellOrderId; }
        double getTradePrice() const { return tradePrice; }
        unsigned int getTradeVolume() const { return tradeVolume; }

        // Setters
        void setTradePrice(double newPrice) { tradePrice = newPrice; }
        void setTradeVolume(unsigned int newVolume) { tradeVolume = newVolume; }
    };
}

#endif