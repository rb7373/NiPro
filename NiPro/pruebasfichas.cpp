#include "pruebasfichas.h"
#include "ui_pruebasfichas.h"

PruebasFichas::PruebasFichas(AdministradorPiezas *pAdministradorPiezas,
                             QWidget *parent) :
    QFrame(parent),
    ui(new Ui::PruebasFichas)
{
    ui->setupUi(this);

    _AdministradorPiezas = pAdministradorPiezas;

    crearObjetos();

    iniciarParametrosCamara();

    connect(ui->pushButtonCerrar,SIGNAL(clicked()),this,SLOT(iniciarAnimacionOcultarVentana()));

    cargarFichas();

    QDir::setCurrent(QCoreApplication::applicationDirPath());
    path = QDir::currentPath()+"/fichas/pieza";

    QTimer::singleShot(0,this,SLOT(iniciarAnimacionMostrarVentana()));

}

PruebasFichas::~PruebasFichas()
{

    delete ui;

    // Disconnect camera if connected
    if(isCameraConnected)
    {
        _Controller->disconnectCamera();
    }

    //delete _Controller;

    //qDebug() << "Pruebas destruidas";

}

void PruebasFichas::iniciarAnimacionMostrarVentana()
{
    //    QParallelAnimationGroup *grupoParaleloDeAnimaciones = new QParallelAnimationGroup(this);

    //    QPropertyAnimation *propiedadTransparencia;

    //    if (QGraphicsOpacityEffect *effect =
    //            (static_cast<QGraphicsOpacityEffect*>(
    //                 this->graphicsEffect())))
    //    {
    //        propiedadTransparencia = new QPropertyAnimation(effect, "opacity");
    //        propiedadTransparencia->setStartValue(0.0);
    //        propiedadTransparencia->setEndValue(1.0);
    //        grupoParaleloDeAnimaciones->addAnimation(propiedadTransparencia);
    //    }

    //    for (int i = 0; i < grupoParaleloDeAnimaciones->animationCount(); ++i) {
    //        QPropertyAnimation *anim = qobject_cast<QPropertyAnimation *>(grupoParaleloDeAnimaciones->animationAt(i));
    //        anim->setEasingCurve(QEasingCurve::Linear);
    //        anim->setDuration(Constants::DURACION_ANIMACION_MOSTRAR_VENTANA_SETTINGS);
    //    }

    //    grupoParaleloDeAnimaciones->start();
}

void PruebasFichas::iniciarAnimacionOcultarVentana()
{
    //    QParallelAnimationGroup *grupoParaleloDeAnimaciones = new QParallelAnimationGroup(this);

    //    QPropertyAnimation *propiedadTransparencia;

    //    if (QGraphicsOpacityEffect *effect =
    //            (static_cast<QGraphicsOpacityEffect*>(
    //                 this->graphicsEffect())))
    //    {
    //        propiedadTransparencia = new QPropertyAnimation(effect, "opacity");
    //        propiedadTransparencia->setStartValue(1.0);
    //        propiedadTransparencia->setEndValue(0.0);
    //        grupoParaleloDeAnimaciones->addAnimation(propiedadTransparencia);
    //    }

    //    for (int i = 0; i < grupoParaleloDeAnimaciones->animationCount(); ++i) {
    //        QPropertyAnimation *anim = qobject_cast<QPropertyAnimation *>(grupoParaleloDeAnimaciones->animationAt(i));
    //        anim->setEasingCurve(QEasingCurve::Linear);
    //        anim->setDuration(Constants::DURACION_ANIMACION_MOSTRAR_VENTANA_SETTINGS);
    //    }

    //    grupoParaleloDeAnimaciones->start();

    //    connect(grupoParaleloDeAnimaciones,SIGNAL(finished()),this,SLOT(deleteLater()));

    deleteLater();
}

void PruebasFichas::actualizarPiezaADetectar(int pIDPieza)
{
    imageProcessingSettings.encontrarPieza = pIDPieza;
    imageProcessingFlags.encontrarPieza = true;
    imageProcessingFlags.encontrarPiezas = false;
    imageProcessingFlags.erodeOn = true;
    emit newImageProcessingFlags(imageProcessingFlags);
    emit newImageProcessingSettings(imageProcessingSettings);


}

void PruebasFichas::crearObjetos()
{

    // Create controller
    _Controller = new Controller(this);

    _BottunCameraCheck = new BotonAnimadoABoolDosEstados(this);

    _BottunCameraCheck->setFocusPolicy(Qt::NoFocus);
    _BottunCameraCheck->setFlat(true);
    _BottunCameraCheck = new BotonAnimadoABoolDosEstados(this);

    _BottunCameraCheck->setFocusPolicy(Qt::NoFocus);
    _BottunCameraCheck->setFlat(true);
    _BottunCameraCheck->setStyleSheet(Constants::TRANSPARENT_BACKGROUND);
    _BottunCameraCheck->setIconSize(QSize(Constants::SIZE_ICON_X,
                                          Constants::SIZE_ICON_Y));
    _BottunCameraCheck->setDuracionAnimacion(Constants::DURACION_ANIMACION_BOTON);
    _BottunCameraCheck->setCambioTamXY(Constants::CHANGE_SIZE_BUTTON_X,
                                       Constants::CHANGE_SIZE_BUTTON_Y);
    _BottunCameraCheck->setTamIconoXY(Constants::SIZE_ICON_X,
                                      Constants::SIZE_ICON_Y);
    _BottunCameraCheck->setCambioPosicion(Constants::CHANGE_POS_BUTTON);

    _BottunCameraCheck->setIconsPath(Constants::PATH_ICON_CHECK_CAMERA,
                                     Constants::PATH_ICON_UNCHECK_CAMERA);

    _BottunCameraCheck->setCambioDeTam(true);
    _BottunCameraCheck->setTipoInterpolacion(QEasingCurve::Linear);

    //Correction in size in order to show the button text
    _BottunCameraCheck->setGeometry(ui->labelWebcamIcon->x()+
                                    Constants::POS_BUTTON_CAMERA_CHECK_X,
                                    ui->labelWebcamIcon->y()+
                                    Constants::POS_BUTTON_CAMERA_CHECK_Y,
                                    Constants::SIZE_ICON_X+
                                    Constants::INCREASE_SIZE_20,
                                    Constants::SIZE_ICON_Y+
                                    Constants::INCREASE_SIZE_20);

    _BottunCameraCheck->setPosicionInicialXY(Constants::POS_BUTTON_CAMERA_CHECK_X,
                                             Constants::POS_BUTTON_CAMERA_CHECK_Y);

    _BottunCameraCheck->setTexto(Constants::TITLE_BUTTON_CHECK_CAMERA);
    _BottunCameraCheck->centrarTexto();

    connect(_BottunCameraCheck,SIGNAL(toggled(bool)),this,SLOT(connectToCamera(bool)));

    _LabelCamara = new FrameLabel(this);
    _LabelCamara->setStyleSheet("border-style: outset; border-width: 1px; border-radius: 10px; border-color: white;");
    _LabelCamara->setPixmap(QPixmap(":/images/backgrounds/set_0/manos_3_640x480.png"));
    _LabelCamara->setGeometry(270,70,
                              Constants::RESOLUCION_W,
                              Constants::RESOLUCION_H);

    _FramePiezas = new QFrame(this);
    _FramePiezas->setObjectName(QString::fromUtf8("frame"));
    _FramePiezas->setGeometry(QRect(0, 0, 128, 128));
    _FramePiezas->setFrameShape(QFrame::StyledPanel);
    _FramePiezas->setFrameShadow(QFrame::Raised);

    _FramePiezas->setStyleSheet("color: rgba( 255, 255, 255, 0%);border-style: outset; border-radius: 10px; border-color: rgba(255, 255, 255, 0%);");
    //_FramePiezas->setStyleSheet("color: blue ;border-style: outset; border-radius: 10px; border-color: red;");

    ui->scrollArea->setWidget(_FramePiezas);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    //ui->scrollArea->widget()->adjustSize();
    ui->scrollArea->widget()->resize(128+10,
                                     Constants::CANTIDAD_PIEZAS*138+10);

    ui->scrollArea->setWidgetResizable(false);

    //qDebug() << "Size frame Scrool 3:" << ui->scrollArea->widget()->width() << " : " << ui->scrollArea->widget()->height();




    pushButtonPiezaActual = new QPushButton(this);
    pushButtonPiezaActual->setObjectName(QString::fromUtf8("pushButtonPiezaActual"));
    pushButtonPiezaActual->setGeometry(QRect(850, 580, 85, 81));
    pushButtonPiezaActual->setCursor(QCursor(Qt::PointingHandCursor));
    pushButtonPiezaActual->setFocusPolicy(Qt::NoFocus);
    pushButtonPiezaActual->setStyleSheet(QString::fromUtf8("background-color: rgba( 255, 255, 255, 0% );"));
    QIcon iconTemp;
    iconTemp.addFile(QString::fromUtf8(":/images/icons/set_0/camera_1_96x96.png"), QSize(), QIcon::Normal, QIcon::Off);
    pushButtonPiezaActual->setIcon(iconTemp);
    pushButtonPiezaActual->setIconSize(QSize(70, 70));
    pushButtonPiezaActual->setFlat(true);

}

void PruebasFichas::cargarFichas()
{
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    QString path = QDir::currentPath()+"/fichas/pieza";

    for (int i = 0; i < Constants::CANTIDAD_PIEZAS; i++)
    {
        QString rutaPieza = path +
                QString::number(i)+
                ".png";
        QFile file(rutaPieza);

        PushButtonPiezaSimple *botonTemp = new PushButtonPiezaSimple(_FramePiezas);
        botonTemp->setFlat(true);
        botonTemp->setFocusPolicy(Qt::NoFocus);
        botonTemp->setIconSize(QSize(100,100));

        botonTemp->setGeometry(10,i*138+10,128,128);
        //botonTemp->setStyleSheet("background-color: blue; color: rgba( 255, 255, 255, 0%);border-style: outset; border-radius: 10px; border-color: red; padding: 10;");
        botonTemp->setStyleSheet("border-color: rgb(0,95,114,255); border-top-color: rgb(0,95,114,255);");

        if (file.exists() == true)
        {
            QPixmap tempPixmap(rutaPieza);
            tempPixmap = tempPixmap.scaled(126,126,Qt::KeepAspectRatio);
            botonTemp->setIcon(QIcon(tempPixmap));


        }
        else
        {
            QPixmap tempPixmap(":/images/icons/set_0/cuidado.png");
            tempPixmap = tempPixmap.scaled(126,126,Qt::KeepAspectRatio);
            botonTemp->setIcon(QIcon(tempPixmap));
        }


        //botonTemp->move(0, i*133+10);

        //botonTemp->setStyleSheet("color: green;border-style: outset; border-radius: 10px; border-color: yellow;");
        //pieza->setStyleSheet("color: blue;border-style: outset; border-radius: 10px; border-color: red;");

        botonTemp->setID(i);
        connect(botonTemp,SIGNAL(actualizar(int)),this,SLOT(actualizarPiezaADetectar(int)));
        _ListaPiezas << botonTemp;
    }
}

//////////////////////////
//CAMARA
//////////////////////////

void PruebasFichas::iniciarParametrosCamara()
{
    //CAMARA

    // Initialize flag
    isCameraConnected=false;

    //CAMARA
}

void PruebasFichas::connectToCamera(bool pToggled)
{

    if (pToggled == true && isCameraConnected == false)
    {
        //qDebug("Activando camara");


        deviceNumber=getDeviceNumber();


        // Store image buffer size in local variable
        imageBufferSize=getImageBufferSize();

        // Connect to camera

        isCameraConnected = _Controller->connectToCamera(deviceNumber,imageBufferSize,
                                                         getDropFrameCheckBoxState(),
                                                         getCaptureThreadPrio(),
                                                         getProcessingThreadPrio());
        if(isCameraConnected)
        {
            connectToCameraAux();
        }
        // Display error dialog if camera connection is unsuccessful
        else
        {
            QMessageBox::warning(0,"ERROR:","No se pudo conectar la camara");
        }
    }
    else
    {
        //qDebug("Desactivando camara");
        if(isCameraConnected == true)
        {
            disconnectCamera();
        }
    }

} // connectToCamera()

void PruebasFichas::connectToCameraAux()
{
    _Controller->processingThread->_AdministradorPiezas = _AdministradorPiezas;

    // Create connection between processing thread (emitter)
    // and GUI thread (receiver/listener)
    connect(_Controller->processingThread,SIGNAL(newFrame(QImage)),this,SLOT(updateFrame(QImage)));

    connect(_Controller->processingThread,SIGNAL(nuevaPieza(float,float,float,float,int)),
            this,SLOT(mostrarNuevaPieza(float,float,float,float,int)));


    connect(_Controller->processingThread,SIGNAL(piezaActual(int)),
            this,SLOT(actualizarPiezaEnProcesamiento(int)));



    // Create connections (3) between GUI thread (emitter) and processing thread (receiver/listener)
    connect(this,SIGNAL(newImageProcessingSettings(struct ImageProcessingSettings)),_Controller->processingThread,SLOT(updateImageProcessingSettings(struct ImageProcessingSettings)));
    connect(this,SIGNAL(newImageProcessingFlags(struct ImageProcessingFlags)),_Controller->processingThread,SLOT(updateImageProcessingFlags(struct ImageProcessingFlags)));

    // Initialize data structures
    initializeImageProcessingFlagsStructure();
    updateStoredSettings();

    // Set data to defaults in processingThread
    emit newImageProcessingFlags(imageProcessingFlags);

    // Enable/disable appropriate GUI items
    //Modificar

    // Get input stream properties
    sourceWidth=_Controller->captureThread->getInputSourceWidth();
    sourceHeight=_Controller->captureThread->getInputSourceHeight();

    //qDebug() << "Ancho: " << sourceWidth;
    //qDebug() << "Ancho: " << sourceHeight;

    // Set text in labels in main window
    //Modiciar
}


void PruebasFichas::iniciarConexionesCamara()
{
    //Controlador
    connect(_Controller,SIGNAL(camDisconnected()),this,SLOT(camDisconnected()));

} // signalSlotsInit()




void PruebasFichas::updateFrame(const QImage &frame)
{
    // Display frame in main window
    _LabelCamara->setPixmap(QPixmap::fromImage(frame));

    ////qDebug("Actualizando label de la camara");

} // updateFrame()

void PruebasFichas::reestablecerFondoLabelCamara()
{
    _LabelCamara->setPixmap(QPixmap(":/images/backgrounds/set_0/manos_3_640x480.png"));

}

void PruebasFichas::loadImage(QString pPath)
{
    //Imagen de OpenCV
    imageTemp = cv::imread(pPath.toAscii().data(), CV_LOAD_IMAGE_COLOR);
    //Si la imagen se puede cargar
    if (imageTemp.data)
    {

    }

}

void PruebasFichas::updateStoredSettings()
{
    resetAllToDefaults();
    emit newImageProcessingSettings(imageProcessingSettings);
} // updateStoredSettings()


void PruebasFichas::resetAllToDefaults()
{
    // Smooth

    imageProcessingSettings.smoothType = Constants::DEFAULT_SMOOTH_TYPE;
    imageProcessingSettings.smoothParam1 = Constants::DEFAULT_SMOOTH_PARAM_1;
    imageProcessingSettings.smoothParam2 = Constants::DEFAULT_SMOOTH_PARAM_2;
    imageProcessingSettings.smoothParam3 = Constants::DEFAULT_SMOOTH_PARAM_3;
    imageProcessingSettings.smoothParam4 = Constants::DEFAULT_SMOOTH_PARAM_4;
    // Dilate
    imageProcessingSettings.dilateNumberOfIterations = Constants::DEFAULT_DILATE_ITERATIONS;
    // Erode
    imageProcessingSettings.erodeNumberOfIterations = Constants::DEFAULT_ERODE_ITERATIONS;
    // Flip
    imageProcessingSettings.flipCode = Constants::DEFAULT_FLIP_CODE;
    // Canny
    imageProcessingSettings.cannyThreshold1 = Constants::DEFAULT_CANNY_THRESHOLD_1;
    imageProcessingSettings.cannyThreshold2 = Constants::DEFAULT_CANNY_THRESHOLD_2;
    imageProcessingSettings.cannyApertureSize = Constants::DEFAULT_CANNY_APERTURE_SIZE;
    imageProcessingSettings.cannyL2gradient = Constants::DEFAULT_CANNY_L2GRADIENT;
    imageProcessingSettings.encontrarPieza = Constants::DEFAULT_IMAGE_FIND;
    imageProcessingSettings.colorDistanceThreshold = Constants::DEFAULT_COLOR_DISTANCE_THRESHOLD;

} // resetAllToDefaults()


void PruebasFichas::disconnectCamera()
{
    // Check if camera is connected
    if(_Controller->captureThread->isCameraConnected())
    {
        // Disconnect connections

        disconnect(_Controller->processingThread,SIGNAL(newFrame(QImage)),0,0);
        disconnect(_Controller->processingThread,SIGNAL(nuevaPieza(float,float,float,float,int)),
                   0,0);

        disconnect(this,SIGNAL(newImageProcessingFlags(struct ImageProcessingFlags)),_Controller->processingThread,SLOT(updateImageProcessingFlags(struct ImageProcessingFlags)));
        disconnect(this,SIGNAL(newImageProcessingSettings(struct ImageProcessingSettings)),_Controller->processingThread,SLOT(updateImageProcessingSettings(struct ImageProcessingSettings)));

        // Reset flag
        isCameraConnected=false;

        // Disconnect camera
        _Controller->disconnectCamera();

    }
    // Display error dialog
    else
        QMessageBox::warning(0,"ERROR:","La camara ya se encuentra conectada");
} // disconnectCamera()

void PruebasFichas::clearImageBuffer()
{
    _Controller->clearImageBuffer();
} // clearImageBuffer()

void PruebasFichas::initializeImageProcessingFlagsStructure()
{

    imageProcessingFlags.grayscaleOn = Constants::DEFAULT_GRAYSCALE;
    imageProcessingFlags.smoothOn = Constants::DEFAULT_SMOOTH;
    imageProcessingFlags.dilateOn = Constants::DEFAULT_DILATE;
    imageProcessingFlags.erodeOn = Constants::DEFAULT_ERODE;
    imageProcessingFlags.flipOn = Constants::DEFAULT_FLIP;
    imageProcessingFlags.cannyOn = Constants::DEFAULT_CANNY;
    imageProcessingFlags.encontrarPiezas = Constants::DEFAULT_FIND_PIECES;
    imageProcessingFlags.encontrarPieza = Constants::DEFAULT_FIND_PIECE;


} // initializeImageProcessingFlagsStructure()

void PruebasFichas::camDisconnected()
{

    //qDebug() <<"***SE confirma desconexion";
    isCameraConnected = false;


} // camDisconnected()

///////////////////////////
///BEGINNIG: GETS
///////////////////////////

int PruebasFichas::getDeviceNumber()
{

    return Constants::DEFAULT_CAMERA_DEV_NO;

} // getDeviceNumber()

int PruebasFichas::getImageBufferSize()
{

    return Constants::DEFAULT_IMAGE_BUFFER_SIZE;

} // getImageBufferSize()

bool PruebasFichas::getDropFrameCheckBoxState()
{

    return Constants::DEFAULT_DROP_FRAMES;

} // getDropFrameCheckBoxState()


int PruebasFichas::getCaptureThreadPrio()
{
    return Constants::DEFAULT_CAP_THREAD_PRIO;

} // getCaptureThreadPrio()

int PruebasFichas::getProcessingThreadPrio()
{
    return Constants::DEFAULT_PROC_THREAD_PRIO;
} // getProcessingThreadPrio()


///////////////////////////
///END: GETS
///////////////////////////


///////////////////////////
///BEGINNIG: SETS
///////////////////////////

void PruebasFichas::setImageProcessingSettings()
{


} // setImageProcessingSettings()

void PruebasFichas::setGrayscale(bool input)
{

} // setGrayscale()

void PruebasFichas::setSmooth(bool input)
{

} // setSmooth()

void PruebasFichas::setDilate(bool input)
{

} // setDilate()

void PruebasFichas::setErode(bool input)
{

} // setErode()

void PruebasFichas::setFlip(bool input)
{

} // setFlip()

void PruebasFichas::setCanny(bool input)
{

} // setCanny()
///////////////////////////
///END: SETS
///////////////////////////


void PruebasFichas::on_pushButtonDistanceThreshold_released()
{
    //    //qDebug("***Cambiando find");
    //    imageProcessingFlags.encontrarPieza = !imageProcessingFlags.encontrarPiezas;

    //    emit newImageProcessingFlags(imageProcessingFlags);

}

void PruebasFichas::on_horizontalSliderDistanceThreshold_valueChanged(int value)
{
    imageProcessingSettings.colorDistanceThreshold = value;
    //qDebug() << "Nuevo valor de umbral: " << value;
    emit newImageProcessingSettings(imageProcessingSettings);
}

void PruebasFichas::on_pushButtonErodeNumber_released()
{
    //    //qDebug("***Cambiando erosion");
    //    imageProcessingFlags.erodeOn = !imageProcessingFlags.erodeOn;
    //    emit newImageProcessingFlags(imageProcessingFlags);
}

void PruebasFichas::on_horizontalSliderErodeNumber_valueChanged(int value)
{
    imageProcessingSettings.erodeNumberOfIterations = value;
    //qDebug() << "Nuevo valor erosion"<< value;
    emit newImageProcessingSettings(imageProcessingSettings);
}

void PruebasFichas::mostrarNuevaPieza(float pX,
                                      float pY,
                                      float pWidth,
                                      float pHeight,
                                      int pID)
{


}

void PruebasFichas::actualizarPiezaEnProcesamiento(int pID)
{
    QString rutaPieza = path +
            QString::number(pID)+
            ".png";

    QFile file(rutaPieza);

    if (file.exists() == true)
    {
        QPixmap tempPixmap(rutaPieza);
        tempPixmap = tempPixmap.scaled(70,70,Qt::KeepAspectRatio);
        pushButtonPiezaActual->setIcon(QIcon(tempPixmap));
    }
}

//Test

//Original

/*

void PruebasFichas::connectToCamera(bool pToggled)
{

    if (pToggled == true && isCameraConnected == false)
    {
        //qDebug("Activando camara");


        deviceNumber=getDeviceNumber();


        // Store image buffer size in local variable
        imageBufferSize=getImageBufferSize();

        // Connect to camera

        isCameraConnected = _Controller->connectToCamera(deviceNumber,imageBufferSize,
                                                         getDropFrameCheckBoxState(),
                                                         getCaptureThreadPrio(),
                                                         getProcessingThreadPrio());
        if(isCameraConnected)
        {
            connectToCameraAux();
        }
        // Display error dialog if camera connection is unsuccessful
        else
        {
            QMessageBox::warning(0,"ERROR:","No se pudo conectar la camara");
        }
    }
    else
    {
        //qDebug("Desactivando camara");
        if(isCameraConnected == true)
        {
            disconnectCamera();
        }
    }

} // connectToCamera()

*/

/*
  Test Tipos de camaras

void PruebasFichas::connectToCamera(bool pToggled)
{

    if (pToggled == true && isCameraConnected == false)
    {
        //qDebug("Activando camara");
                bool ok;
                QInputDialog tempQInputDialog;
                tempQInputDialog.setWindowIcon(QIcon(":/icon/buttons/images/question_1_24x24.png"));
                QString numberCam = tempQInputDialog.getText(0, tr("Importante!!!"),
                                                             tr("Digite el numero del dispositivo de la camara (En caso de no saber mantener -1)"), QLineEdit::Normal,
                                                             "-1", &ok);
                if( ok && !numberCam.isEmpty() )
                {
                   int numero = numberCam.toInt(&ok);
                    if (ok)
                    {
                        // Store device number in local variable
                        deviceNumber=numero;
                    }
                    else
                    {

        deviceNumber=getDeviceNumber();
                    }

        // Store image buffer size in local variable
        imageBufferSize=getImageBufferSize();

        // Connect to camera

        isCameraConnected = _Controller->connectToCamera(deviceNumber,imageBufferSize,
                                                         getDropFrameCheckBoxState(),
                                                         getCaptureThreadPrio(),
                                                         getProcessingThreadPrio());
        if(isCameraConnected)
        {
            connectToCameraAux();
        }
        // Display error dialog if camera connection is unsuccessful
        else
        {
            QMessageBox::warning(0,"ERROR:","No se pudo conectar la camara");
        }
    }
    }
    else
    {
        //qDebug("Desactivando camara");
        if(isCameraConnected == true)
        {
            disconnectCamera();
        }
    }

} // connectToCamera()
  */
