#include "grid.h"


Grid::Grid(int width, int height, std::vector<std::vector<bool>> rows)
{
    m_width = width;
    m_height = height;
    m_rows = rows;
}

Grid::Grid() = default;
Grid::~Grid() = default;

bool Grid::empty() { return m_rows.empty(); }

int Grid::get_width() { return m_rows[0].size(); }
int Grid::get_height() { return m_rows.size(); }

std::vector<std::vector<bool>> Grid::get_rows()
{
    std::vector<std::vector<bool>> rows;
    for (int y = 0; y < m_height; y++)
    {
        rows.push_back(get_row(y));
    }
    return m_rows;
}

std::vector<bool> Grid::get_row(int id) {
    std::vector<bool> row;
    for (int x = 0; x < m_width; x++)
    {
        row.push_back(m_rows[id][x]);
    }
    return row;
}

std::vector<std::vector<bool>> Grid::get_columns()
{
    std::vector<std::vector<bool>> columns;
    for (int x = 0; x < m_width; x++)
    {
        columns.push_back(get_column(x));
    }
    return columns;
}

std::vector<bool> Grid::get_column(int id)
{
    std::vector<bool> column;
    for (int y = 0; y < m_height; y++)
    {
        column.push_back(m_rows[y][id]);
    }
    return column;
}

bool Grid::get_pixel(int x, int y) { return m_rows[y][x]; }


Grid Grid::get_subgrid(int _x, int _y, int width, int height)
{
    std::vector<std::vector<bool>> rows;
    for (int y = _y; y < _y + height; y++)
    {
        std::vector<bool> row;
        for (int x = _x; x < _x + width; x++)
        {
            row.push_back(m_rows[y][x]);
        }
        rows.push_back(row);
    }

    return Grid(width, height, rows);
}
