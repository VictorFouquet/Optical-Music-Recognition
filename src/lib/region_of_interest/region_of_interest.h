#ifndef REGION_OF_INTEREST_H
#define REGION_OF_INTEREST_H

#include <functional>
#include <memory>
#include <vector>

#include "grid.h"


class RegionOfInterest
{
public:
    RegionOfInterest(
        std::vector<int> vertical_distrib,
        std::vector<int> horizontal_distrib,
        int x_offset,
        int y_offset,
        int width,
        int height
    );

    RegionOfInterest(
        int x_offset,
        int y_offset,
        int width,
        int height
    );

    RegionOfInterest();
    ~RegionOfInterest();

    int get_x_offset();
    int get_y_offset();

    int get_width();
    int get_height();
    
    void set_distributions(std::shared_ptr<Grid> grid);

    std::vector<int> get_vertical_distrib();
    std::vector<int> get_horizontal_distrib();

    int get_first_interesting_row_index(std::function<bool(int)> callback);
    int get_last_interesting_col_index(std::function<bool(int)> callback);

    int get_first_interesting_col_index(std::function<bool(int)> callback);
    int get_last_interesting_row_index(std::function<bool(int)> callback);

private:
    int m_x_offset, m_y_offset, m_width, m_height;
    std::vector<int> m_vertical_distrib;
    std::vector<int> m_horizontal_distrib;
};

#endif