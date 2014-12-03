#ifndef SUBPROCESADORIMAGENES_H
#define SUBPROCESADORIMAGENES_H

#include <QDebug>
#include <QDir>
#include <QGuiApplication>
#include <QFileDialog>

#include "constants.h"
#include "colorhistogram.h"
#include "objectFinder.h"

//OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

class SubProcesadorImagenes
{
public:
    SubProcesadorImagenes();
    ~SubProcesadorImagenes();
    bool obtenerColoresPrincipales(int pID);

public:
    int getColorR();
    int getColorB();
    int getColorG();


private:
    int _R;
    int _B;
    int _G;

    /// Establish the number of bins
    int histSize;

    /// Set the ranges ( for B,G,R) )
    float range[2];
    const float* histRange;

    bool uniform;
    bool accumulate;

    //int _ArregloColoresPrincipales[];
    //OpenCV
    cv::Mat imageTemp;
};

#endif // SUBPROCESADORIMAGENES_H
