#include "region_of_interest.h"
#include <iostream>


RegionOfInterest::RegionOfInterest(
    std::vector<int> vertical_distrib,
    std::vector<int> horizontal_distrib,
    int x_offset, int y_offset,
    int width, int height
) : m_vertical_distrib(vertical_distrib), m_horizontal_distrib(horizontal_distrib),
    m_x_offset(x_offset), m_y_offset(y_offset),
    m_width(width), m_height(height) {}

RegionOfInterest::RegionOfInterest(int x_offset, int y_offset, int width, int height) : 
    m_x_offset(x_offset), m_y_offset(y_offset), m_width(width), m_height(height) {}

RegionOfInterest::RegionOfInterest() = default;
RegionOfInterest::~RegionOfInterest() = default;

int RegionOfInterest::get_x_offset() { return m_x_offset; }
int RegionOfInterest::get_y_offset() { return m_y_offset; }


int RegionOfInterest::get_width() { return m_width; }
int RegionOfInterest::get_height() { return m_height; }

void RegionOfInterest::set_distributions(std::shared_ptr<Grid> grid)
{
    std::vector<int> vert_dist(m_width, 0);
    std::vector<int> horz_dist(m_height, 0);
    m_vertical_distrib = std::vector(m_width, 0);
    m_horizontal_distrib = std::vector(m_height, 0);

    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            if (!(grid->get_pixel(x + m_x_offset, y + m_y_offset)))
            {
                m_vertical_distrib[x]++;
                m_horizontal_distrib[y]++;
            }
        }
    }
}

std::vector<int> RegionOfInterest::get_vertical_distrib() { return m_vertical_distrib; }

std::vector<int> RegionOfInterest::get_horizontal_distrib() { return m_horizontal_distrib; }

int RegionOfInterest::get_first_interesting_row_index(std::function<bool(int)> callback)
{
    for (int i = 0; i < m_height; i++)
        if (callback(m_horizontal_distrib[i]))
            return i;
    return -1;
}

int RegionOfInterest::get_last_interesting_row_index(std::function<bool(int)> callback)
{
    for (int i = m_height - 1; i >= 0; i--)
    {
        if (callback(m_horizontal_distrib[i]))
            return i + 1;
    }
    return -1;
}


int RegionOfInterest::get_first_interesting_col_index(std::function<bool(int)> callback)
{
    for (int i = 0; i < m_width; i++)
        if (callback(m_vertical_distrib[i]))
            return i;
    return -1;
}

int RegionOfInterest::get_last_interesting_col_index(std::function<bool(int)> callback)
{
    for (int i = m_width - 1; i >= 0; i--)
    {   
        if (callback(m_vertical_distrib[i]))
            return i + 1;
    }
    return -1;
}
