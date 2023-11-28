#ifndef DATAIMPORTER_HPP
#define DATAIMPORTER_HPP

#include "CSVImporter.hpp"
#include "StockData.hpp"
#include "DataValidator.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <stdexcept>

namespace importer
{
    class CSVImporter;

    class DataImporter
    {
    private:
        std::unique_ptr<importer::CSVImporter> csvImporter;
        DataValidator dataValidator;
        std::vector<StockData> importedData;

    public:
        DataImporter() { }
        ~DataImporter() { }

        void importData(const std::string& source, const std::string& type);
        void validateData();
        const std::vector<StockData>& getData() const;
    };
}

#endif