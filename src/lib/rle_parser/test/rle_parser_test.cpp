#include <gtest/gtest.h>
#include "rle_parser.h"


TEST(RLE_Parser_get_rle_test, RLEParserGTest)
{
    int width = 2, height = 2;
    std::string rle = "W 1 B 1 W 1 B 1";
    RLEParser parser = RLEParser(width, height, rle);
    ASSERT_EQ(parser.get_rle(), rle);
}

TEST(RLE_Parser_get_distrib_rows_pattern_test, RLEParserGTest)
{
    int width = 2, height = 2;
    std::string rle = "W 2 B 2";
    std::vector<int> expected_vert_hist = { 1, 1 };
    std::vector<int> expected_horz_hist = { 0, 2 };

    RLEParser parser = RLEParser(width, height, rle);
    parser.parse_source(std::make_shared<Grid>(Grid(width, height)));
    RegionOfInterest roi = parser.get_roi();
    int mismatch;

    mismatch = 0;
    std::vector<int> actual_vert_hist = roi.get_vertical_distrib();

    for (int i = 0; i < expected_vert_hist.size(); i++)
    {
        if (expected_vert_hist[i] != actual_vert_hist[i])
            mismatch++;
    }
    ASSERT_EQ(mismatch, 0);

    mismatch = 0;
    std::vector<int> actual_horz_hist = roi.get_horizontal_distrib();

    for (int i = 0; i < expected_vert_hist.size(); i++)
    {
        if (expected_horz_hist[i] != actual_horz_hist[i])
            mismatch++;
    }
    ASSERT_EQ(mismatch, 0);
}

TEST(RLE_Parser_get_distrib_columns_pattern_test, RLEParserGTest)
{
    int width = 2, height = 2;
    std::string rle = "W 1 B 1 W 1 B 1";
    std::vector<int> expected_vert_hist = { 0, 2 };
    std::vector<int> expected_horz_hist = { 1, 1 };

    RLEParser parser = RLEParser(width, height, rle);
    parser.parse_source(std::make_shared<Grid>(Grid(width, height)));
    RegionOfInterest roi = parser.get_roi();
    int mismatch;

    mismatch = 0;
    std::vector<int> actual_vert_hist = roi.get_vertical_distrib();

    for (int i = 0; i < expected_vert_hist.size(); i++)
    {
        if (expected_vert_hist[i] != actual_vert_hist[i])
            mismatch++;
    }
    ASSERT_EQ(mismatch, 0);

    mismatch = 0;
    std::vector<int> actual_horz_hist = roi.get_horizontal_distrib();

    for (int i = 0; i < expected_vert_hist.size(); i++)
    {
        if (expected_horz_hist[i] != actual_horz_hist[i])
            mismatch++;
    }
    ASSERT_EQ(mismatch, 0);
}

TEST(RLE_Parser_get_distrib_checkerboard_pattern_test, RLEParserGTest)
{
    int width = 2, height = 2;
    std::string rle = "W 1 B 2 W 1";
    std::vector<int> expected_vert_hist = { 1, 1 };
    std::vector<int> expected_horz_hist = { 1, 1 };

    RLEParser parser = RLEParser(width, height, rle);
    parser.parse_source(std::make_shared<Grid>(Grid(width, height)));
    RegionOfInterest roi = parser.get_roi();
    
    int mismatch;

    mismatch = 0;
    std::vector<int> actual_vert_hist = roi.get_vertical_distrib();

    for (int i = 0; i < expected_vert_hist.size(); i++)
    {
        if (expected_vert_hist[i] != actual_vert_hist[i])
            mismatch++;
    }
    ASSERT_EQ(mismatch, 0);

    mismatch = 0;
    std::vector<int> actual_horz_hist = roi.get_horizontal_distrib();

    for (int i = 0; i < expected_vert_hist.size(); i++)
    {
        if (expected_horz_hist[i] != actual_horz_hist[i])
            mismatch++;
    }
    ASSERT_EQ(mismatch, 0);
}