#ifndef COLORHISTOGRAM_H
#define COLORHISTOGRAM_H

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>

class ColorHistogram
{
private:
    int histSize[3]; // number of bins
    float hranges[2]; // min and max pixel value
    const float* ranges[3]; // rangos para cada color
    int channels[3]; //canales

public:
    ColorHistogram();
    cv::MatND getHistogram(const cv::Mat &image);

    //The cv::SparseMat data structure that
    //is designed to represent large sparse
    //matrices (that is, matrices with
    //very few non-zero elements) without consuming too much
    //memory.

    cv::SparseMat getSparseHistogram(const cv::Mat &image);

    // Computes the 1D Hue histogram with a mask.
    // BGR source image is converted to HSV
    // Pixels with low saturation are ignored

    cv::MatND getHueHistogram(const cv::Mat &image,
                              int minSaturation=0);


    cv::Mat colorReduce(const cv::Mat &image, int div=64);

};

#endif // COLORHISTOGRAM_H
