# Optical music recognition

The task is to parse the notes contained in a sheet of music given as a run-length encoded string.

## Data structures

### Grid

A grid is a wrapper to store a 2d binary table extended util functions (get width and height, get columns and rows, get pixel, get subgrid).

Each cell is `true` if the pixel is on, else `false`

### Region of interest

A region of interest (ROI) is an area in a picture containing relevant information.

The broadest ROI is the picture itself, the smallest ROIs are the squares in which individual keys can be found.

A ROI is composed of :

- one binary grid containing the region's raw data
- one x-y offset vector (computed from the ROI's upper left corner's coordinates, the origin [0, 0] being the global image's upper left corner)
- two histograms, storing the quantity of black pixel in each rows and columns respectively

### RLE parser

The RLE parser is in charge of extracting significant data from the RLE string.

It fills in a 2D grid and computes horizontal - vertical distributions as it reads the RLE string.

It uses the generated 2d grid and distributions to create the global region of interest.