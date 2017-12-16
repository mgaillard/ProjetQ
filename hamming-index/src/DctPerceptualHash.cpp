#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <nmmintrin.h>

#include "DctPerceptualHash.h"

uint64_t DctPerceptualHash(vector<char>& binary_image)
{
    uint64_t hash = 0;

    cv::Mat input;
    cv::Mat grayImg;
    cv::Mat bluredImg;
    cv::Mat resizeImg;
    cv::Mat resizeFImg;
    cv::Mat dctImg;

    // Convert the binary image into an OpenCV Mat.
    cv::Mat raw_data(binary_image);

    input = cv::imdecode(raw_data, cv::IMREAD_COLOR);

    if (input.data == NULL || (input.type() != CV_8UC3 && input.type() != CV_8U)) {
        // If there is a reading error, return a null hash.
        cerr << "Error reading image" << endl;
        return 0;
    }

    // Convert the image to grayscale using its luminance
    if(input.type() == CV_8UC3) {
        cv::cvtColor(input, grayImg, CV_BGR2GRAY);
    } else {
        grayImg = input;
    }

    // Mean filter with kernel 7x7.
    cv::blur(grayImg, bluredImg, cv::Size(7, 7));

    // Resize the image to 32x32 pixels.
    cv::resize(bluredImg, resizeImg, cv::Size(32,32));

    resizeImg.convertTo(resizeFImg, CV_32F);
    cv::dct(resizeFImg, dctImg);

    std::vector<float> topLeftDCTCoeffs;
    // Take only the coefficients in the rectangle (1, 1) ; (9, 9).
    topLeftDCTCoeffs.reserve(64);
    for (int i = 1; i <= 8; i++) {
        for (int j = 1; j <= 8; j++) {
            topLeftDCTCoeffs.push_back(dctImg.at<float>(i, j));
        }
    }

    // Compute the median
    std::vector<float> coeffs(topLeftDCTCoeffs);

    // The median of a 64 elements array is the mean between the 31th and the 32th element.
    float median = 0;
    std::nth_element(coeffs.begin(), coeffs.begin() + coeffs.size()/2, coeffs.end());
    median += coeffs[coeffs.size()/2];
    std::nth_element(coeffs.begin(), coeffs.begin() + coeffs.size()/2 - 1, coeffs.end());
    median += coeffs[coeffs.size()/2 - 1];
    median /= 2;

    // Transform into a 64 bits integer.
    for (unsigned int i = 0; i < topLeftDCTCoeffs.size(); i++) {
        hash <<= 1;
        if (topLeftDCTCoeffs[i] >= median) {
            hash |= 1;
        }
    }

    return hash;
}

int DctPerceptualHashDistance(uint64_t x, uint64_t y)
{
#if defined(__GNUC__) || defined(__GNUG__)
    return __builtin_popcountll(x ^ y);
#elif defined(_MSC_VER)
    return _mm_popcnt_u64(x ^ y);
#endif
}
