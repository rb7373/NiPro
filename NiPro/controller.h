#ifndef CONTROLLER_H
#define CONTROLLER_H



// Qt header files
#include <QtGui>
// OpenCV header files
#include <opencv/highgui.h>

#include "imagebuffer.h"
#include "processingthread.h"
#include "capturethread.h"
#include "Structures.h"


class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    ~Controller();

    ImageBuffer *_ImageBuffer;
    ProcessingThread *processingThread;
    CaptureThread *captureThread;
    bool connectToCamera(int,int,bool,int,int);
    void disconnectCamera();
    void stopCaptureThread();
    void stopProcessingThread();
    void deleteCaptureThread();
    void deleteProcessingThread();
    void clearImageBuffer();
    void deleteImageBuffer();



private:
    int _ImageBufferSize;

signals:
    void camDisconnected();

private slots:
    void deletedProcessingThread();


};

#endif // CONTROLLER_H
