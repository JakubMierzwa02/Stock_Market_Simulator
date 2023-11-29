#ifndef DATAVALIDATOR_HPP
#define DATAVALIDATOR_HPP

#include "StockData.hpp"

#include <regex>

namespace importer
{
    class DataValidator
    {
    public:
        bool validateDate(const std::string& date);
        bool validatePrice(double price);
        bool validateVolume(long volume);

    public:
        DataValidator() { }
        bool validate(const StockData& data);
    };
}

#endif