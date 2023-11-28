#include <gtest/gtest.h>
#include "../src/DataImporter.hpp"

class DataImporterTest : public ::testing::Test
{
protected:
    importer::DataImporter importer;
};

class DataValidatorTest : public ::testing::Test
{
protected:
    importer::DataValidator validator;
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

TEST_F(DataValidatorTest, ValidateDate)
{
    EXPECT_TRUE(validator.validateDate("2023-01-01"));
    EXPECT_FALSE(validator.validateDate("01-01-2023"));
    EXPECT_FALSE(validator.validateDate("2023/01/01"));
}

TEST_F(DataValidatorTest, ValidatePrice) 
{
    EXPECT_TRUE(validator.validatePrice(100.50));
    EXPECT_FALSE(validator.validatePrice(-1.00));
}

TEST_F(DataValidatorTest, ValidateVolume) 
{
    EXPECT_TRUE(validator.validateVolume(1000));
    EXPECT_FALSE(validator.validateVolume(-100));
}