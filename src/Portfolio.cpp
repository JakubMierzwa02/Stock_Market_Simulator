#include "Portfolio.hpp"

namespace portfolio
{
    std::string Asset::getAssetId() const
    {
        return assetId;
    }

    unsigned int Asset::getQuantity() const
    {
        return quantity;
    }

    void Asset::updateQuantity(int newQuantity)
    {
        quantity = newQuantity;
    }

    void Portfolio::addAsset(const Asset &asset)
    {
        auto it = assets.find(asset.getAssetId());
        if (it != assets.end())
        {
            it->second.updateQuantity(it->second.getQuantity() + asset.getQuantity());
        }
        else
        {
            assets[asset.getAssetId()] = asset;
        }
    }

    void Portfolio::removeAsset(const std::string &assetId)
    {
        auto it = assets.find(assetId);
        if (it != assets.end())
        {
            assets.erase(it);
        }
        else
        {
            throw std::runtime_error("Asset not found in portfolio.");
        }
    }

    unsigned int Portfolio::getAssetQuantity(const std::string &assetId) const
    {
        auto it = assets.find(assetId);
        if (it != assets.end())
        {
            return it->second.getQuantity();
        }
        else
        {
            return 0;
        }
    }

    void Portfolio::updateAssetQuantity(const std::string &assetId, unsigned int quantityChange)
    {
        auto it = assets.find(assetId);
        if (it != assets.end())
        {
            int newQuantity = it->second.getQuantity() + quantityChange;
            if (newQuantity >= 0)
            {
                it->second.updateQuantity(newQuantity);
            }
            else
            {
                throw std::runtime_error("Insufficient quantity for update.");
            }
        }
        else
        {
            throw std::runtime_error("Asset not found in portfolio.");
        }
    }

    void Portfolio::addCash(double amount)
    {
        cash += amount;
    }

    double Portfolio::getCashBalance() const
    {
        return cash;
    }

    void Portfolio::setCashBalance(double amount)
    {
        cash = amount;
    }
}