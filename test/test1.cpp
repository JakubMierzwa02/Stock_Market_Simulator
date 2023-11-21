#include <gtest/gtest.h>
#include "../src/DataImporter.hpp"

class DataImporterTest : public ::testing::Test
{
protected:
    importer::DataImporter importer;
};

TEST_F(DataImporterTest, ImportDataFromValidFile)
{
    importer.importData("../../data.csv", "CSV");
}

TEST_F(DataImporterTest, HandleNonexistentFile) 
{
    importer.importData("nonexistent.csv", "CSV");
    auto data = importer.getData();
    EXPECT_TRUE(data.empty());
}