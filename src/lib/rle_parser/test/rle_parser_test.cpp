#include <gtest/gtest.h>
#include "rle_parser.h"
#include <iostream>
TEST(RLE_Parser_get_rle_test, RLEParserGTest)
{
    int width = 2, height = 2;
    std::string rle = "W 1 B 1 W 1 B 1";
    RLEParser parser = RLEParser(width, height, rle);
    ASSERT_EQ(parser.get_rle(), rle);
}

TEST(RLE_Parser_get_roi_rows_pattern_test, RLEParserGTest)
{
    int width = 2, height = 2;
    std::string rle = "W 2 B 2";
    std::vector<std::vector<bool>> expected_data = {{true, true}, {false, false}};

    RLEParser parser = RLEParser(width, height, rle);
    RegionOfInterest roi = parser.get_roi();
    Grid grid = roi.get_grid();
    
    ASSERT_EQ(grid.get_width(), width);
    ASSERT_EQ(grid.get_height(), height);

    for (int y = 0; y < expected_data.size(); y++)
    {
        for (int x = 0; x < expected_data[0].size(); x++)
        {
            ASSERT_EXIT(
                (grid.get_pixel(x, y), exit(0)),
                ::testing::ExitedWithCode(0),
                ".*"
            );
            ASSERT_EQ(grid.get_pixel(x, y), expected_data[y][x]);
        }
    }
}

TEST(RLE_Parser_get_roi_columns_pattern_test, RLEParserGTest)
{
    int width = 2, height = 2;
    std::string rle = "W 1 B 1 W 1 B 1";
    std::vector<std::vector<bool>> expected_data = {{true, false}, {true, false}};

    RLEParser parser = RLEParser(width, height, rle);
    RegionOfInterest roi = parser.get_roi();
    Grid grid = roi.get_grid();
    
    ASSERT_EQ(grid.get_width(), width);
    ASSERT_EQ(grid.get_height(), height);

    for (int y = 0; y < expected_data.size(); y++)
    {
        for (int x = 0; x < expected_data[0].size(); x++)
        {
            ASSERT_EXIT(
                (grid.get_pixel(x, y), exit(0)),
                ::testing::ExitedWithCode(0),
                ".*"
            );
            ASSERT_EQ(grid.get_pixel(x, y), expected_data[y][x]);
        }
    }
}

TEST(RLE_Parser_get_roi_checkerboard_pattern_test, RLEParserGTest)
{
    int width = 2, height = 2;
    std::string rle = "W 1 B 2 W 1";
    std::vector<std::vector<bool>> expected_data = {{true, false}, {false, true}};

    RLEParser parser = RLEParser(width, height, rle);
    RegionOfInterest roi = parser.get_roi();
    Grid grid = roi.get_grid();
    
    ASSERT_EQ(grid.get_width(), width);
    ASSERT_EQ(grid.get_height(), height);

    for (int y = 0; y < expected_data.size(); y++)
    {
        for (int x = 0; x < expected_data[0].size(); x++)
        {
            ASSERT_EXIT(
                (grid.get_pixel(x, y), exit(0)),
                ::testing::ExitedWithCode(0),
                ".*"
            );
            ASSERT_EQ(grid.get_pixel(x, y), expected_data[y][x]);
        }
    }
}



TEST(RLE_Parser_get_distrib_rows_pattern_test, RLEParserGTest)
{
    int width = 2, height = 2;
    std::string rle = "W 2 B 2";
    std::vector<int> expected_vert_hist = { 1, 1 };
    std::vector<int> expected_horz_hist = { 0, 2 };

    RLEParser parser = RLEParser(width, height, rle);
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