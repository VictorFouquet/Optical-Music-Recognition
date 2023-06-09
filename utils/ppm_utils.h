#ifndef PPM_UTIL_H
#define PPM_UTIL_H

#ifdef _IMG_DEBUG_PATH
    #define PATH _IMG_DEBUG_PATH
#else
    #define PATH ""
#endif


#include <fstream>
#include <string>
#include <vector>


void raw_bin_image_to_ppm(std::vector<std::vector<bool>> raw_data, std::string output)
{
    std::ofstream image;
    image.open(PATH + output);
    
    int height = raw_data.size();
    int width = raw_data[0].size();
    
    if (image.is_open())
    {
        image << "P3 " << width << " " << height << " 255" << std::endl;
        for (auto row: raw_data)
        {
            for (auto pixel: row)
            {
                int value = pixel ? 255 : 0;
                image << value << " " << value << " " << value << " ";
            }
            image << std::endl;
        }
    }

    image.close();
}

#endif