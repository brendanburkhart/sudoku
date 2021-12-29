#include "ocr.hpp"

#include <iostream>
#include <string>

#include <leptonica/allheaders.h>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <tesseract/baseapi.h>

namespace vision {

OCR::OCR() : tesseract(std::make_unique<tesseract::TessBaseAPI>()) {
    tesseract->Init("tesseract_data", "eng", tesseract::OEM_LSTM_ONLY);
    tesseract->SetDebugVariable("debug_file", "/dev/null");
    tesseract->SetVariable("tessedit_char_whitelist", "123456789");

    tesseract->SetPageSegMode(tesseract::PSM_SINGLE_CHAR);
}

cv::Mat OCR::preprocess(cv::Mat image) {
    //cv::Mat gray;
    //cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    ////cv::GaussianBlur(gray, gray, cv::Size(5, 5), 0.0);

    //cv::Mat thresholded;
    //cv::adaptiveThreshold(gray, thresholded, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 21, 3);

    //return thresholded;

    //cv::Mat thresholded;
    //cv::threshold(image, thresholded, 0, 255, cv::THRESH_BINARY + cv::THRESH_OTSU);

    return image;
}

std::optional<int> OCR::extract_digit(cv::Mat image) {
    cv::Mat processed = preprocess(image);

    //double mean = cv::mean(processed)[0];
    /*if (mean > 0.95 * 255.0) {
        return std::nullopt;
    }*/

    tesseract->SetImage(processed.data, processed.cols, processed.rows, static_cast<int>(processed.elemSize()), static_cast<int>(processed.step));
    tesseract->SetSourceResolution(3 * processed.rows);

    std::unique_ptr<char[]> data = std::unique_ptr<char[]>(tesseract->GetUTF8Text());
    std::string text = std::string(data.get());

    if (text.length() != 2 || !std::isdigit(text[0])) {
        return std::nullopt;
    }

    return std::optional<int>(std::stoi(text));
}

}
