#pragma once

#include <iostream>
#include <optional>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

#include "grid_detector.hpp"
#include "ocr.hpp"
#include "../common/sudoku.hpp"

namespace vision {

class Vision {
public:
    bool init();
    bool capture_frame();
    std::optional<common::Sudoku> extract_puzzle();
    void add_solution(common::Sudoku puzzle, common::Sudoku solution);
    bool display_solution();

private:
    cv::Mat image;
    OCR ocr;
    cv::VideoCapture capture;

    common::Sudoku stored_puzzle;
    common::Sudoku stored_solution;
};

}
