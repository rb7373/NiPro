#ifndef PROCESSINGTHREAD_H
#define PROCESSINGTHREAD_H

#include "Structures.h"
#include "colordetector.h"

// Qt header files
#include <QThread>
#include <QtGui>

// OpenCV header files
#include <opencv2/highgui/highgui.hpp>

#include "imagebuffer.h"
#include "constants.h"
#include "mattoqimage.h"

//Procesamiento especifico

#include "colorhistogram.h"
#include "objectFinder.h"
#include "administradorpiezas.h"
//#include "mainmanager.h"
#include "piezathreadprocesamiento.h"

#include <cmath>

using namespace cv;

class ProcessingThread : public QThread
{
    Q_OBJECT

public:
    ProcessingThread(ImageBuffer *imageBuffer, int inputSourceWidth, int inputSourceHeight);
    ~ProcessingThread();
    void stopProcessingThread();
    int getAvgFPS();
    int getCurrentSizeOfBuffer();
    Rect getCurrentROI();

    AdministradorPiezas *_AdministradorPiezas;


private:
    void updateFPS(int);
    void setROI();
    void resetROI();

    void processA(Mat &image, cv::Rect pRect);
    void inicializarFichas();

    ImageBuffer *imageBuffer;
    volatile bool stopped;
    int inputSourceWidth;
    int inputSourceHeight;
    int currentSizeOfBuffer;
    Mat currentFrame;
    Mat backGroundFrame;
    Mat currentFrameGrayscale;
    Rect originalROI;
    Rect currentROI;
    QImage frame;
    QTime t;
    int processingTime;
    QQueue<int> fps;
    int fpsSum;
    int sampleNo;
    int avgFPS;
    QMutex stoppedMutex;
    QMutex updateMembersMutex;
    Size frameSize;
    Point framePoint;
    // Image processing flags
    bool grayscaleOn;
    bool smoothOn;
    bool dilateOn;
    bool erodeOn;
    bool flipOn;
    bool cannyOn;
    bool findPieces;
    bool findPiece;

    // Image processing settings
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
    bool setROIFlag;
    bool resetROIFlag;
    Rect selectionBox;

    const PiezaLogica* piezaTemp;

    // Create image processor object
    ColorDetector *_ColorDetector;

    QString path;

    QList <PiezaThreadProcesamiento*> _ListaPiezas;
    const PiezaLogica *_TempPieza;

    cv::FeatureDetector * detector;
    cv::DescriptorExtractor * extractor;

protected:
    void run();
private slots:
    void updateImageProcessingFlags(struct ImageProcessingFlags);
    void updateImageProcessingSettings(struct ImageProcessingSettings);
    void updateTaskData(struct TaskData);
signals:
    void newFrame(const QImage &frame);
    void nuevaPieza(float pX, float pY, float pWidth, float pHeight, int pID);
    void piezaActual(int pID);
    void iniciaProcesamientoEspecial(bool inicia);

};

#endif // PROCESSINGTHREAD_H
