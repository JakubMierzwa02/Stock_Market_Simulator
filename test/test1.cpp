#include <gtest/gtest.h>
#include "../src/DataImporter.hpp"

class CSVImporterTest : public ::testing::Test
{
protected:
    CSVImporter importer;
};

TEST_F(CSVImporterTest, ImportDataFromValidFile)
{
    importer.importData("../../data.csv");
    auto data = importer.getData();
    EXPECT_FALSE(data.empty());
}

TEST_F(CSVImporterTest, HandleNonexistentFile) 
{
    importer.importData("nonexistent.csv");
    auto data = importer.getData();
    EXPECT_TRUE(data.empty());
}