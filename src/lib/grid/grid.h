#ifndef GRID_H
#define GRID_H

#include <vector>

class Grid
{
public:
    Grid(int width, int height, std::vector<std::vector<bool>> rows);
    Grid();
    ~Grid();

    bool empty();
    int get_width();
    int get_height();

    std::vector<std::vector<bool>> get_rows();
    std::vector<bool> get_row(int id);

    std::vector<std::vector<bool>> get_columns();
    std::vector<bool> get_column(int id);

    bool get_pixel(int x, int y);
    Grid get_subgrid(int x, int y, int width, int height);

private:
    int m_width, m_height;
    std::vector<std::vector<bool>> m_rows;
};

#endif