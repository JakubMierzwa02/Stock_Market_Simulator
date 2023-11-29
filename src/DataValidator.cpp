#include "DataValidator.hpp"

namespace importer
{
    // Function to validate the format of a date string.
    // It checks if the date is in the format YYYY-MM-DD using a regular expression.
    bool DataValidator::validateDate(const std::string& date)
    {
        std::regex datePattern(R"(^\d{4}-\d{2}-\d{2}$)");
        return std::regex_match(date, datePattern);
    }

    // Function to validate a price value.
    // It checks if the price is greater than 0.0.
    bool DataValidator::validatePrice(double price)
    {
        return price > 0.0;
    }

    // Function to validate a volume value.
    // It checks if the volume is non-negative.
    bool DataValidator::validateVolume(long volume)
    {
        return volume >= 0;
    }

    // Function to validate a StockData object.
    // It checks if all components of the StockData (date, open, high, low, close prices, and volume) are valid
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