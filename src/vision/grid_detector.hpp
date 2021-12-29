#pragma once

#include <array>
#include <iostream>
#include <opencv2/core.hpp>
#include <vector>

namespace vision {

class GridDetection {
public:
    class Parameters {
    public:
        Parameters(double min_size, double poly_approx_error, double shape_threshold);
        static Parameters default();

        double min_size;
        double poly_approx_error;
        double shape_threshold;
    };

    static GridDetection construct(const cv::Mat& image, const Parameters& parameters);

    bool grid_found();
    std::vector<cv::Point> get_hull();
    std::array<cv::Point2f, 4> get_poly();
    std::vector<cv::Point2f> get_grid_points();
    cv::Mat extract_cell(int i, int j);

private:
    double min_size_ratio = 0.25;
    double shape_threshold = 0.80;

    bool detected;
    cv::Mat grid_image;
    std::vector<cv::Point> grid_hull;
    std::array<cv::Point2f, 4> grid_poly;
    std::vector<cv::Point2f> grid_points;

    static constexpr int cell_size = 100;
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

}  // namespace vision
