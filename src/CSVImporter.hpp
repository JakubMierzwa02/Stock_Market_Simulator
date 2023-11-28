#ifndef CSVIMPORTER_HPP
#define CSVIMPORTER_HPP

#include "DataImporter.hpp"
#include "IDataImporter.hpp"
#include "StockData.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

namespace importer
{
    class DataImporter;
    struct StockData;

    class CSVImporter : public IDataImporter
    {
    private:
        std::string filePath;
        std::vector<importer::StockData> data;

        void clearData();
        importer::StockData parseLine(const std::string &line);

    public:
        CSVImporter() : filePath(""), data() {}
        ~CSVImporter() { clearData(); }

        void importData(const std::string &source) override
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
                    importer::StockData stockData = parseLine(line);
                    data.push_back(stockData);
                }
                catch (const std::exception &e)
                {
                    std::cerr << "Error while parsing line: " << e.what() << std::endl;
                }
            }

            file.close();
        }

        const std::vector<importer::StockData> &getData() const;
    };
}

#endif