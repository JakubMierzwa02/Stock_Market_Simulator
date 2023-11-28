#ifndef IDATAIMPORTER_HPP
#define IDATAIMPORTER_HPP

#include <string>

namespace importer
{
    class IDataImporter
    {
    public:
        virtual void importData(const std::string& source) = 0;
        //virtual void parseData() = 0;
    };
}

#endif