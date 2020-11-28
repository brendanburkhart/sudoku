#pragma once

#include <array>
#include <iostream>
#include <vector>

#include <opencv2/core.hpp>

namespace vision {

class GridDetection {
public:
    static GridDetection construct(const cv::Mat& image);

    bool grid_found();
    std::vector<cv::Point> get_hull();
    std::array<cv::Point2f, 4> get_poly();
    std::vector<cv::Point2f> get_grid_points();
    cv::Mat extract_cell(int i, int j);

private:
    static constexpr double min_size_ratio = 0.25;

    bool detected;
    cv::Mat grid_image;
    std::vector<cv::Point> grid_hull;
    std::array<cv::Point2f, 4> grid_poly;
    std::vector<cv::Point2f> grid_points;
    
    static constexpr int cell_size = 50;
    static std::vector<cv::Point2f> construct_grid_points();
    static std::vector<cv::Point2f> construct_grid_hull();

    GridDetection();
    GridDetection(std::vector<cv::Point> grid_hull, std::array<cv::Point2f, 4> grid_poly,
        std::vector<cv::Point2f> grid_points, cv::Mat grid_image);

    static cv::Mat threshold(const cv::Mat& image);
    static cv::Mat extract_grid(const cv::Mat& image, const cv::Mat& homography);
    static std::vector<cv::Point> compute_convex_hull(const cv::Mat& thresholded);
    static cv::Mat identify(const std::array<cv::Point2f, 4>& grid_poly);
};

}
