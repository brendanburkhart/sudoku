# Sudoku Solver

Sudoku solver, can detect and solve Sudoku puzzles from an image or video.

## Building

You will need [CMake](https://cmake.org/) and [vcpkg](https://github.com/Microsoft/vcpkg) installed in order to build this project.

The Sudoku grid recognition relies on OpenCV for the computer vision and Tesseract for the OCR, both which need to be installed, as well as GTest for the units tests. The CMake integration for vcpkg should download and build local copies of these dependencies when CMake configuration is run.

## Usage

CMake builds three targets:
- `sudoku`, built from `src/main.cpp`, which tries to find, solve, and display solutions to Sudoku puzzles shown to the first camera OpenCV finds.
- `sudoku_test` which runs the unit tests from `test/` using Google Test.
- `sudoku_benchmark`, built from `src/benchmark/benchmark.cpp`, which times how long it takes to solve six different Sudoku puzzles of varying levels of difficulty over and over, and can be used to judge the effect of optimizations.

## Design

### Solver

Each cell in the Sudoku puzzle is represented as an Options, which tracks the available values for each cell. Solving the puzzle is done by methodically reducing the remaining available values for each cell down to a single value. Internally, the Options uses an integer as a bit array, where the least significant bit represents 1, the next represents 2, then 3, up till the most significant bit used which represents 9. For example, 20 is 0b10100, an Options with value 20 represents both 3 and 5 being possible values for that cell. This representation allows useful operations like adding and removing values from the Options to be implemented as simple bitwise operations.

The grid coordinates are 0 through 8, with (0, 0) being the top-left corner of the grid, and (8, 0) being the bottom-left corner. Any time cells are referenced using coordinates, the first parameter/variable is the vertical axis.

The Sudoku grid is split up into 27 Regions - nine columns, nine rows, and nine boxes, each containing references to their nine cell Options. Each cell is in one column, one row, and one box, which contain a pointer to the same Options, so any changes made by one Region is visible in the others. Two primary operations are supported by Regions. The first, elimination, simply removes solved values from other cells in the Region. For example, if a cell is solved and must contain a 7, then 7 can be eliminated as a possibility in all other cells in the Region. The second operation, exclusion, is a bit more complex. If n cells possibilities only ever occur together, and furthermore occur in exactly n cells together, then all other possibilities can be excluded from those cells. For example, if three cells could possibily be 2, 5, or 6 (with other possibilities are well), and no other cells in the Region contain a 2, 5, or 6 (either alone or together), then those three cells must be where 2, 5, and 6 go, and any other possibilties for those cells can be removed.

Each Region also exposes manipulation operations which are useful for solving operations involving multiple Regions. Each Region is divided into three segments: segment 0 is the first three cells, segment 1 the middle three, and segment 2 the last three. The available_in_segment methods returns an Options contain all values that could possibly occur in that segment, restrict_to_segment makes it so the specified Options are only available in that segment, and exclude_from_segment makes it so the specified options are only available outside of the segment.

The Sudoku grid is also split up into six SuperRegions, each containing three Regions. A single SuperRegion contains only adjacent column Regions, or adjacent row Regions, which all fall within the same three box Regions. For example, the first column SuperRegion contains the first three columns the puzzle. SuperRegions support two operations: restrict_between, and restrict_within. 
The restrict_between checks if for any of the boxes of the SuperRegion, only one of the three Regions could possibly have specific values. If so, that values must occur within that segment of the Region (that is, it has to fall within that box). The restrict_within looks for a segment of a Region that must have a specific value somewhere in the Region, and removes that possibility from the corresponding segment of other Regions in the same box. Look at `test/solver/super_region_test.cpp` for examples.

Solving is done by applying the exclusion and restriction operations to the Regions/SuperRegions over and over again until changes after a full pass, or the puzzle is solved. Note that the elimination operation has to be applied to the entire puzzle between all the other operations, or they might falsely assume a value is a valid possibility that is not.

### Vision

The first step in recognizing and extracting a Sudoku puzzle from an image is detecting the border/outline of the puzzle. To help with this, OpenCV's adaptive threshold is used to binarize the image. Next, the largest convex hull is found. A Quad is constructed from this, which is done by approximating the convex hull as a polygon. If the convex hull was too small, or the Quad is a bad fit for the hull, the detection fails.

Once the outline of the puzzle has been identified, a homography is constructed to deskew and straighten the region of the image containing the puzzle. The individual cells can be then extracted as square, aligned images.

Next, the images of the cells are checked to see if they are empty or not. If not, they are passed through Tesseract OCR to extract the digit, and a puzzle can be constructed.
