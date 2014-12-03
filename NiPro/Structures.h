#ifndef STRUCTURES_H
#define STRUCTURES_H

// Qt header files
#include <QtGui>

// ImageProcessingSettings structure definition
struct ImageProcessingSettings{
    int smoothType;
    int smoothParam1;
    int smoothParam2;
    double smoothParam3;
    double smoothParam4;
    int dilateNumberOfIterations;
    int erodeNumberOfIterations;
    int flipCode;
    double cannyThreshold1;
    double cannyThreshold2;
    int cannyApertureSize;
    bool cannyL2gradient;
    int encontrarPieza;
    int colorDistanceThreshold;
};

// ImageProcessingFlags structure definition
struct ImageProcessingFlags{
    bool grayscaleOn;
    bool smoothOn;
    bool dilateOn;
    bool erodeOn;
    bool flipOn;
    bool cannyOn;
    bool encontrarPiezas;
    bool encontrarPieza;
};

// TaskData structure definition
struct TaskData{
    QRect selectionBox;
    bool setROIFlag;
    bool resetROIFlag;
};

// MouseData structure definition
struct MouseData{
    QRect selectionBox;
    bool leftButtonRelease;
    bool rightButtonRelease;
};

#endif // STRUCTURES_H
