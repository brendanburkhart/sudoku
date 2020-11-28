#pragma once

#include <array>
#include <vector>

#include <opencv2/core.hpp>

namespace vision {

class Quad {
public:
    static Quad construct(std::vector<cv::Point> hull, double allowed_error);

    bool is_valid();
    double parallelogram_score();
    std::array<cv::Point2f, 4> get_vertices();

private:
    std::array<cv::Point2f, 4> vertices;
    bool valid;

    Quad();
    Quad(cv::Point2f top_left, cv::Point2f bottom_left, cv::Point2f bottom_right, cv::Point2f top_right);

    static float length(cv::Point2f first, cv::Point2f second);
    static bool is_major_diagonal(cv::Point2f first, cv::Point2f second);
    static std::vector<cv::Point2f> compute_poly(const std::vector<cv::Point>& hull, double percent_error);
};

}
