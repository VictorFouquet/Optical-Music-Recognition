#ifndef RLE_PARSER_H
#define RLE_PARSER_H

#include <string>
#include <vector>
#include "grid.h"
#include "region_of_interest.h"


class RLEParser
{
public:
    RLEParser(int width, int height, std::string rle_img);
    ~RLEParser();

    std::string get_rle();
    RegionOfInterest get_roi();

private:
    bool rle_to_roi();

    int m_width, m_height;
    std::string m_rle_encoded;
    bool m_parsed;
    RegionOfInterest m_roi;
};

#endif