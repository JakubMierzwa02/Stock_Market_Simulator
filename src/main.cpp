#include <iostream>
#include "DataImporter.hpp"

int main()
{
    importer::DataImporter importer;
    importer.importData("../data.csv", "CSV");

    const auto& data = importer.getData();
    for (const auto& row : data) 
    {
        std::cout << "Date: " << row.date
                  << ", Symbol: " << row.symbol
                  << ", Open: " << row.open
                  << ", High: " << row.high
                  << ", Low: " << row.low
                  << ", Close: " << row.close
                  << ", Volume: " << row.volume << std::endl;
    }

    return 0;
}