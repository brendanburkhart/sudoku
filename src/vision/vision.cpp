#include "vision.hpp"

#include <algorithm>
#include <string>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "../common/sudoku.hpp"

namespace vision {

bool Vision::init() {
    capture.open(0);

    return capture.isOpened();
}

bool Vision::capture_frame() {
    bool ok = capture.read(image);
    return ok && !image.empty();
}

std::optional<common::Sudoku> Vision::extract_puzzle() {
    GridDetection detection = GridDetection::construct(image);

    if (!detection.grid_found()) {
        return std::nullopt;
    }

    common::Sudoku puzzle;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cv::Mat cell = detection.extract_cell(i, j);
            std::optional<int> digit = ocr.extract_digit(cell);

            if (digit) {
                puzzle.set_cell(i, j, digit.value());
            }
        }
    }

    return std::optional<common::Sudoku>(puzzle);
}

void Vision::add_solution(common::Sudoku puzzle, common::Sudoku solution) {
    stored_puzzle = puzzle;
    stored_solution = solution;
}

bool Vision::display_solution() {
    int cell_size = 50;
    cv::Mat solution = cv::Mat(cell_size * 9, cell_size * 9, CV_8UC3, cv::Scalar(255, 255, 255));

    for (int i = 0; i < 10; i++) {
        int width = (i % 3 == 0) ? 4 : 2;
        cv::line(solution, cv::Point(0, i * cell_size), cv::Point(9 * cell_size, i * cell_size), cv::Scalar(0, 0, 0), width);
        cv::line(solution, cv::Point(i * cell_size, 0), cv::Point(i * cell_size, 9 * cell_size), cv::Scalar(0, 0, 0), width);
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (stored_solution.get_cell(i, j)) {
                cv::Scalar color;
                if (stored_puzzle.get_cell(i, j)) {
                    color = cv::Scalar(255, 100, 75);
                } else {
                    color = cv::Scalar(0, 0, 0);
                }

                cv::putText(solution, std::to_string(stored_solution.get_cell(i, j).value()), cv::Point(j * cell_size + cell_size / 4, (i + 1) * cell_size - cell_size / 4),
                    cv::FONT_HERSHEY_SIMPLEX, 1.0, color, 2);
            }
        }
    }

    cv::imshow("Solution", solution);

    if (cv::waitKey(5) >= 0) {
        return false;
    }

    return true;
}

}
