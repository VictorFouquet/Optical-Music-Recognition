#include <fstream>
#include <string>

#include <gtest/gtest.h>

#include "omr.h"


// END TO END TESTS
// - TO DO: UNIT TEST OMR METHODS
std::string read_input_file(std::string file_name)
{
    auto ss = std::ostringstream{};
    std::ifstream rle_file(file_name);
    if (rle_file.is_open())
    {
        ss << rle_file.rdbuf();
    }
    return ss.str();
}

TEST(OMR_one_black_interline_test, OMRGTest)
{
    int width = 120, height = 176;
    std::string rle = read_input_file("in1.txt");

    OpticalMusicRecognition omr = OpticalMusicRecognition(width, height);
    ASSERT_EQ(rle, "W 4090 B 100 W 20 B 100 W 20 B 100 W 20 B 100 W 1040 B 2 W 118 B 2 W 118 B 2 W 118 B 2 W 118 B 2 W 118 B 2 W 118 B 2 W 118 B 2 W 118 B 2 W 118 B 2 W 118 B 2 W 118 B 2 W 58 B 100 W 20 B 100 W 20 B 100 W 20 B 100 W 80 B 2 W 118 B 2 W 118 B 2 W 118 B 2 W 118 B 2 W 118 B 2 W 118 B 2 W 118 B 2 W 118 B 2 W 118 B 2 W 118 B 2 W 118 B 2 W 118 B 2 W 118 B 2 W 118 B 2 W 118 B 2 W 118 B 2 W 118 B 2 W 118 B 2 W 118 B 2 W 58 B 100 W 20 B 100 W 20 B 100 W 20 B 100 W 66 B 10 W 4 B 2 W 103 B 12 W 3 B 2 W 101 B 16 W 1 B 2 W 101 B 16 W 1 B 2 W 100 B 20 W 99 B 21 W 99 B 21 W 98 B 22 W 98 B 22 W 98 B 22 W 98 B 22 W 98 B 22 W 98 B 22 W 98 B 22 W 99 B 20 W 100 B 20 W 101 B 18 W 103 B 16 W 104 B 16 W 106 B 12 W 63 B 100 W 20 B 100 W 20 B 100 W 20 B 100 W 2420 B 100 W 20 B 100 W 20 B 100 W 20 B 100 W 5050");
    omr.read_sheet(rle);
    std::vector<std::string> notes = omr.get_notes();
    std::string output = "";
    for (int i = 0; i < notes.size(); i++)
    {
        output += notes[i];
        if (i < notes.size() - 1)
            output += " ";
    }

    ASSERT_EQ(output, "AQ");
}

TEST(OMR_one_black_line_test, OMRGTest)
{
    int width = 120, height = 176;
    std::string rle = read_input_file("in2.txt");

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

    ASSERT_EQ(output, "BQ");
}

TEST(OMR_one_white_interline_test, OMRGTest)
{
    int width = 120, height = 176;
    std::string rle = read_input_file("in3.txt");

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

    ASSERT_EQ(output, "AH");
}

TEST(OMR_one_white_line_test, OMRGTest)
{
    int width = 120, height = 176;
    std::string rle = read_input_file("in4.txt");

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

    ASSERT_EQ(output, "BH");
}

TEST(OMR_only_black_without_c_test, OMRGTest)
{
    int width = 420, height = 176;
    std::string rle = read_input_file("in5.txt");

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

    ASSERT_EQ(output, "CQ CQ CQ CQ DQ EQ CQ AQ");
}


TEST(OMR_only_white_without_c_test, OMRGTest)
{
    int width = 390, height = 176;
    std::string rle = read_input_file("in6.txt");

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

    ASSERT_EQ(output, "DH EH FH AH CH EH DH");
}

TEST(OMR_black_and_white_scale_test, OMRGTest)
{
    int width = 440, height = 176;
    std::string rle = read_input_file("in7.txt");

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

    ASSERT_EQ(output, "EQ FH GQ AH BQ CH DQ EH FQ");
}

TEST(OMR_black_and_white_scale_with_c_test, OMRGTest)
{
    int width = 520, height = 176;
    std::string rle = read_input_file("in8.txt");

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

    ASSERT_EQ(output, "CQ CQ CQ DQ EH DH CQ EQ DQ DQ CH");
}

TEST(OMR_close_notes_test, OMRGTest)
{
    int width = 520, height = 176;
    std::string rle = read_input_file("in9.txt");

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

    ASSERT_EQ(output, "BQ CH DH EH FQ GQ GQ BQ DH BQ");
}

TEST(OMR_one_pixel_line_test, OMRGTest)
{
    int width = 420, height = 78;
    std::string rle = read_input_file("in10.txt");

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

    ASSERT_EQ(output, "BQ CH DH EH FQ GQ GQ BQ DH BQ BQ CH DH EH FQ GQ GQ BQ DH BQ");
}

TEST(OMR_doctor_who_test, OMRGTest)
{
    int width = 4320, height = 241;
    std::string rle = read_input_file("in11.txt");

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

    ASSERT_EQ(output, "CH CQ DQ CH EH CQ CQ AQ CH EQ DH CQ CQ DH CQ DQ CH CQ DQ EQ FQ AQ BQ CQ DQ EQ FQ GH CH CQ DQ CH EH CQ CQ AQ CH EQ DH CQ CQ DH CQ DQ CH CQ DQ EQ FQ AQ BQ CQ DQ EQ FQ GH CH CQ DQ CH EH CQ CQ AQ CH EQ DH CQ CQ DH CQ DQ CH CQ DQ EQ FQ AQ BQ CQ DQ EQ FQ GH");
}

TEST(OMR_random_test, OMRGTest)
{
    int width = 4020, height = 241;
    std::string rle = read_input_file("in12.txt");

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

    ASSERT_EQ(output, "FH CH EQ BQ EH EH FQ AQ CH AQ EH DQ DQ CH EH CH FQ EQ CQ GH CH EQ FQ EH BQ GH BH FQ CQ FH AH DH GQ AH DQ FH FQ GH DH CH EQ GH EH EH GH BH GQ BH FH CQ CQ FH DH BH EQ CQ GQ CQ DH FH AH FQ CH DH FH EQ EQ BH DQ FQ GQ DH CH GH FQ EH CQ EQ AQ GQ DH EQ CQ FH AQ DQ FH AH FQ EQ");
}
