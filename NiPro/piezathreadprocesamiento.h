#ifndef PIEZATHREADPROCESAMIENTO_H
#define PIEZATHREADPROCESAMIENTO_H

#include <QDebug>
#include <QtGui/QApplication>
#include <QDir>


#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"

using namespace cv;

class PiezaThreadProcesamiento
{
public:
    PiezaThreadProcesamiento(int pId);

public:
    QString path;
    cv::Mat objectImg;
    std::vector<cv::KeyPoint> objectKeypoints;
    cv::Mat objectDescriptors;
    cv::FeatureDetector * detector;
    cv::DescriptorExtractor * extractor;

};

#endif // PIEZATHREADPROCESAMIENTO_H
