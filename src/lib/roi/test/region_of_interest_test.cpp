#include <gtest/gtest.h>
#include "region_of_interest.h"

std::vector<std::vector<bool>> raw_data = {
    { true, true,  true,  true },
    { true, false, true,  true },
    { true, false, false, true },
    { true, true,  true,  true },
};
std::vector<int> vertical_distrib = { 0, 2, 1, 0 };
std::vector<int> horizontal_distrib = { 0, 1, 2, 1 };
Grid grid = Grid(raw_data[0].size(), raw_data.size(), raw_data);


TEST(ROI_get_width_test, ROIGTest)
{
    RegionOfInterest roi = RegionOfInterest(grid, vertical_distrib, horizontal_distrib, 0 , 0);
    ASSERT_EXIT(
        (roi.get_width(), exit(0)),
        ::testing::ExitedWithCode(0),
        ".*"
    );
    ASSERT_EQ(roi.get_width(), raw_data[0].size());
}

TEST(ROI_get_height_test, ROIGTest)
{
    RegionOfInterest roi = RegionOfInterest(grid, vertical_distrib, horizontal_distrib, 0 , 0);
    ASSERT_EXIT(
        (roi.get_height(), exit(0)),
        ::testing::ExitedWithCode(0),
        ".*"
    );
    ASSERT_EQ(roi.get_height(), raw_data.size());
}

TEST(ROI_get_x_grid_offset_test, ROIGTest)
{
    int x_offset = 2;
    RegionOfInterest roi = RegionOfInterest(grid, vertical_distrib, horizontal_distrib, x_offset , 0);
    ASSERT_EXIT(
        (roi.get_grid_x_offset(), exit(0)),
        ::testing::ExitedWithCode(0),
        ".*"
    );
    ASSERT_EQ(roi.get_grid_x_offset(), x_offset);
}

TEST(ROI_get_y_grid_offset_test, ROIGTest)
{
    int y_offset = 3;
    RegionOfInterest roi = RegionOfInterest(grid, vertical_distrib, horizontal_distrib, 0, y_offset);
    ASSERT_EXIT(
        (roi.get_grid_y_offset(), exit(0)),
        ::testing::ExitedWithCode(0),
        ".*"
    );
    ASSERT_EQ(roi.get_grid_y_offset(), y_offset);
}

TEST(ROI_get_vertical_distrib_test, ROIGTest)
{
    RegionOfInterest roi = RegionOfInterest(grid, vertical_distrib, horizontal_distrib, 0 , 0);
    ASSERT_EXIT(
        (roi.get_vertical_distrib(), exit(0)),
        ::testing::ExitedWithCode(0),
        ".*"
    );
    ASSERT_EQ(roi.get_vertical_distrib().size(), vertical_distrib.size());
    for (int i = 0; i < vertical_distrib.size(); i++)
    {
        ASSERT_EQ(roi.get_vertical_distrib()[i], vertical_distrib[i]);
    }
}

TEST(ROI_get_horizontal_distrib_test, ROIGTest)
{
    RegionOfInterest roi = RegionOfInterest(grid, vertical_distrib, horizontal_distrib, 0 , 0);
    ASSERT_EXIT(
        (roi.get_horizontal_distrib(), exit(0)),
        ::testing::ExitedWithCode(0),
        ".*"
    );
    ASSERT_EQ(roi.get_horizontal_distrib().size(), horizontal_distrib.size());
    for (int i = 0; i < horizontal_distrib.size(); i++)
    {
        ASSERT_EQ(roi.get_horizontal_distrib()[i], horizontal_distrib[i]);
    }
}

TEST(ROI_get_grid_test, ROIGTest)
{
    RegionOfInterest roi = RegionOfInterest(grid, vertical_distrib, horizontal_distrib, 0, 0);
    ASSERT_EXIT(
        (roi.get_grid(), exit(0)),
        ::testing::ExitedWithCode(0),
        ".*"
    );
    
    int mismatch = 0;
    for (int y = 0; y < roi.get_height(); y++)
    {
        for (int x = 0; x < roi.get_width(); x++)
        {
            ASSERT_EXIT(
                (roi.get_grid().get_pixel(x, y), exit(0)),
                ::testing::ExitedWithCode(0),
                ".*"
            );
            if (roi.get_grid().get_pixel(x, y) != raw_data[y][x])
                mismatch ++;
        }
    }
    ASSERT_EQ(mismatch, 0);
}

TEST(ROI_get_first_interesting_row_test, ROIGTest)
{
    RegionOfInterest roi = RegionOfInterest(grid, vertical_distrib, horizontal_distrib, 0 , 0);
    ASSERT_EXIT(
        (roi.get_first_interesting_row_index(), exit(0)),
        ::testing::ExitedWithCode(0),
        ".*"
    );
    ASSERT_EQ(roi.get_first_interesting_row_index(), 1);
}

TEST(ROI_get_last_interesting_row_test, ROIGTest)
{
    RegionOfInterest roi = RegionOfInterest(grid, vertical_distrib, horizontal_distrib, 0 , 0);
    ASSERT_EXIT(
        (roi.get_last_interesting_row_index(), exit(0)),
        ::testing::ExitedWithCode(0),
        ".*"
    );
    ASSERT_EQ(roi.get_last_interesting_row_index(), 3);
}

TEST(ROI_get_first_interesting_col_test, ROIGTest)
{
    RegionOfInterest roi = RegionOfInterest(grid, vertical_distrib, horizontal_distrib, 0 , 0);
    ASSERT_EXIT(
        (roi.get_first_interesting_col_index(), exit(0)),
        ::testing::ExitedWithCode(0),
        ".*"
    );
    ASSERT_EQ(roi.get_first_interesting_col_index(), 1);
}

TEST(ROI_get_last_interesting_col_test, ROIGTest)
{
    RegionOfInterest roi = RegionOfInterest(grid, vertical_distrib, horizontal_distrib, 0 , 0);
    ASSERT_EXIT(
        (roi.get_last_interesting_col_index(), exit(0)),
        ::testing::ExitedWithCode(0),
        ".*"
    );
    ASSERT_EQ(roi.get_last_interesting_col_index(), 3);
}
