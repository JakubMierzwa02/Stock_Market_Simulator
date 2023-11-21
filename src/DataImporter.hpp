#ifndef DATAIMPORTER_HPP
#define DATAIMPORTER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <stdexcept>

namespace importer
{
    struct StockData
    {
        std::string date;
        std::string symbol;
        double open;
        double high;
        double low;
        double close;
        long volume;
    };

    class IDataImporter
    {
    public:
        virtual void importData(const std::string& source) = 0;
        virtual void parseData() = 0;
    };

    class CSVImporter : public IDataImporter
    {
    private:
        std::string filePath;
        std::vector<StockData> data;

        void clearData()
        {
            data.clear();
        }

        StockData parseLine(const std::string& line)
        {
            std::istringstream iss(line);
            std::string token;
            StockData stockData;

            std::getline(iss, stockData.date, ',');
            std::getline(iss, stockData.symbol, ',');
            std::getline(iss, token, ','); stockData.open = std::stod(token);
            std::getline(iss, token, ','); stockData.high = std::stod(token);
            std::getline(iss, token, ','); stockData.low = std::stod(token);
            std::getline(iss, token, ','); stockData.close = std::stod(token);
            std::getline(iss, token, ','); stockData.volume = std::stol(token);

            return stockData;
        }
    public:
        CSVImporter() : filePath(""), data()
        {

        }

        ~CSVImporter()
        {
            clearData();
        }

        void importData(const std::string& source) override
        {
            filePath = source;
            std::ifstream file(filePath);
            if (!file.is_open())
            {
                std::cerr << "Cannot open the file: " << filePath << std::endl;
                return;
            }

            std::string line;
            std::getline(file, line);
            while (std::getline(file, line))
            {
                try 
                {
                    StockData stockData = parseLine(line);
                    data.push_back(stockData);
                } 
                catch (const std::exception& e) 
                {
                    std::cerr << "Error while parsing line: " << e.what() << std::endl;
                }
            }

            file.close();
        }

        void parseData() override
        {

        }

        const std::vector<StockData>& getData() const
        {
            return data;
        }
    };

    class DataImporter
    {
    private:
        std::unique_ptr<CSVImporter> csvImporter;
        //DataValidator dataValidator;
        std::vector<StockData> importedData;

    public:
        DataImporter()
        {
            
        }

        ~DataImporter()
        {

        }

        void importData(const std::string& source, const std::string& type)
        {
            if (type == "CSV")
            {
                csvImporter = std::make_unique<CSVImporter>();
                csvImporter->importData(source);
                importedData = csvImporter->getData();
            }
        }

        const std::vector<StockData>& getData() const
        {
            return csvImporter->getData();
        }
    };
}

#endif