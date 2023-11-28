#include "CSVImporter.hpp"

namespace importer
{
    void CSVImporter::clearData()
    {
        data.clear();
    }

    StockData CSVImporter::parseLine(const std::string &line)
    {
        std::istringstream iss(line);
        std::string token;
        StockData stockData;

        std::getline(iss, stockData.date, ',');
        std::getline(iss, stockData.symbol, ',');
        std::getline(iss, token, ',');
        stockData.open = std::stod(token);
        std::getline(iss, token, ',');
        stockData.high = std::stod(token);
        std::getline(iss, token, ',');
        stockData.low = std::stod(token);
        std::getline(iss, token, ',');
        stockData.close = std::stod(token);
        std::getline(iss, token, ',');
        stockData.volume = std::stol(token);

        return stockData;
    }

    const std::vector<StockData>& CSVImporter::getData() const
    {
        return data;
    }
}