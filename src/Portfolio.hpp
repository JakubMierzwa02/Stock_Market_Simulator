#ifndef PORTFOLIO_HPP
#define PORTFOLIO_HPP

#include <map>
#include <string>
#include <stdexcept>

namespace portfolio
{
    class Asset
    {
    private:
        std::string assetId;
        unsigned int quantity;

    public:
        Asset() { }
        Asset(const std::string& id, unsigned int qty) : assetId(id), quantity(qty) { }

        std::string getAssetId() const;
        unsigned int getQuantity() const;
        void updateQuantity(int newQuantity);
    };

    class Portfolio
    {
    private:
        std::map<std::string, Asset> assets;
        double cash;

    public:
        Portfolio() : cash(0.0) { }

        void addAsset(const Asset& asset);
        void removeAsset(const std::string& assetId);
        unsigned int getAssetQuantity(const std::string& assetId) const;
        void updateAssetQuantity(const std::string& assetId, unsigned int quantityChange);
        void addCash(double amount);
        double getCashBalance() const;
        void setCashBalance(double amount);
    };
}

#endif