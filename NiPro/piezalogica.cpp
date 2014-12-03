#include "piezalogica.h"

PiezaLogica::PiezaLogica(int pID,
                         int pErodeNumberOfIterations,
                         int pColorDistanceThreshold,
                         int pR, int pG, int pB,
                         std::vector<cv::KeyPoint> pObjectKeypoints,
                         Mat pObjectData,
                         int pRows,
                         int pCols,
                         QObject *parent) :
    QObject(parent)
{
    _ID = pID;
    _ErodeNumberOfIterations = pErodeNumberOfIterations;
    _ColorDistanceThreshold = pColorDistanceThreshold;

    _R = pR;
    _G = pG;
    _B = pB;

//        _R = qrand() % 256;
//        _G = qrand() % 256;
//        _B = qrand() % 256;

    _Rows = pRows;
    _Cols = pCols;


    objectKeypoints = pObjectKeypoints;
    objectData = pObjectData;

//    _ID_R = qrand() % 256;
//    _ID_G = qrand() % 256;
//    _ID_B = qrand() % 256;

}

PiezaLogica::~PiezaLogica()
{
    qDebug() << "###";
    qDebug() << "Se ha liberado memoria de pieza logica "<< "Id: " << _ID;
    qDebug() << "###";
}
