#include <gtest/gtest.h>
#include "grid.h"


std::vector<std::vector<bool>> data = {{ true, false }, {false, true}};
Grid grid = Grid(2,2,data);

// Tests width getter
TEST(Grid_Get_Width_Test, GridGTest)
{
    ASSERT_EQ(grid.get_width(), 2);
}

// Tests height getter
TEST(Grid_Get_Height_Test, GridGTest)
{
    ASSERT_EQ(grid.get_height(), 2);
}

// Tests rows getter
TEST(Grid_Get_Rows_Test, GridGTest)
{
    int mismatch = 0;
    std::vector<std::vector<bool>> rows = grid.get_rows();

    for (int y = 0; y < rows.size(); y++)
    {
        for (int x = 0; x < rows[y].size(); x++)
        {
            if (rows[y][x] != data[y][x])
                mismatch++;
        }
    }
    ASSERT_EQ(mismatch, 0);
}

// Tests columns getter
TEST(Grid_Get_Columns_Test, GridGTest)
{
    int mismatch = 0;
    std::vector<std::vector<bool>> columns = grid.get_columns();

    for (int x = 0; x < columns.size(); x++)
    {
        for (int y = 0; y < columns[x].size(); y++)
        {
            if (columns[x][y] != data[y][x])
                mismatch++;
        }
    }
    ASSERT_EQ(mismatch, 0);
}

// Tests row getter
TEST(Grid_Get_Row_Test, GridGTest)
{
    std::vector<bool> row;
    int mismatch;

    mismatch = 0;
    row = grid.get_row(0);

    for (int x = 0; x < row.size(); x++)
    {
        if (row[x] != data[0][x])
            mismatch++;
    }

    ASSERT_EQ(mismatch, 0);

    mismatch = 0;
    row = grid.get_row(1);

    for (int x = 0; x < row.size(); x++)
    {
        if (row[x] != data[1][x])
            mismatch++;
    }

    ASSERT_EQ(mismatch, 0);
}

// Tests column getter
TEST(Grid_Get_Column_Test, GridGTest)
{
    int mismatch;
    std::vector<bool> column;

    mismatch = 0;
    column = grid.get_column(0);

    for (int y = 0; y < column.size(); y++)
    {
        if (column[y] != data[y][0])
            mismatch++;
    }

    ASSERT_EQ(mismatch, 0);

    mismatch = 0;
    column = grid.get_column(1);

    for (int y = 0; y < column.size(); y++)
    {
        if (column[y] != data[y][1])
            mismatch++;
    }

    ASSERT_EQ(mismatch, 0);
}

// Tests pixel getter
TEST(Grid_Get_Pixel_Test, GridGTest)
{
    ASSERT_EXIT(
        (grid.get_pixel(0, 0), exit(0)),
        ::testing::ExitedWithCode(0),
        ".*"
    );
    ASSERT_EXIT(
        (grid.get_pixel(data.size(), data[0].size()), exit(0)),
        ::testing::KilledBySignal(SIGSEGV),
        ".*"
    );

    int mismatch = 0;
    
    for (int y = 0; y < data.size(); y++)
    {
        for (int x = 0; x < data[y].size(); x++)
        {
            if (grid.get_pixel(x, y) != data[y][x])
                mismatch++;
        }
    }

    ASSERT_EQ(mismatch, 0);
}

// Tests subgrid getter
TEST(Grid_Get_Subgrid_Test, GridGTest)
{
    int mismatch;
    int x, y, width, height;
    Grid subgrid;

    // UPPER LEFT SQUARE
    mismatch = 0;
    x = 0, y = 0, width = 1, height = 1;

    ASSERT_EXIT(
        (grid.get_subgrid(x, y, width, height), exit(0)),
        ::testing::ExitedWithCode(0),
        ".*"
    );

    subgrid = grid.get_subgrid(x, y, width, height);
    

    for (int _y = 0; _y < height; _y++)
    {
        for (int _x = 0; _x < width; _x++)
        {
            ASSERT_EXIT(
                (subgrid.get_pixel(_x, _y), exit(0)),
                ::testing::ExitedWithCode(0),
                ".*"
            );
            if (subgrid.get_pixel(_x, _y) != data[_y + y][_x + x])
                mismatch++;
        }
    }

    ASSERT_EQ(mismatch, 0);

    // RIGHT COLUMN
    mismatch = 0;
    x = 1, y = 0, width = 1, height = 2;

    ASSERT_EXIT(
        (grid.get_subgrid(x, y, width, height), exit(0)),
        ::testing::ExitedWithCode(0),
        ".*"
    );

    subgrid = grid.get_subgrid(x, y, width, height);

    for (int _y = 0; _y < height; _y++)
    {
        for (int _x = 0; _x < width; _x++)
        {
            ASSERT_EXIT(
                (subgrid.get_pixel(_x, _y), exit(0)),
                ::testing::ExitedWithCode(0),
                ".*"
            );
            if (subgrid.get_pixel(_x, _y) != data[_y + y][_x + x])
                mismatch++;
        }
    }

    ASSERT_EQ(mismatch, 0);

    // BOTTOM LINE
    mismatch = 0;
    x = 0, y = 1, width = 2, height = 1;

    ASSERT_EXIT(
        (grid.get_subgrid(x, y, width, height), exit(0)),
        ::testing::ExitedWithCode(0),
        ".*"
    );

    subgrid = grid.get_subgrid(x, y, width, height);
 
    for (int _y = 0; _y < height; _y++)
    {
        for (int _x = 0; _x < width; _x++)
        {
            ASSERT_EXIT(
                (data[_y + y][_x + x], exit(0)),
                ::testing::ExitedWithCode(0),
                ".*"
            );
            if (subgrid.get_pixel(_x, _y) != data[_y + y][_x + x])
                mismatch++;
        }
    }

    ASSERT_EQ(mismatch, 0);

    // ALL GRID
    mismatch = 0;
    x = 0, y = 0, width = 2, height = 2;

    ASSERT_EXIT(
        (grid.get_subgrid(x, y, width, height), exit(0)),
        ::testing::ExitedWithCode(0),
        ".*"
    );

    subgrid = grid.get_subgrid(x, y, width, height);
 
    for (int _y = 0; _y < height; _y++)
    {
        for (int _x = 0; _x < width; _x++)
        {
            if (subgrid.get_pixel(_x, _y) != data[_y + y][_x + x])
                mismatch++;
        }
    }

    ASSERT_EQ(mismatch, 0);

    // OUT OF BOUNDARIES
    mismatch = 0;
    x = 0, y = 0, width = 3, height = 3;

    ASSERT_EXIT(
        (grid.get_subgrid(x, y, width, height), exit(0)),
        ::testing::KilledBySignal(SIGSEGV),
        ".*"
    );
}
