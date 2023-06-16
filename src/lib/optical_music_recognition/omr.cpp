#include <math.h>

#include "omr.h"


OpticalMusicRecognition::OpticalMusicRecognition() = default;
OpticalMusicRecognition::~OpticalMusicRecognition() = default;

OpticalMusicRecognition::OpticalMusicRecognition(int sheet_width, int sheet_height)
{
    m_sheet_width = sheet_width;
    m_sheet_height = sheet_height;
    m_grid = std::make_shared<Grid>(Grid(m_sheet_width, m_sheet_height));
}

/** Gets parsed notes */
std::vector<std::string> OpticalMusicRecognition::get_notes() { return m_notes; }

/** Sets RLE source */
void OpticalMusicRecognition::set_rle_source(std::string source) { m_source = source; }

/** Converts RLE source to global region of interest */
void OpticalMusicRecognition::parse_rle_source()
{
    RLEParser parser = RLEParser(m_sheet_width, m_sheet_height, m_source);
    parser.parse_source(m_grid);
    m_img_roi = parser.get_roi();
}


/* Gets global region of interest */
RegionOfInterest OpticalMusicRecognition::get_img_roi() { return m_img_roi; }

/** Gets image free from leading and trailing white columns and rows */
RegionOfInterest OpticalMusicRecognition::get_cropped_image()
{
    auto callback = get_is_not_zero_callback();

    // First and last interesting cols and rows are the first and last containing black pixels
    int x_begin = m_img_roi.get_first_interesting_col_index(callback);
    int x_end   = m_img_roi.get_last_interesting_col_index(callback);
    int y_begin = m_img_roi.get_first_interesting_row_index(callback);
    int y_end   = m_img_roi.get_last_interesting_row_index(callback);

    // Stores cropped vertical distribution (same as global distrib)
    std::vector<int> vert_dist;
    for (int i = x_begin; i < x_end; i++)
    {
        vert_dist.push_back(m_img_roi.get_vertical_distrib()[i]);
    }
    // Stores cropped horizontal distribution (same as global distrib)
    std::vector<int> horz_dist;
    for (int i = y_begin; i < y_end; i++)
    {
        horz_dist.push_back(m_img_roi.get_horizontal_distrib()[i]);
    }
    // Creates cropped region of interest
    m_cropped_roi = RegionOfInterest(
        vert_dist,
        horz_dist,
        x_begin, y_begin,
        x_end - x_begin, y_end - y_begin
    );

    return m_cropped_roi;
}

/** Computes local region of interests where notes can be found */
std::vector<RegionOfInterest> OpticalMusicRecognition::get_local_rois()
{
    // Gets the notes vertical boundaries, index of columns where lines only are found
    std::vector<int> boundaries = get_vertical_boundaries();
    // Computes horizontal intervals from the vertical boundaries
    std::vector<int> intervals = get_notes_intervals(boundaries);

    for (int i = 0; i < intervals.size(); i+=2)
    {
        // Gets the vertical interval of the note tail (y and y' of tail's start and end)
        std::vector<int> tail_interval = get_note_tail_interval(intervals[i], intervals[i+1]);
        // Create the note's region of interest
        RegionOfInterest note_roi = RegionOfInterest(
            intervals[i] + m_cropped_roi.get_x_offset(), tail_interval[0],
            intervals[i+1] - intervals[i], tail_interval[1] - tail_interval[0]
        );
        // Sets individual note's distributions
        note_roi.set_distributions(m_grid);
        m_notes_rois.push_back(note_roi);
    }

    return m_notes_rois;
}


/** Computes the height of a line */
void OpticalMusicRecognition::compute_line_height()
{
    // First column of cropped region of interest should only store pixels belonging to lines,
    // so the height of a line is the quantity of black pixels in first column divided by n of lines
    m_line_height = m_cropped_roi.get_vertical_distrib()[0] / 5;
}

/** Computes the distance between two lines */
void OpticalMusicRecognition::compute_interline_height()
{
    m_interline_height = -1;
    // The first black pixel of the first line hasn't been found
    bool first_line_found = false;
    // The last black pixel of the first line hasn't been found
    bool first_line_finished = false;

    // Uses cropped roi x offset to iterate on the grid's first column with lines
    int x = m_cropped_roi.get_x_offset();
    // First white pixel of the interline's y index
    int interline_y_begin;

    int start_y = m_cropped_roi.get_y_offset();
    int end_y = start_y + m_cropped_roi.get_height();

    for (int y = start_y; y < end_y; y++)
    {
        // Pixel is white and the first line hasn't been crossed
        if (m_grid->get_pixel(x, y) && !first_line_finished)
        {
            // If the first line has been found and the current pixel is white,
            // then the first line is now crossed and the first pixel of interline is found
            if (first_line_found)
            {
                interline_y_begin = y;
                first_line_finished = true;
            }
        }
        // Pixel is black
        else if (!m_grid->get_pixel(x, y))
        {
            // If first line had not been found,
            // then the current pixel is the first of the first line
            if (!first_line_found)
                first_line_found = true;
            // If first line has been crossed, the current pixel is the first of the second line,
            // so the last pixel of the interline was the previous pixel
            else if (first_line_finished)
            {
                m_interline_height =  y - interline_y_begin;
                break;
            }
        }
    }
}

/** Computes the expected y axis of each note */
void OpticalMusicRecognition::compute_notes_y_axis()
{
    // Computes line and interline heights
    compute_line_height();
    compute_interline_height();

    std::vector<int> line_axes;
    int x = m_cropped_roi.get_x_offset();

    // Finds center of the five vertical lines
    for (int y = 0; y < m_sheet_height; y++)
    {
        if (m_grid->get_pixel(x, y) == false)
        {
            line_axes.push_back(y + floor(m_line_height * 0.5));
            y += m_line_height - 1;
        }
    }

    // Computes distance between lines
    int distance_between_axis = line_axes[1] - line_axes[0];
    // Computes interline axis offset
    int interline_y_offset = (int) distance_between_axis * 0.5;

    // Stores the lines and interlines axis indices  
    for (int i = 0; i < 5; i++)
    {
        m_notes_y_axis.push_back(line_axes[i]);
        m_notes_y_axis.push_back(line_axes[i] + interline_y_offset);
    }

    // Prepends axis of highest G interlin
    m_notes_y_axis.insert(m_notes_y_axis.begin(), m_notes_y_axis[0] - interline_y_offset);
    // Appends axis of lowest C line
    m_notes_y_axis.push_back(m_notes_y_axis.back() + interline_y_offset);
}

/** 
 * Gets indices boundaries that separate the notes.
 * Each even indexed element is inclusive, whereas all odd indexed elements are exclusive.
 */
std::vector<int> OpticalMusicRecognition::get_vertical_boundaries()
{
    std::vector<int> boundaries;
    std::vector<int> vert_dist = m_cropped_roi.get_vertical_distrib();

    // Expected number of black pixels per column when the column only contains lines
    int five_line_count = m_line_height * 5;
    int six_line_count = m_line_height * 6;

    // Iterates over columns distribution
    // (ignores the first column as we know it only contains lines)
    for (int i = 1; i < vert_dist.size(); i++)
    {
        int n = vert_dist[i], m = vert_dist[i-1];
        // Pushes index to boundaries if current column is note and previous column is empty
        if (
            // Column does contain a note
            ((n != five_line_count) && (n != six_line_count)) &&
            // Previous column is empty
            ((m == five_line_count) || (m == six_line_count))
        )
            boundaries.push_back(i);

        // Pushes index to boundaries if previous column is empty and previous column is note
        else if (
            // Column is empty
            ((n == five_line_count) || (n == six_line_count)) &&
            // Previous column does contain a note
            ((m != five_line_count) && (m != six_line_count))
        )
            boundaries.push_back(i);
    }

    return boundaries;
}

/** Converts boundaries to intervals */
std::vector<int> OpticalMusicRecognition::get_notes_intervals(std::vector<int> boundaries)
{
    // Notes are circles, and a note fills in all the space between two lines
    // Then a note's width is equal to an interline height

    // We don't know the width of a note's tail, so for two boundaries to constitute a note interval,
    // the distance between two intervals must be higher than a note width.
    std::vector<int> intervals;
    intervals.push_back(boundaries[0]);
    for (int i = 1; i < boundaries.size(); i++)
    {
        // Pushes boundary to intervals if last interval is closed (intervals size is even),
        // or if an interval is open, and distance between opening and current boundary os greater than a note width
        if (
            (!(intervals.size() & 1)) || 
            (boundaries[i] - intervals.back() > m_interline_height)
        )
            intervals.push_back(boundaries[i]);
    }
    // Pushes last boundary if length of intervals is odd
    if (intervals.size() & 1)
        intervals.push_back(boundaries.back());

    return intervals;
}

/** Gets the x begin and end index of a note's tail */
std::vector<int> OpticalMusicRecognition::get_note_tail_interval(int x_min, int x_max)
{
    std::vector<int> vertical_distrib = m_cropped_roi.get_vertical_distrib();

    // Tail is located either at the begining or the end of the horizontal interval
    int max_value_index = vertical_distrib[x_min] > vertical_distrib[x_max - 1] ? x_min : x_max - 1;
    // Computes absolute value of x in grid
    int x = max_value_index + m_cropped_roi.get_x_offset();

    // Computes intervals containing black pixels
    std::vector<int> black_px_intervals;
    int y_start = m_cropped_roi.get_y_offset();
    int y_end = y_start + m_cropped_roi.get_height();

    for (int y = y_start; y < y_end; y++)
    {
        // Current pixel is black
        if (m_grid->get_pixel(x, y) == 0)
        {
            // First black pixel in column
            if (black_px_intervals.size() == 0)
                black_px_intervals.push_back(y);
            // Previous pixel was white
            else if (m_grid->get_pixel(x, y - 1) != 0)
                black_px_intervals.push_back(y);
            // Last black pixel in column
            else if (y == y_end - 1)
                black_px_intervals.push_back(y_end);
        } else {
            // Current pixel is white and previous is black
            if (m_grid->get_pixel(x, y - 1) == 0)
                black_px_intervals.push_back(y - 1);
        }
    }
    // Case in which pixel line height is 1px
    if (black_px_intervals.size() & 1)
        black_px_intervals.push_back(black_px_intervals.back());

    // Tail is the maximum continuous black pixels interval 
    int max_interval = -1;
    int tail_y_begin, tail_y_end;
    // Finds tail's begin and end indices
    for (int i = 0; i < black_px_intervals.size(); i+= 2)
    {
        if (black_px_intervals[i+1] - black_px_intervals[i] > max_interval)
        {
            max_interval = black_px_intervals[i+1] - black_px_intervals[i];
            tail_y_begin = black_px_intervals[i];
            tail_y_end = black_px_intervals[i+1];
        }
    }

    return { tail_y_begin, tail_y_end };
}

/** Groups note areas by giving their final type to the areas that can be either line or note */
std::vector<std::vector<int>> OpticalMusicRecognition::group_note_areas(std::vector<std::vector<int>> areas)
{
    for (int i = 0; i < areas.size(); i++)
    {
        // Current area is either line or note and its length is lower or equal than line height
        if (areas[i][0] == m_is_line_or_note && areas[i][1] <= m_line_height)
            areas[i][0] = m_is_line;
        // Current area is either line or note
        else if (areas[i][0] == m_is_line_or_note)
        {
            areas[i][0] = m_is_note;
            // Merge current area to the previous one if it was also a note
            if (i > 0 && areas[i-1][0] == m_is_note)
            {
                areas[i][1] += areas[i-1][1];
                areas.erase(areas.begin() + i - 1);
            }
        }
        // Two contiguous areas are notes
        else if (areas[i][0] == m_is_note && i > 0 && areas[i-1][0] == m_is_note)
        {
            // Updates previous area's count by current area's count
            areas[i][1] += areas[i-1][1];
            areas.erase(areas.begin() + i - 1);
        }
    }
    return areas;
}

/**
 * Categorizes rows areas according to their number of pixels
 * Each area is stored as { area_type, area_black_pixel_count }
 */
std::vector<std::vector<int>> OpticalMusicRecognition::get_note_areas(RegionOfInterest note_roi)
{
    std::vector<int> horz_dist = note_roi.get_horizontal_distrib();
    std::vector<std::vector<int>> areas;

    // Tail rows are the one with the minimum number of black pixels
    int tail_width = *min_element(horz_dist.begin(), horz_dist.end());
    // Line rows have the same quantity of black pixel as the roi's width
    int line_width = note_roi.get_width();

    for (int y = 0; y < note_roi.get_height(); y++)
    {
        // Current row is a tail
        if (horz_dist[y] == tail_width)
        {
            if (areas.empty() || areas.back()[0] != m_is_tail)
                areas.push_back({ m_is_tail, 0 });
            areas.back()[1]++;
        }
        // Current row is a note
        else if (horz_dist[y] != line_width)
        {
            if (areas.empty() || areas.back()[0] != m_is_note)
                areas.push_back({ m_is_note, 0 });
            areas.back()[1]++;
        }
        // Current row is either a note or a line
        else
        {
            if (areas.empty() || areas.back()[0] != m_is_line_or_note)
                areas.push_back({ m_is_line_or_note, 0 });
            areas.back()[1]++;
        }
    }

    return group_note_areas(areas);
}

/** Parses a note region of interest */
void OpticalMusicRecognition::parse_note_roi(RegionOfInterest note_roi)
{
    // Areas define groups of contiguous pixels sharing the same type
    std::vector<std::vector<int>> areas = get_note_areas(note_roi);
    
    // Note's estimated horizontal axis is either first or last row
    int note_horizontal_axis = areas[0][0] == m_is_note ?
        note_roi.get_y_offset() :
        note_roi.get_y_offset() + note_roi.get_height();

    // Finds the index of the reference note axis that minimizes the distance
    // to the estimated note horizontal axis 
    int min_dist = 1e9, min_index = -1;
    int dist;
    for (int i = 0; i < m_notes_y_axis.size(); i++)
    {
        dist = abs(m_notes_y_axis[i] - note_horizontal_axis);
        if (dist < min_dist)
        {
            min_dist = dist;
            min_index = i;
        }
    }
    // Gets the note's name from reference scale
    std::string note = m_reference_scale[min_index];

    // Gets the note's length from the note's center pixel color
    int center_x = note_roi.get_x_offset() + (int) note_roi.get_width() * 0.5;
    int center_y = m_notes_y_axis[min_index];
    // Note is a hald is center pixel is white, else quarter
    note += m_grid->get_pixel(center_x, center_y) ? "H" : "Q";

    m_notes.push_back(note);
}


void OpticalMusicRecognition::read_sheet(std::string rle)
{
    set_rle_source(rle);
    parse_rle_source();
    get_img_roi();
    get_cropped_image();
    compute_notes_y_axis();
    get_local_rois();
    for (auto roi: m_notes_rois)
        parse_note_roi(roi);
}


/** Gets callback */
std::function<bool(int)> OpticalMusicRecognition::get_is_not_zero_callback()
{
    return std::bind(&OpticalMusicRecognition::is_not_zero, this, std::placeholders::_1);
}

/* Callback to check if a value is not zero */
bool OpticalMusicRecognition::is_not_zero(int x) { return x != 0; }
