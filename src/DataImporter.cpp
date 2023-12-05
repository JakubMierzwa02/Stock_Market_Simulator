#include "DataImporter.hpp"

namespace importer
{
    void DataImporter::importData(const std::string &source, const std::string &type)
    {
        if (type == "CSV")
        {
            csvImporter = std::make_unique<importer::CSVImporter>();
            csvImporter->importData(source);
            importedData = csvImporter->getData();
        }
    }

    void DataImporter::validateData()
    {
        for (auto& data : importedData) 
        {
            if (!dataValidator.validate(data)) 
            {
                std::cerr << "Data validation error." << std::endl;
            }
        }
    }

    const std::vector<importer::StockData>& DataImporter::getData() const
    {
        return csvImporter->getData();
    }
}