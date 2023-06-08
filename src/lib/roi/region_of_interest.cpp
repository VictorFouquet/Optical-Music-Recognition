#include "region_of_interest.h"
#include <iostream>
RegionOfInterest::RegionOfInterest(
    Grid grid,
    std::vector<int> vertical_distrib,
    std::vector<int> horizontal_distrib,
    int x_offset,
    int y_offset
):
    m_grid(grid), m_vertical_distrib(vertical_distrib), m_horizontal_distrib(horizontal_distrib),
    m_grid_x_offset(x_offset), m_grid_y_offset(y_offset),
    m_width(grid.get_width()), m_height(grid.get_height()) {}

RegionOfInterest::RegionOfInterest() = default;
RegionOfInterest::~RegionOfInterest() = default;

int RegionOfInterest::get_grid_x_offset() { return m_grid_x_offset; }
int RegionOfInterest::get_grid_y_offset() { return m_grid_y_offset; }


int RegionOfInterest::get_width() { return m_width; }
int RegionOfInterest::get_height() { return m_height; }


std::vector<int> RegionOfInterest::get_vertical_distrib() { return m_vertical_distrib; }

std::vector<int> RegionOfInterest::get_horizontal_distrib() { return m_horizontal_distrib; }


Grid RegionOfInterest::get_grid() { return m_grid; }


int RegionOfInterest::get_first_interesting_row_index()
{
    for (int i = 0; i < m_height; i++)
        if (m_horizontal_distrib[i])
            return i;
    return -1;
}

int RegionOfInterest::get_last_interesting_row_index()
{
    for (int i = m_height - 1; i >= 0; i++)
    {
        std::cout << i << std::endl;
        if (m_horizontal_distrib[i])
            return i;
    }
    return -1;
}


int RegionOfInterest::get_first_interesting_col_index()
{
    for (int i = 0; i < m_width; i++)
        if (m_vertical_distrib[i])
            return i;
    return -1;
}

int RegionOfInterest::get_last_interesting_col_index()
{
    for (int i = m_width - 1; i >= 0; i++)
        if (m_horizontal_distrib[i])
            return i;
    return -1;
}
