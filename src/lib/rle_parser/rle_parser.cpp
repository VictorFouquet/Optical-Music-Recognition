#include <math.h>
#include <iostream>

#include "rle_parser.h"


RLEParser::RLEParser(int width, int height, std::string rle_img):
    m_width(width), m_height(height), m_rle_encoded(rle_img), m_parsed(false)
    {}

RLEParser::~RLEParser() = default;

std::string RLEParser::get_rle() { return m_rle_encoded; }

RegionOfInterest RLEParser::get_roi()
{
    if (!m_parsed)
        m_parsed = rle_to_roi();
    return m_roi;
}

bool RLEParser::rle_to_roi()
{
    int current_index = 0;

    std::vector<std::vector<bool>> pixels;
    std::vector<int> vertical_hist(m_width, 0);
    std::vector<int> horizontal_hist(m_height, 0);
    int x = 0, y = -1;
    int black_px_per_row = 0, black_px_per_col = 0;

    while (current_index < m_rle_encoded.length())
    {
        bool px_value = m_rle_encoded[current_index] == 'W';
        std::string qty_str = "";
        current_index += 2;

        while (m_rle_encoded[current_index] && m_rle_encoded[current_index] != ' ')
        {
            qty_str += m_rle_encoded[current_index];
            current_index++;
        }
        int qty = stoi(qty_str);

        for (int i = 0; i < qty; i++)
        {
            if (x == 0)
            {
                y++;
                pixels.push_back({});
            }
            pixels.back().push_back(px_value);
            if (!px_value)
            {
                vertical_hist[x]++;
                horizontal_hist[y]++;
            }
            x = (x + 1) % m_width;
        }

        current_index++;
    }

    if (pixels.empty())
        return false;

    m_roi = RegionOfInterest(
        Grid(m_width, m_height, pixels),
        vertical_hist, horizontal_hist,
        0, 0
    );

    return true;
}
