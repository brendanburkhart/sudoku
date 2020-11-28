#pragma once

#include <optional>

#include <opencv2/core.hpp>
#include <tesseract/baseapi.h>

namespace vision {

class OCR {
public:
    OCR();

    std::optional<int> extract_digit(cv::Mat image);

private:
    std::unique_ptr<tesseract::TessBaseAPI> tesseract;

    cv::Mat preprocess(cv::Mat image);
};

}
