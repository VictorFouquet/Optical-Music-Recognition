#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>

#include "omr.h"


int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        std::cerr
            << "Please provide [width] [height] and [rle_string] as argument to the program"
            << std::endl;
        return 1;
    }

    int width = std::stoi(argv[1]);
    int height = std::stoi(argv[2]);

    auto stringstream = std::ostringstream{};
    std::ifstream rle_file(argv[3]);
    if (rle_file.is_open())
    {
        stringstream << rle_file.rdbuf();
    }

    std::string rle = stringstream.str();

    OpticalMusicRecognition omr = OpticalMusicRecognition(width, height);
    omr.read_sheet(rle);
    std::vector<std::string> notes = omr.get_notes();

    std::string output = "";
    for (int i = 0; i < notes.size(); i++)
    {
        output += notes[i];
        if (i < notes.size() - 1)
            output += " ";
    }
    std::cout << "Notes contained in the provided image:" << std::endl;
    std::cout << output << std::endl;

    return 0;
}
