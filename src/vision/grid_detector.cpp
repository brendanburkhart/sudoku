#include "grid_detector.hpp"

#include <algorithm>

#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "quad.hpp"

namespace vision {

std::vector<cv::Point2f> GridDetection::construct_grid_points() {
    std::vector<cv::Point2f> points;

    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 10; j++) {
            points.push_back(cv::Point2f(
                static_cast<float>(cell_size * i),
                static_cast<float>(cell_size * j)));
        }
    }

    return points;
}

std::vector<cv::Point2f> GridDetection::construct_grid_hull() {
    std::vector<cv::Point2f> all_points = construct_grid_points();
    std::vector<cv::Point2f> points = { all_points[0], all_points[9 * 10], all_points[9 * 10 + 9], all_points[9] };

    return points;
}

cv::Mat GridDetection::threshold(const cv::Mat& image) {
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    cv::Mat thresholded;
    gray.convertTo(thresholded, CV_8UC1);
    cv::adaptiveThreshold(thresholded, thresholded, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY_INV, 17, 8);
    
    return thresholded;
}

cv::Mat GridDetection::extract_grid(const cv::Mat& image, const cv::Mat& homography) {
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    
    cv::Mat thresholded;
    cv::threshold(gray, thresholded, 0, 255, cv::THRESH_BINARY + cv::THRESH_OTSU);

    cv::Mat grid_image;
    cv::warpPerspective(thresholded, grid_image, homography, cv::Size(cell_size * 9, cell_size * 9));

    return grid_image;
}

std::vector<cv::Point> GridDetection::compute_convex_hull(const cv::Mat& thresholded) {
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(thresholded, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

    if (contours.size() == 0) {
        return std::vector<cv::Point>();
    }

    auto convex_hull = [](std::vector<cv::Point>& contour) {
        std::vector<cv::Point> convex_hull;
        cv::convexHull(contour, convex_hull);
        return convex_hull;
    };

    std::vector<std::vector<cv::Point>> candidate_hulls;
    std::transform(contours.begin(), contours.end(), std::back_inserter(candidate_hulls), convex_hull);

    auto area_comparator = [](const std::vector<cv::Point>& lhs, const std::vector<cv::Point>& rhs) {
        return cv::contourArea(lhs) < cv::contourArea(rhs);
    };

    auto hull_ptr = std::max_element(candidate_hulls.begin(), candidate_hulls.end(), area_comparator);
    return *hull_ptr;
}

cv::Mat GridDetection::identify(const std::array<cv::Point2f, 4>& grid_poly) {
    std::vector<cv::Point2f> aligned_rect = construct_grid_hull();
    
    return cv::findHomography(grid_poly, aligned_rect);
}

GridDetection::GridDetection() : detected(false) {}

GridDetection::GridDetection(std::vector<cv::Point> grid_hull, std::array<cv::Point2f, 4> grid_poly,
    std::vector<cv::Point2f> grid_points, cv::Mat grid_image)
    : detected(true), grid_hull(grid_hull), grid_poly(grid_poly), grid_image(grid_image), grid_points(grid_points) {}

GridDetection GridDetection::construct(const cv::Mat& image) {
    cv::Mat thresholded = threshold(image);

    auto hull = compute_convex_hull(thresholded);

    double min_area = min_size_ratio * static_cast<double>(image.rows) * static_cast<double>(image.cols);
    bool detected = cv::contourArea(hull) > min_area;

    if (!detected) {
        return GridDetection();
    }

    auto quad = Quad::construct(hull, 0.05);
    if (!quad.is_valid() || quad.parallelogram_score() < 0.8) {
        return GridDetection();
    }

    auto homography = identify(quad.get_vertices());
    cv::Mat grid_image = extract_grid(image, homography);

    std::vector<cv::Point2f> grid_points;
    auto aligned_points = construct_grid_points();
    cv::perspectiveTransform(aligned_points, grid_points, homography.inv());
    
    return GridDetection(hull, quad.get_vertices(), grid_points, grid_image);
}

bool GridDetection::grid_found() {
    return detected;
}

std::vector<cv::Point> GridDetection::get_hull() {
    return grid_hull;
}

std::array<cv::Point2f, 4> GridDetection::get_poly() {
    return grid_poly;
}

std::vector<cv::Point2f> GridDetection::get_grid_points() {
    return grid_points;
}

cv::Mat GridDetection::extract_cell(int i, int j) {
    cv::Rect cell = cv::Rect(j * cell_size + cell_size / 10, i * cell_size + cell_size / 10,
        8 * (cell_size/10), 8 * (cell_size/10));

    return cv::Mat(grid_image, cell);
}

}
