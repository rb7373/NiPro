#ifndef PIEZALOGICA_H
#define PIEZALOGICA_H

#include <QObject>
#include <QDebug>
#include <QtGlobal>


// OpenCV header files
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class PiezaLogica : public QObject
{
    Q_OBJECT
public:
    explicit PiezaLogica(int pID,
                         int pErodeNumberOfIterations,
                         int pColorDistanceThreshold,
                         int pR,
                         int pG,
                         int pB,
                         std::vector<cv::KeyPoint> pObjectKeypoints,
                         cv::Mat pObjectData,
                         int pRows,
                         int pCols,
                         QObject *parent = 0);
    virtual ~PiezaLogica();

    int _ID;
    int _ErodeNumberOfIterations;
    int _ColorDistanceThreshold;
    int _R;
    int _G;
    int _B;
    int _Rows;
    int _Cols;

    int _ID_R;
    int _ID_G;
    int _ID_B;

    std::vector<cv::KeyPoint> objectKeypoints;
    cv::Mat objectData;


signals:
    
public slots:

private:



    
};

#endif // PIEZALOGICA_H
