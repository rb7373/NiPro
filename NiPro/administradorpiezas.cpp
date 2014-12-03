#include "administradorpiezas.h"



AdministradorPiezas::AdministradorPiezas(QObject *parent) :
    QObject(parent)
{

    QDir::setCurrent(QCoreApplication::applicationDirPath());
    path = QDir::currentPath()+"/fichas/pieza";

    detector = new cv::FastFeatureDetector();
    extractor = new cv::SurfDescriptorExtractor();

}

AdministradorPiezas::~AdministradorPiezas()
{

    delete detector;
    delete extractor;

    qDebug() << "###";
    qDebug() << "Se ha liberado memoria del administrador de piezas";
    qDebug() << "###";
}

void AdministradorPiezas::agregarPiezaLogica(int pID,
                                             int pErodeNumberOfIterations,
                                             int pColorDistanceThreshold,
                                             int pR,
                                             int pG,
                                             int pB)
{
    QString rutaPieza = path +
            QString::number(pID)+
            ".png";

    QFile file(rutaPieza);

    if (file.exists() == true)
    {

        //qDebug() << "Procesando cargar imagen";

        //qDebug() << "Imagen: " << rutaPieza;

        Mat objectImg = imread(rutaPieza.toAscii().data());

        if( objectImg.data)
        {

            std::vector<cv::KeyPoint> tempObjectKeypoints;
            cv::Mat tempObjectDescriptors;
            cv::Mat tempObjectData;

            detector->detect(objectImg, tempObjectKeypoints);
            extractor->compute(objectImg, tempObjectKeypoints, tempObjectDescriptors);

            if(tempObjectDescriptors.type()!=CV_32F) {
                tempObjectDescriptors.convertTo(tempObjectData, CV_32F); // make sure it's CV_32F
            }
            else {
                tempObjectData = tempObjectDescriptors;
            }

            int tempRows = objectImg.rows;
            int tempCols = objectImg.cols;



            PiezaLogica *nuevaPieza = new PiezaLogica(pID,
                                                      pErodeNumberOfIterations,
                                                      pColorDistanceThreshold,
                                                      pR,
                                                      pG,
                                                      pB,
                                                      tempObjectKeypoints,
                                                      tempObjectData,
                                                      tempRows,
                                                      tempCols,
                                                      this);

            _ListaPiezas.append(nuevaPieza);

            //qDebug() <<  "Se ha insertado una una pieza: " << pID;

        }

    }



}

void AdministradorPiezas::actualizarPiezaLogica(int pId,
                                                int pR,
                                                int pG,
                                                int pB)
{
    actualizarPiezaLogica(pId,
                          Constants::DEFAULT_ERODE_ITERATIONS,
                          Constants::DEFAULT_COLOR_DISTANCE_THRESHOLD,
                          pR,
                          pG,
                          pB);


}

void AdministradorPiezas::actualizarPiezaLogica(int pID,
                                                int pErodeNumberOfIterations,
                                                int pColorDistanceThreshold,
                                                int pR,
                                                int pG,
                                                int pB)
{
    qDebug() << "###";
    qDebug() << "AdministradorPiezas";
    qDebug() << "actualizando pieza";
    qDebug() << "###";

    QString rutaPieza = path +
            QString::number(pID)+
            ".png";

    QFile file(rutaPieza);

    if (file.exists() == true)
    {

        //qDebug() << "Procesando cargar imagen";

        //qDebug() << "Imagen: " << rutaPieza;

        Mat objectImg = imread(rutaPieza.toAscii().data());

        if( objectImg.data)
        {

            std::vector<cv::KeyPoint> tempObjectKeypoints;
            cv::Mat tempObjectDescriptors;
            cv::Mat tempObjectData;

            detector->detect(objectImg, tempObjectKeypoints);
            extractor->compute(objectImg, tempObjectKeypoints, tempObjectDescriptors);

            if(tempObjectDescriptors.type()!=CV_32F) {
                tempObjectDescriptors.convertTo(tempObjectData, CV_32F); // make sure it's CV_32F
            }
            else {
                tempObjectData = tempObjectDescriptors;
            }

            int tempRows = objectImg.rows;
            int tempCols = objectImg.cols;


            _ListaPiezas[pID]->_ErodeNumberOfIterations = pErodeNumberOfIterations;
            _ListaPiezas[pID]->_ColorDistanceThreshold = pColorDistanceThreshold;
            _ListaPiezas[pID]->_R = pR;
            _ListaPiezas[pID]->_G = pG;
            _ListaPiezas[pID]->_B = pB;

            _ListaPiezas[pID]->_Rows = tempRows;
            _ListaPiezas[pID]->_Cols = tempCols;
            _ListaPiezas[pID]->objectKeypoints = tempObjectKeypoints;
            _ListaPiezas[pID]->objectData = tempObjectData;

            //qDebug() <<  "Se ha insertado una una pieza: " << pID;

        }

    }




}

const int AdministradorPiezas::sizeLista()
{
    return _ListaPiezas.size();
}

const PiezaLogica* AdministradorPiezas::at(int pIndex)
{
    return _ListaPiezas.at(pIndex);
}






