#pragma once

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <optional>
#include <vector>

#include "../common/sudoku.hpp"
#include "grid_detector.hpp"
#include "ocr.hpp"

namespace vision {

class Vision {
public:
    /**
     * If debug_mode is set, intermediate CV steps will be displayed.
     */
    Vision(bool debug_mode);

    bool init();
    bool capture_frame();
    std::optional<common::Sudoku> extract_puzzle();
    void add_solution(common::Sudoku puzzle, common::Sudoku solution);
    bool display_solution();

private:
    cv::Mat image;
    OCR ocr;
    cv::VideoCapture capture;

    bool debug_mode;

    common::Sudoku stored_puzzle;
    common::Sudoku stored_solution;
};

}  // namespace vision
