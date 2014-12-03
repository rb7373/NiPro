#ifndef ADMINISTRADORPIEZAS_H
#define ADMINISTRADORPIEZAS_H

#include <QObject>
#include <QDebug>
#include <QList>

#include <QGuiApplication>

// OpenCV header files
#include <opencv/highgui.h>
#include <opencv2/features2d/features2d.hpp>

#include "constants.h"
#include "piezalogica.h"
#include "administradorxml.h"

using namespace cv;

class AdministradorPiezas : public QObject
{
    Q_OBJECT
public:
    explicit AdministradorPiezas(QObject *parent = 0);
    virtual ~AdministradorPiezas();

    //Una pieza ya existente se le modifican los parametros
    void actualizarPiezaLogica(int pId,
                               int pR,
                               int pG,
                               int pB);

    //Una pieza ya existente se le modifican los parametros
    void actualizarPiezaLogica(int pID,
                               int pErodeNumberOfIterations,
                               int pColorDistanceThreshold,
                               int pR,
                               int pG,
                               int pB);

    const PiezaLogica* at(int pIndex);
    const int sizeLista();



signals:
    
public slots:
    void agregarPiezaLogica(int pID,
                            int pErodeNumberOfIterations,
                            int pColorDistanceThreshold,
                            int pR,
                            int pG,
                            int pB);



private:
    QList<PiezaLogica*> _ListaPiezas;
    QString path;
    cv::FeatureDetector * detector;
    cv::DescriptorExtractor * extractor;


private:
    //void actualizarPieza(int pId);
    
};

#endif // ADMINISTRADORPIEZAS_H
