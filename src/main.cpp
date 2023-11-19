#include <iostream>
#include "DataImporter.hpp"

int main()
{
    CSVImporter importer;
    importer.importData("../data.csv");

    const auto& data = importer.getData();
    for (const auto& row : data) {
        std::cout << "Data: " << row.date
                  << ", Symbol: " << row.symbol
                  << ", Open: " << row.open
                  << ", High: " << row.high
                  << ", Low: " << row.low
                  << ", Close: " << row.close
                  << ", Volume: " << row.volume << std::endl;
    }

    return 0;
}