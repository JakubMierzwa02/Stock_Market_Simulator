#include "DataValidator.hpp"

namespace importer
{
    bool DataValidator::validateDate(const std::string& date)
    {
        std::regex datePattern(R"(^\d{4}-\d{2}-\d{2}$)");
        return std::regex_match(date, datePattern);
    }

    bool DataValidator::validatePrice(double price)
    {
        return price > 0.0;
    }

    bool DataValidator::validateVolume(long volume)
    {
        return volume >= 0;
    }

    bool DataValidator::validate(const StockData& data)
    {
        return validateDate(data.date) &&
            validatePrice(data.open) &&
            validatePrice(data.high) &&
            validatePrice(data.low) &&
            validatePrice(data.close) &&
            validateVolume(data.volume);
    }
}