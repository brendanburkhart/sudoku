#include "quad.hpp"

#include <opencv2/imgproc.hpp>

namespace vision {

Quad::Quad() : valid(false) {}

Quad::Quad(cv::Point2f top_left, cv::Point2f bottom_left,
    cv::Point2f bottom_right, cv::Point2f top_right)
    : valid(true), vertices{ top_left, bottom_left, bottom_right, top_right } {}

float Quad::length(cv::Point2f first, cv::Point2f second) {
    float dx = second.x - first.x;
    float dy = second.y - first.y;

    return sqrt(dx * dx + dy * dy);
}

bool Quad::is_major_diagonal(cv::Point2f first, cv::Point2f second) {
    float dx = second.x - first.x;
    float dy = second.y - first.y;

    if (dx == 0.0) {
        return true;
    }

    float tangent = dy / dx;
    return tangent > 0.0;
}

std::vector<cv::Point2f> Quad::compute_poly(const std::vector<cv::Point>& convex_hull, double percent_error) {
    std::vector<cv::Point2f> float_hull;

    auto point_to_point2f = [](const cv::Point& point) { return cv::Point2f(static_cast<float>(point.x), static_cast<float>(point.y));  };
    std::transform(convex_hull.begin(), convex_hull.end(), std::back_inserter(float_hull), point_to_point2f);

    double epsilon = percent_error * cv::arcLength(convex_hull, true);

    std::vector<cv::Point2f> poly;
    cv::approxPolyDP(float_hull, poly, epsilon, true);
    return poly;
}

Quad Quad::construct(std::vector<cv::Point> hull, double allowed_error) {
    std::vector<cv::Point2f> poly = compute_poly(hull, allowed_error);

    if (poly.size() != 4) {
        return Quad();
    }

    bool is_major_first = is_major_diagonal(poly[0], poly[2]);
    bool is_major_second = is_major_diagonal(poly[1], poly[3]);

    if (is_major_first == is_major_second) {
        return Quad();
    }

    size_t top_left;
    if (is_major_first) {
        top_left = (poly[0].x < poly[2].x) ? 0 : 2;
    } else {
        top_left = (poly[1].x < poly[3].x) ? 1 : 3;
    }

    return Quad(poly[top_left],
        poly[(top_left + 1) % 4],
        poly[(top_left + 2) % 4],
        poly[(top_left + 3) % 4]);
}

bool Quad::is_valid() {
    return valid;
}

double Quad::parallelogram_score() {
    float left_length = length(vertices[0], vertices[1]);
    float bottom_length = length(vertices[1], vertices[2]);
    float right_length = length(vertices[2], vertices[3]);
    float top_length = length(vertices[3], vertices[0]);

    float vertical_score = abs(1.0f - left_length / right_length);
    float horizontal_score = abs(1.0f - top_length / bottom_length);

    float x = vertical_score + horizontal_score;
    return 1.0 / (2.0*x + 1.0);
}

std::array<cv::Point2f, 4> Quad::get_vertices() {
    return vertices;
}

}
