#include "subprocesadorimagenes.h"

SubProcesadorImagenes::SubProcesadorImagenes()
{
    histSize = 256;
    range[0] = 0;
    range[1] = 256;
    histRange = range;

    _R = 0;
    _G = 0;
    _B = 0;

    uniform = true;
    accumulate = false;

}

SubProcesadorImagenes::~SubProcesadorImagenes()
{
    qDebug() << "***";
    qDebug() << "Destruyendo subprocedor de imagenes";
    qDebug() << "***";
}

bool SubProcesadorImagenes::obtenerColoresPrincipales(int pID)
{
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    QString path = QDir::currentPath()+"/fichas/pieza";

    QString rutaPieza = path +
            QString::number(pID)+
            ".png";
    QFile file(rutaPieza);

    if (file.exists() == true)
    {
        Mat src;
        /// Load image
        src = cv::imread(rutaPieza.toAscii().data());
        if( !src.data )
        {
            return false;
        }

        /// Separate the image in 3 places ( B, G and R )
        vector<Mat> bgr_planes;
        split( src, bgr_planes );

        Mat b_hist, g_hist, r_hist;

        /// Compute the histograms:
        calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
        calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
        calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

        double maxVal = 0;
        Point maxPos;

        qDebug() << "Resultados de procesamiento imagen personalizada:";

        minMaxLoc(r_hist, 0, &maxVal, 0, &maxPos);
        _R = maxPos.y;
        qDebug() << "R: " << maxVal <<"Pos: " << maxPos.x<<", " << _R;

        minMaxLoc(g_hist, 0, &maxVal, 0, &maxPos);
        _G = maxPos.y;
        qDebug() << "G: " << maxVal <<"Pos: " << maxPos.x<<", " << _G;

        minMaxLoc(b_hist, 0, &maxVal, 0, &maxPos);
        _B = maxPos.y;
        qDebug() << "B: " << maxVal <<"Pos: " << maxPos.x<<", " << _B;

    }

    return true;

}

int SubProcesadorImagenes::getColorR()
{
    return _R;
}

int SubProcesadorImagenes::getColorG()
{
    return _G;
}

int SubProcesadorImagenes::getColorB()
{
    return _B;
}




//Respaldos
//else
//{
//    QString fileName = QFileDialog::getOpenFileName(0,
//     "Open Image", ".", "Image Files (*.png *.jpg *.bmp)");

//    //qDebug() << "Ruta:" << fileName;
//    imageTemp= cv::imread(fileName.toAscii().data());

//    if (imageTemp.data)
//    {
//        cv::namedWindow("Original Image");
//        cv::imshow("Original Image", imageTemp);
//    }

//}

//qDebug() << "Ruta:" << rutaPieza;
//            // Load color image
//            ColorHistogram hc;
//            cv::Mat color= cv::imread("../waves.jpg");
//            cv::Mat result1;
//            color= hc.colorReduce(color,32);
//            cv::namedWindow("Color Image");
//            cv::imshow("Color Image",color);

//            imageROI= color(cv::Rect(0,0,165,75)); // blue sky area

//            // Get 3D color histogram
//            cv::MatND shist= hc.getHistogram(imageROI);
//            // Histograms with SparseMat does not work with OpenCV2.1
//            // cv::SparseMat shist= hc.getSparseHistogram(imageROI);

//            finder.setHistogram(shist);
//            finder.setThreshold(0.05f);

//            // Get back-projection of color histogram
//            result1= finder.find(color);

//            cv::namedWindow("Color Backproject Result");
//            cv::imshow("Color Backproject Result",result1);




//            //Imagen de OpenCV
//            imageTemp = cv::imread(rutaPieza.toAscii().data());

//            //Si la imagen se puede cargar
//            if (imageTemp.data)
//            {


//                //qDebug() << "Mostrando ventana OPENCV " << i;
////                cv::namedWindow("Color Image");
////                cv::imshow("Color Image",imageTemp);


//            }
//        }
//        else
//        {

//        }
//}
