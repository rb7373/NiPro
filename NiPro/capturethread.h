#ifndef CAPTURETHREAD_H
#define CAPTURETHREAD_H

// Qt header files
#include <QThread>
#include <QtGui>
#include <QDebug>
// OpenCV header files
#include "opencv/highgui.h"

#include "imagebuffer.h"
#include "constants.h"


using namespace cv;



class CaptureThread : public QThread
{
    Q_OBJECT

public:
    CaptureThread(ImageBuffer *buffer);

    // Open camera and return result
    bool connectToCamera(int);

    void disconnectCamera();
    void stopCaptureThread();
    int getAvgFPS();
    bool isCameraConnected();
    int getInputSourceWidth();
    int getInputSourceHeight();
private:
    void updateFPS(int);
    ImageBuffer *imageBuffer;
    VideoCapture cap;
    Mat grabbedFrame;
    QTime t;
    QMutex stoppedMutex;
    int captureTime;
    int avgFPS;
    QQueue<int> fps;
    int sampleNo;
    int fpsSum;
    volatile bool stopped;
protected:
    void run();
};

#endif // CAPTURETHREAD_H
