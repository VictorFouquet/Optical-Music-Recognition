#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "region_of_interest.h"
#include "rle_parser.h"
#include "grid.h"

class OpticalMusicRecognition
{
public:
    OpticalMusicRecognition();
    OpticalMusicRecognition(int sheet_width, int sheet_height);
    ~OpticalMusicRecognition();

    std::vector<std::string> get_notes();

    void set_rle_source(std::string source);
    void parse_rle_source();

    RegionOfInterest get_img_roi();
    RegionOfInterest get_cropped_image();
    std::vector<RegionOfInterest> get_local_rois();

    void compute_line_height();
    void compute_interline_height();
    void compute_notes_y_axis();

    std::vector<int> get_vertical_boundaries();
    std::vector<int> get_notes_intervals(std::vector<int> boundaries);
    std::vector<int> get_note_tail_interval(int x_min, int x_max);

    void parse_note_roi(RegionOfInterest note_roi);
    std::vector<std::vector<int>> get_note_areas(RegionOfInterest note_roi);
    std::vector<std::vector<int>> group_note_areas(std::vector<std::vector<int>> areas);

    // Main entry point
    void read_sheet(std::string rle);

    std::function<bool(int)> get_is_not_zero_callback();

private:
    bool is_not_zero(int x);

    std::string m_source;
    int m_sheet_width, m_sheet_height;

    std::shared_ptr<Grid> m_grid;

    int m_line_height;
    int m_interline_height;
    std::vector<int> m_notes_y_axis;

    RegionOfInterest m_img_roi;
    RegionOfInterest m_cropped_roi;
    std::vector<RegionOfInterest> m_notes_rois;

    std::vector<std::string> m_notes;
    int m_is_line = 0, m_is_line_or_note = 1, m_is_tail = 2, m_is_note = 3;
    std::vector<std::string> m_reference_scale = {"G","F","E","D","C","B","A","G","F","E","D","C"};
};
