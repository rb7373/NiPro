#include "controller.h"

Controller::Controller(QObject *parent) :
    QObject(parent)
{
    //qDebug("Controlador creado");
}// Controller constructor


Controller::~Controller()
{
    //qDebug("Controlador destruido");
} // Controller destructor

bool Controller::connectToCamera(int deviceNumber,
                                 int pImageBufferSize,
                                 bool dropFrame,
                                 int capThreadPrio,
                                 int procThreadPrio)
{
    // Local variables
    bool isOpened=false;

    // Store imageBufferSize in private member
    _ImageBufferSize=pImageBufferSize;

    // Create image buffer with user-defined settings
    _ImageBuffer = new ImageBuffer(pImageBufferSize,dropFrame);

    // Create capture thread
    captureThread = new CaptureThread(_ImageBuffer);

    // Attempt to connect to camera

    isOpened=captureThread->connectToCamera(deviceNumber);

    if(isOpened)
    {
        // Create processing thread
        processingThread = new ProcessingThread(_ImageBuffer,
                                                captureThread->getInputSourceWidth(),
                                                captureThread->getInputSourceHeight());

        // Start capturing frames from camera
        captureThread->start((QThread::Priority)capThreadPrio);
        // Start processing captured frames
        processingThread->start((QThread::Priority)procThreadPrio);

        connect(processingThread, SIGNAL(destroyed()),this,SLOT(deletedProcessingThread()));

    }
    else
    {
        // Delete capture thread
        deleteCaptureThread();
        // Delete image buffer
        deleteImageBuffer();
    }
    // Return camera open result
    return isOpened;
} // connectToCamera()

void Controller::stopCaptureThread()
{
    //qDebug() << "-------------------";
    //qDebug() << "Deteniendo el hilo de captura...";

    captureThread->stopCaptureThread();

    // Take one frame off a FULL queue to allow the capture thread to finish
    if(_ImageBuffer->getSizeOfImageBuffer()==_ImageBufferSize)
    {
        //Modificar
        Mat temp=_ImageBuffer->getFrame();
    }
    captureThread->wait();

    //qDebug() << "Hilo de captura exitosamente detenido";
    //qDebug() << "-------------------";

} // stopCaptureThread()

void Controller::stopProcessingThread()
{

    //qDebug() << "-------------------";
    //qDebug() << "Deteniendo el hilo de procesamiento de imagenes...";
    processingThread->stopProcessingThread();
    processingThread->wait();
    //qDebug() << "Hilo de procesamiento de imagenes exitosamente detenido";
    //qDebug() << "-------------------";

} // stopProcessingThread()

void Controller::deleteCaptureThread()
{
    // Delete thread
    delete captureThread;
} // deleteCaptureThread()

void Controller::deleteProcessingThread()
{
    // Delete thread
    delete processingThread;
} // deleteProcessingThread()

void Controller::clearImageBuffer()
{
    _ImageBuffer->clearBuffer();
} // clearImageBuffer()

void Controller::deleteImageBuffer()
{
    // Delete image buffer
    delete _ImageBuffer;
} // deleteImageBuffer()


void Controller::disconnectCamera()
{
    // Stop processing thread
    if(processingThread->isRunning())
        stopProcessingThread();
    // Stop capture thread
    if(captureThread->isRunning())
        stopCaptureThread();
    // Clear image buffer
    clearImageBuffer();
    // Disconnect camera
    captureThread->disconnectCamera();
    // Delete threads
    deleteCaptureThread();
    deleteProcessingThread();
    // Delete image buffer
    deleteImageBuffer();

} // disconnectCamera()

void Controller::deletedProcessingThread()
{
    emit camDisconnected();
}
