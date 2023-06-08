#ifndef REGION_OF_INTEREST_H
#define REGION_OF_INTEREST_H

#include <vector>
#include "grid.h"


class RegionOfInterest
{
public:
    RegionOfInterest(
        Grid grid,
        std::vector<int> vertical_distrib,
        std::vector<int> horizontal_distrib,
        int x_offset,
        int y_offset
    );

    RegionOfInterest();
    ~RegionOfInterest();

    int get_grid_x_offset();
    int get_grid_y_offset();

    int get_width();
    int get_height();
    
    std::vector<int> get_vertical_distrib();
    std::vector<int> get_horizontal_distrib();

    Grid get_grid();

    int get_first_interesting_row_index();
    int get_last_interesting_col_index();

    int get_first_interesting_col_index();
    int get_last_interesting_row_index();

private:
    int m_grid_x_offset, m_grid_y_offset, m_width, m_height;
    std::vector<int> m_vertical_distrib;
    std::vector<int> m_horizontal_distrib;
    Grid m_grid;
};

#endif