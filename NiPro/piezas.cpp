#include "piezas.h"
#include "ui_piezas.h"

Piezas::Piezas(AdministradorPiezas *pAdministradorPiezas,
               QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Piezas)
{
    ui->setupUi(this);

    _AdministradorPiezas = pAdministradorPiezas;

    crearObjetos();

    cargarPiezas();

    //////////////////////////
    //CAMARA
    //////////////////////////

    iniciarParametrosCamara();
    iniciarConexionesCamara();

    //////////////////////////
    //CAMARA
    //////////////////////////

    connect(ui->pushButtonCerrar,SIGNAL(clicked()),this,SLOT(iniciarAnimacionOcultarVentana()));

    ui->pushButtonAnterior->hide();

    ui->pushButtonAnterior->setStyleSheet(Constants::TRANSPARENT_BACKGROUND);
    ui->pushButtonCerrar->setStyleSheet(Constants::TRANSPARENT_BACKGROUND);

//    QGraphicsOpacityEffect *effect;
//    effect = new QGraphicsOpacityEffect(this);
//    effect->setOpacity(0.0);
//    this->setGraphicsEffect(effect);

    QTimer::singleShot(0,this,SLOT(iniciarAnimacionMostrarVentana()));

//    setMinimumSize();
//    set





}

Piezas::~Piezas()
{
    delete ui;

    // Disconnect camera if connected
    if(isCameraConnected)
    {
        _Controller->disconnectCamera();
    }

    //qDebug() << "Piezas destruidas";
}

void Piezas::iniciarAnimacionMostrarVentana()
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

void Piezas::iniciarAnimacionOcultarVentana()
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

void Piezas::crearObjetos()
{

    // Create controller
    _Controller = new Controller(this);

    _FramePiezas = new QFrame(this);
    _FramePiezas->setObjectName(QString::fromUtf8("frame"));
    _FramePiezas->setGeometry(QRect(0, 0, 840, 512));
    _FramePiezas->setFrameShape(QFrame::StyledPanel);
    _FramePiezas->setFrameShadow(QFrame::Raised);

    _FramePiezas->setStyleSheet("color: rgba( 255, 255, 255, 0%);border-style: outset; border-radius: 10px; border-color: rgba(255, 255, 255, 0%);");
    _FramePiezas->resize(_FramePiezas->width(), Constants::CANTIDAD_PIEZAS*266);

    ui->scrollArea->setWidget(_FramePiezas);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    //ui->scrollArea->widget()->adjustSize();
    ui->scrollArea->widget()->resize(Constants::TAM_X_SCROll_AREA,
                                     Constants::CANTIDAD_PIEZAS*266+10);

    ui->scrollArea->setWidgetResizable(false);

    //qDebug() << "Size frame Scrool 3:" << ui->scrollArea->widget()->width() << " : " << ui->scrollArea->widget()->height();



    _LabelCamara = new FrameLabel(this);
    QGraphicsOpacityEffect *effect;
    effect = new QGraphicsOpacityEffect(_LabelCamara);
    effect->setOpacity(0.0);
    _LabelCamara->setGraphicsEffect(effect);
    //_LabelCamara->setStyleSheet("border-style: outset; border-width: 1px; border-radius: 10px; border-color: white;");
    _LabelCamara->setPixmap(QPixmap(":/images/backgrounds/set_0/manos_3_640x480.png"));
    _LabelCamara->setGeometry(270,70,Constants::RESOLUCION_W,
                              Constants::RESOLUCION_H);
    _LabelCamara->hide();

    _BottunTakePhoto = new BotonAnimadoA(this);
    _BottunTakePhoto->setFocusPolicy(Qt::NoFocus);
    _BottunTakePhoto->setFlat(true);
    _BottunTakePhoto->setStyleSheet(Constants::TRANSPARENT_BACKGROUND+
                                    Constants::TITLE_BUTTON_COMIC);

    _BottunTakePhoto->setIconSize(QSize(Constants::SIZE_ICON_X,
                                        Constants::SIZE_ICON_Y));
    _BottunTakePhoto->setDuracionAnimacion(Constants::DURACION_ANIMACION_BOTON);
    _BottunTakePhoto->setCambioTamXY(Constants::CHANGE_SIZE_BUTTON_X,
                                     Constants::CHANGE_SIZE_BUTTON_Y);
    _BottunTakePhoto->setIcon(QIcon(Constants::PATH_ICON_CAMERA));

    _BottunTakePhoto->setTamIconoXY(Constants::SIZE_ICON_X,
                                    Constants::SIZE_ICON_Y);
    _BottunTakePhoto->setCambioPosicion(Constants::CHANGE_POS_BUTTON);

    _BottunTakePhoto->setCambioDeTam(true);
    _BottunTakePhoto->setCambioDePos(true);
    _BottunTakePhoto->setCambioDeTransp(true);
    _BottunTakePhoto->setTipoInterpolacion(QEasingCurve::OutBounce);

    //Correction in size in order to show the button text
    _BottunTakePhoto->setGeometry(170,
                                  250,
                                  Constants::SIZE_ICON_X+
                                  Constants::INCREASE_SIZE_20,
                                  Constants::SIZE_ICON_Y+
                                  Constants::INCREASE_SIZE_20);

    _BottunTakePhoto->setPosicionInicialXY(170,
                                           250);

    _BottunTakePhoto->setTexto("<font color='white'>Tomar</font>");
    _BottunTakePhoto->centrarTexto();

    _BottunTakePhoto->hide();
    _BottunSave = new BotonAnimadoA(this);
    _BottunSave->setFocusPolicy(Qt::NoFocus);
    _BottunSave->setFlat(true);
    _BottunSave->setStyleSheet(Constants::TRANSPARENT_BACKGROUND+
                               Constants::TITLE_BUTTON_COMIC);

    _BottunSave->setIconSize(QSize(Constants::SIZE_ICON_X,
                                   Constants::SIZE_ICON_Y));
    _BottunSave->setDuracionAnimacion(Constants::DURACION_ANIMACION_BOTON);
    _BottunSave->setCambioTamXY(Constants::CHANGE_SIZE_BUTTON_X,
                                Constants::CHANGE_SIZE_BUTTON_Y);
    _BottunSave->setIcon(QIcon(Constants::PATH_ICON_CHECK_CAMERA));

    _BottunSave->setTamIconoXY(Constants::SIZE_ICON_X,
                               Constants::SIZE_ICON_Y);
    _BottunSave->setCambioPosicion(Constants::CHANGE_POS_BUTTON);

    _BottunSave->setCambioDeTam(true);
    _BottunSave->setCambioDePos(true);
    _BottunSave->setCambioDeTransp(true);
    _BottunSave->setTipoInterpolacion(QEasingCurve::OutBounce);

    //Correction in size in order to show the button text
    _BottunSave->setGeometry(_BottunTakePhoto->pos().x(),
                             _BottunTakePhoto->pos().y()+200,
                             Constants::SIZE_ICON_X+
                             Constants::INCREASE_SIZE_20,
                             Constants::SIZE_ICON_Y+
                             Constants::INCREASE_SIZE_20);

    _BottunSave->setPosicionInicialXY(_BottunTakePhoto->pos().x(),
                                      _BottunTakePhoto->pos().y()+200);

    _BottunSave->setTexto("<font color='white'>Guardar</font>");
    _BottunSave->centrarTexto();

    _BottunSave->hide();

    _MarcoLabelFoto = new QWidget(this);
    _MarcoLabelFoto->hide();
    _LabelPhoto = new QLabel(_MarcoLabelFoto);
    _MarcoLabelFoto->setGeometry(_BottunTakePhoto->pos().x()+2,
                                 _BottunTakePhoto->pos().y()+100,
                                 84,
                                 64);



    _LabelPhoto->setGeometry(1,
                             2,
                             80,
                             60);

    _MarcoLabelFoto->setStyleSheet("background-color:rgb(0,95,114,255); border-style: ridge; border-width: 1px; border-radius: 5px; border-color:rgb(0,95,114,255);");
    //_MarcoLabelFoto->setStyleSheet("background-color:rgb(89,41,93,193); border-style: ridge; border-width: 1px; border-radius: 5px; border-color: rgb(89,41,93,193);");
    _LabelPhoto->setStyleSheet("border-radius: 10px; border-color: rgba(255, 255, 255, 0%);");

    _LabelPhoto->setScaledContents(true);
    connect(_BottunTakePhoto,SIGNAL(clicked()),this,SLOT(takeAPhoto()));
    connect(_BottunSave,SIGNAL(clicked()),this,SLOT(guardarImagen()));
    connect(ui->pushButtonAnterior,SIGNAL(clicked()),this,SLOT(mostrarPiezas()));

    _LabelCoordenadas = new QLabel(this);
    _LabelCoordenadas->setStyleSheet("background-color: rgba( 255, 255, 255, 0% );\ncolor:white;\nfont: 75 12pt 'Comic Sans MS';");
    _LabelCoordenadas->setGeometry(820,590,131,51);


}

void Piezas::cambiarPieza(int pID)
{
    //qDebug() << "ID: " << pID;

    _IDPiezaActual = pID;

    reducirScrollArea();

}

void Piezas::iniciarCamara()
{

    //qDebug() << "Iniciando camara";
    _BottunTakePhoto->show();
    _LabelPhoto->show();
    _LabelPhoto->setPixmap(0);
    _MarcoLabelFoto->show();
    ui->pushButtonAnterior->show();

    iniciarParametrosCamara();
    connectToCamera();

}

//////////////////////////
//CAMARA
//////////////////////////

void Piezas::iniciarParametrosCamara()
{
    //CAMARA

    // Initialize flag
    isCameraConnected=false;

    //bool
    isNewImagenReady = false;

    // Initialize data structures
    initializeTaskDataStructure();

    //CAMARA
}


void Piezas::iniciarConexionesCamara()
{
    //Controlador
    connect(_Controller,SIGNAL(camDisconnected()),this,SLOT(camDisconnected()));

    //Bottuns
    connect(_LabelCamara, SIGNAL(onMouseMoveEvent()), this, SLOT(updateMouseCursorPosLabel()));


} // signalSlotsInit()

void Piezas::connectToCamera()
{
    if (isCameraConnected == false)
    {
        //qDebug("Activando camara");
        //        bool ok;
        //        QInputDialog tempQInputDialog;
        //        tempQInputDialog.setWindowIcon(QIcon(":/icon/buttons/images/question_1_24x24.png"));
        //        QString numberCam = tempQInputDialog.getText(0, tr("Importante!!!"),
        //                                                     tr("Digite el numero del dispositivo de la camara (En caso de no saber mantener -1)"), QLineEdit::Normal,
        //                                                     "-1", &ok);
        //        if( ok && !numberCam.isEmpty() )
        //        {
        //            int numero = numberCam.toInt(&ok);
        //            if (ok)
        //            {
        //                // Store device number in local variable
        //                deviceNumber=numero;
        //            }
        //            else
        //            {

        deviceNumber=getDeviceNumber();
        //}

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
    //}
    else
    {
        //qDebug("Desactivando camara");
        if(isCameraConnected == true)
        {
            disconnectCamera();
        }
    }

} // connectToCamera()

void Piezas::connectToCameraAux()
{
    //Interesante
    _Controller->processingThread->_AdministradorPiezas = _AdministradorPiezas;

    //Create connection between frameLabel (emitter) and
    //GUI thread (receiver/listener)
    connect(this->_LabelCamara,SIGNAL(newMouseData(struct MouseData)),this,SLOT(newMouseData(struct MouseData)));

    // Create connection between processing thread (emitter)
    // and GUI thread (receiver/listener)
    connect(_Controller->processingThread,SIGNAL(newFrame(QImage)),this,SLOT(updateFrame(QImage)));


    // Create connections (3) between GUI thread (emitter) and processing thread (receiver/listener)
    connect(this,SIGNAL(newImageProcessingSettings(struct ImageProcessingSettings)),_Controller->processingThread,SLOT(updateImageProcessingSettings(struct ImageProcessingSettings)));
    connect(this,SIGNAL(newImageProcessingFlags(struct ImageProcessingFlags)),_Controller->processingThread,SLOT(updateImageProcessingFlags(struct ImageProcessingFlags)));
    connect(this,SIGNAL(newTaskData(struct TaskData)),_Controller->processingThread,SLOT(updateTaskData(struct TaskData)));

    // Initialize data structures
    initializeImageProcessingFlagsStructure();
    initializeTaskDataStructure();
    updateStoredSettings();

    // Set data to defaults in processingThread
    emit newImageProcessingFlags(imageProcessingFlags);
    emit newTaskData(taskData);


    // Enable/disable appropriate GUI items
    //Modificar

    // Get input stream properties
    sourceWidth=_Controller->captureThread->getInputSourceWidth();
    sourceHeight=_Controller->captureThread->getInputSourceHeight();



    // Set text in labels in main window
    //Modiciar
}

void Piezas::updateFrame(const QImage &frame)
{
    // Display frame in main window

    ////qDebug() << "W:" << frame.width() << "H: " << frame.height();
    ////qDebug() << "W:" << _LabelCamara->width() << "H: " << _LabelCamara->height();
    _LabelCamara->setPixmap(QPixmap::fromImage(frame));
    ////qDebug("Actualizando label de la camara");

} // updateFrame()

void Piezas::reestablecerFondoLabelCamara()
{
    _LabelCamara->setPixmap(QPixmap(":/images/backgrounds/set_0/manos_3_640x480.png"));

}

void Piezas::takeAPhoto()
{
    //qDebug("-------------Tomando foto------------");
    if (isCameraConnected == true)
    {
        _PixmapSave = _LabelCamara->pixmap()->copy();
        QPixmap pixmapTem = _LabelCamara->pixmap()->scaled(80,60,Qt::KeepAspectRatio);
        _LabelPhoto->setPixmap(pixmapTem);
        _LabelPhoto->adjustSize();
        _LabelPhoto->move((_LabelPhoto->parentWidget()->width()-
                           _LabelPhoto->width())/2,
                          (_LabelPhoto->parentWidget()->height()-
                           _LabelPhoto->height())/2);
        isNewImagenReady = true;
        _BottunSave->show();

    }
    else
    {
        //qDebug("-------------Camara desconectada------------");
    }
} // takeAPhoto()


void Piezas::loadImage(QString pPath)
{
    //Imagen de OpenCV
    imageTemp = cv::imread(pPath.toAscii().data(), CV_LOAD_IMAGE_COLOR);
    //Si la imagen se puede cargar
    if (imageTemp.data)
    {

    }

}

void Piezas::updateStoredSettings()
{
    resetAllToDefaults();
    emit newImageProcessingSettings(imageProcessingSettings);
} // updateStoredSettings()

void Piezas::resetAllToDefaults()
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

void Piezas::disconnectCamera()
{
    // Check if camera is connected
    if(_Controller->captureThread->isCameraConnected())
    {
        // Disconnect connections
        disconnect(this->_LabelCamara,SIGNAL(newMouseData(struct MouseData)),this,SLOT(newMouseData(struct MouseData)));
        disconnect(_Controller->processingThread,SIGNAL(newFrame(QImage)),0,0);
        disconnect(_Controller->processingThread,SIGNAL(nuevaPieza(int,int,int,int,int)),
                0,0);
        disconnect(this,SIGNAL(newImageProcessingFlags(struct ImageProcessingFlags)),_Controller->processingThread,SLOT(updateImageProcessingFlags(struct ImageProcessingFlags)));
        disconnect(this,SIGNAL(newImageProcessingSettings(struct ImageProcessingSettings)),_Controller->processingThread,SLOT(updateImageProcessingSettings(struct ImageProcessingSettings)));
        disconnect(this,SIGNAL(newTaskData(struct TaskData)),_Controller->processingThread,SLOT(updateTaskData(struct TaskData)));

        // Reset flag
        isCameraConnected=false;

        // Disconnect camera
        _Controller->disconnectCamera();

    }
    // Display error dialog
    else
        QMessageBox::warning(0,"ERROR:","La camara ya se encuentra conectada");
} // disconnectCamera()

void Piezas::about()
{

} // about()

void Piezas::clearImageBuffer()
{
    _Controller->clearImageBuffer();
} // clearImageBuffer()








void Piezas::updateMouseCursorPosLabel()
{

    QString posCursor = QString(" [")+QString::number(_LabelCamara->getMouseCursorPos().x()-(Constants::RESOLUCION_W-_Controller->processingThread->getCurrentROI().width)/2)+
            QString(",")+QString::number(_LabelCamara->getMouseCursorPos().y()-(Constants::RESOLUCION_H-_Controller->processingThread->getCurrentROI().height)/2)+
            QString("]");



    // Show ROI-adjusted cursor position if camera is connected
    if(isCameraConnected)
    {
        posCursor = QString("(")+QString::number(_LabelCamara->getMouseCursorPos().x())+
                QString(",")+QString::number(_LabelCamara->getMouseCursorPos().y())+
                QString(")");
    }

    _LabelCoordenadas->setText(posCursor);



} // updateMouseCursorPosLabel()

//void Piezas::newMouseData(struct MouseData mouseData)
//{
//    // Local variables
//    int x_temp, y_temp, width_temp, height_temp;
//    // Set ROI
//    if(mouseData.leftButtonRelease)
//    {

//        // Copy box dimensions from mouseData to taskData
//        taskData.selectionBox.setX(mouseData.selectionBox.x()-((_LabelCamara->width()-_Controller->captureThread->getInputSourceWidth()))/2);
//        taskData.selectionBox.setY(mouseData.selectionBox.y()-((_LabelCamara->height()-_Controller->captureThread->getInputSourceHeight()))/2);

//        //                        taskData.selectionBox.setX(_FrameLabel->width()- mouseData.selectionBox.x());
//        //                        taskData.selectionBox.setY(mouseData.selectionBox.y());

//        taskData.selectionBox.setX(_LabelCamara->width()- mouseData.selectionBox.x() - mouseData.selectionBox.width());
//        taskData.selectionBox.setY(mouseData.selectionBox.y());



//        taskData.selectionBox.setWidth(mouseData.selectionBox.width());
//        taskData.selectionBox.setHeight(mouseData.selectionBox.height());
//        // Check if selection box has NON-ZERO dimensions
//        if((taskData.selectionBox.width()!=0)&&((taskData.selectionBox.height())!=0))
//        {
//            // Selection box can also be drawn from bottom-right to top-left corner
//            if(taskData.selectionBox.width()<0)
//            {
//                x_temp=taskData.selectionBox.x();
//                width_temp=taskData.selectionBox.width();
//                taskData.selectionBox.setX(x_temp+taskData.selectionBox.width());
//                taskData.selectionBox.setWidth(width_temp*-1);
//            }
//            if(taskData.selectionBox.height()<0)
//            {
//                y_temp=taskData.selectionBox.y();
//                height_temp=taskData.selectionBox.height();
//                taskData.selectionBox.setY(y_temp+taskData.selectionBox.height());
//                taskData.selectionBox.setHeight(height_temp*-1);
//            }
//            // Check if selection box is not outside window
//            if((taskData.selectionBox.x()<0)||(taskData.selectionBox.y()<0)||
//                    ((taskData.selectionBox.x()+taskData.selectionBox.width())>sourceWidth)||
//                    ((taskData.selectionBox.y()+taskData.selectionBox.height())>sourceHeight))
//            {
//                // Display error message
//                QMessageBox::warning(0,"ERROR:","La selección está fuera del rango");
//            }
//            else
//            {
//                // Set setROIFlag to TRUE
//                taskData.setROIFlag=true;
//                // Update task data in processingThread
//                emit newTaskData(taskData);
//                // Set setROIFlag to FALSE
//                taskData.setROIFlag=false;
//            }
//        }
//    }
//    // Reset ROI
//    else if(mouseData.rightButtonRelease)
//    {
//        // Set resetROIFlag to TRUE
//        taskData.resetROIFlag=true;
//        // Update task data in processingThread
//        emit newTaskData(taskData);
//        // Set resetROIFlag to FALSE
//        taskData.resetROIFlag=false;
//    }
//} // newMouseData()

void Piezas::newMouseData(struct MouseData mouseData)
{
    // Local variables
    int x_temp, y_temp, width_temp, height_temp;
    // Set ROI
    if(mouseData.leftButtonRelease)
    {
        // Copy box dimensions from mouseData to taskData
        taskData.selectionBox.setX(mouseData.selectionBox.x()-((_LabelCamara->width()-_Controller->captureThread->getInputSourceWidth()))/2);
        taskData.selectionBox.setY(mouseData.selectionBox.y()-((_LabelCamara->height()-_Controller->captureThread->getInputSourceHeight()))/2);
        taskData.selectionBox.setWidth(mouseData.selectionBox.width());
        taskData.selectionBox.setHeight(mouseData.selectionBox.height());
        // Check if selection box has NON-ZERO dimensions
        if((taskData.selectionBox.width()!=0)&&((taskData.selectionBox.height())!=0))
        {
            // Selection box can also be drawn from bottom-right to top-left corner
            if(taskData.selectionBox.width()<0)
            {
                x_temp=taskData.selectionBox.x();
                width_temp=taskData.selectionBox.width();
                taskData.selectionBox.setX(x_temp+taskData.selectionBox.width());
                taskData.selectionBox.setWidth(width_temp*-1);
            }
            if(taskData.selectionBox.height()<0)
            {
                y_temp=taskData.selectionBox.y();
                height_temp=taskData.selectionBox.height();
                taskData.selectionBox.setY(y_temp+taskData.selectionBox.height());
                taskData.selectionBox.setHeight(height_temp*-1);
            }
            // Check if selection box is not outside window
            if((taskData.selectionBox.x()<0)||(taskData.selectionBox.y()<0)||
               ((taskData.selectionBox.x()+taskData.selectionBox.width())>sourceWidth)||
               ((taskData.selectionBox.y()+taskData.selectionBox.height())>sourceHeight))
            {
                // Display error message
                QMessageBox::warning(this,"ERROR:","Selection box outside range. Please try again.");
            }
            else
            {
                // Set setROIFlag to TRUE
                taskData.setROIFlag=true;
                // Update task data in processingThread
                emit newTaskData(taskData);
                // Set setROIFlag to FALSE
                taskData.setROIFlag=false;
            }
        }
    }
    // Reset ROI
    else if(mouseData.rightButtonRelease)
    {
        // Set resetROIFlag to TRUE
        taskData.resetROIFlag=true;
        // Update task data in processingThread
        emit newTaskData(taskData);
        // Set resetROIFlag to FALSE
        taskData.resetROIFlag=false;
    }
} // newMouseData()

void Piezas::initializeImageProcessingFlagsStructure()
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

void Piezas::initializeTaskDataStructure()
{
    taskData.setROIFlag=false;
    taskData.resetROIFlag=false;
} // initializeTaskDataStructure()


void Piezas::camDisconnected()
{

    //qDebug() <<"***SE confirma desconexion";
    isCameraConnected = false;


} // camDisconnected()

void Piezas::initializeFrameLabel()
{
    _LabelCamara->setPixmap(_PixmapFrameLabel);

}

void Piezas::guardarImagen()
{

    if (isNewImagenReady == true)
    {

        //qDebug("Guardando imagen --- ");
        QDir::setCurrent(QCoreApplication::applicationDirPath());
        QDir tempDir;
        QString path = QDir::currentPath()+"/fichas";
        tempDir.mkdir(path);
        path = path+
                "/pieza"+
                QString::number(_IDPiezaActual)+
                ".png";
        bool sucessful = _PixmapSave.toImage().save(path,"PNG",100);
        if (sucessful)
        {
            qDebug("Imagen guardada!!!");
            actualizarImagen(_IDPiezaActual, path);
        }
        else
        {
            qDebug("Problemas al guardar imagen!!!");
        }
    }
}



///////////////////////////
///BEGINNIG: GETS
///////////////////////////

int Piezas::getDeviceNumber()
{

    return Constants::DEFAULT_CAMERA_DEV_NO;

} // getDeviceNumber()

int Piezas::getImageBufferSize()
{

    return Constants::DEFAULT_IMAGE_BUFFER_SIZE;

} // getImageBufferSize()

bool Piezas::getDropFrameCheckBoxState()
{

    return Constants::DEFAULT_DROP_FRAMES;

} // getDropFrameCheckBoxState()


int Piezas::getCaptureThreadPrio()
{
    return Constants::DEFAULT_CAP_THREAD_PRIO;

} // getCaptureThreadPrio()

int Piezas::getProcessingThreadPrio()
{
    return Constants::DEFAULT_PROC_THREAD_PRIO;
} // getProcessingThreadPrio()


///////////////////////////
///END: GETS
///////////////////////////


///////////////////////////
///BEGINNIG: SETS
///////////////////////////

void Piezas::setImageProcessingSettings()
{


} // setImageProcessingSettings()

void Piezas::setGrayscale(bool input)
{

} // setGrayscale()

void Piezas::setSmooth(bool input)
{

} // setSmooth()

void Piezas::setDilate(bool input)
{

} // setDilate()

void Piezas::setErode(bool input)
{

} // setErode()

void Piezas::setFlip(bool input)
{

} // setFlip()

void Piezas::setCanny(bool input)
{

} // setCanny()
///////////////////////////
///END: SETS
///////////////////////////

///////////////////////////
///
///////////////////////////

void Piezas::cargarPiezas()
{
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    QString path = QDir::currentPath()+"/fichas/pieza";

    for (int i = 0; i < Constants::CANTIDAD_PIEZAS; i++)
    {
        QString rutaPieza = path +
                QString::number(i)+
                ".png";
        QFile file(rutaPieza);
//        qDebug() << "Ruta pieza: ";
//        qDebug() << rutaPieza;
        Pieza *pieza;
        if (file.exists() == true)
        {
            pieza = new Pieza(":/images/icons/set_0/fichas/pieza" + QString::number(i) + ".png",
                              rutaPieza,
                              i,
                              _FramePiezas);
        }
        else
        {
            pieza = new Pieza(":/images/icons/set_0/fichas/pieza" + QString::number(i) + ".png",
                              ":/images/icons/set_0/cuidado.png",
                              i,
                              _FramePiezas);
        }

        //pieza->setDescripcion("<font color='white'>Esta es una ficha tipo: \n Y Tiene como función: \n</font>");
        pieza->setDescripcion("Esta es una ficha tipo: \nTiene como función: ");

        connect(pieza,SIGNAL(signalCambiarPieza(int)),this,SLOT(cambiarPieza(int)));
        pieza->move(0,i*266);
        pieza->setStyleSheet("color: rgba( 255, 255, 255, 0%);border-style: outset; border-radius: 10px; border-color: rgba(255, 255, 255, 0%);");
        //pieza->setStyleSheet("color: blue;border-style: outset; border-radius: 10px; border-color: red;");
        _ListaPiezas << pieza;

    }

}

void Piezas::mostrarPiezas()
{
    // Disconnect camera if connected
    if(isCameraConnected)
    {
        //qDebug() << "Desconectando camara";
        _Controller->disconnectCamera();
    }

    _BottunTakePhoto->hide();
    _LabelPhoto->hide();
    _MarcoLabelFoto->hide();
    _BottunSave->hide();
    ui->pushButtonAnterior->hide();

    ocultarFrameLabel();

    //QTimer::singleShot(1000, this, SLOT(reestablecerFondoLabelCamara()));

}

void Piezas::reducirScrollArea()
{
    QPropertyAnimation *animacionReducirHaciaIzquierda = new QPropertyAnimation(ui->scrollArea, "size", this);
    animacionReducirHaciaIzquierda->setDuration(2000);
    animacionReducirHaciaIzquierda->setStartValue(ui->scrollArea->size());
    animacionReducirHaciaIzquierda->setEndValue(QSize(100,Constants::TAM_Y_SCROll_AREA));
    animacionReducirHaciaIzquierda->setEasingCurve(QEasingCurve::OutBounce);

    animacionReducirHaciaIzquierda->start();

    connect(animacionReducirHaciaIzquierda,SIGNAL(finished()),this,SLOT(mostrarLabelCamara()));

}

void Piezas::aumentarScrollArea()
{
    _FramePiezas-> show();

    QPropertyAnimation *animacionReducirHaciaIzquierda = new QPropertyAnimation(ui->scrollArea, "size", this);
    animacionReducirHaciaIzquierda->setDuration(2000);
    animacionReducirHaciaIzquierda->setStartValue(ui->scrollArea->size());
    animacionReducirHaciaIzquierda->setEndValue(QSize(Constants::TAM_X_SCROll_AREA,
                                                      Constants::TAM_Y_SCROll_AREA));
    animacionReducirHaciaIzquierda->setEasingCurve(QEasingCurve::OutBounce);

    animacionReducirHaciaIzquierda->start();

    ui->pushButtonAnterior->hide();


}

void Piezas::mostrarLabelCamara()
{
    ui->scrollArea->setEnabled(false);
    _FramePiezas->hide();

    //qDebug("----------------");
    //qDebug("----------------");
    //qDebug("Mostrando Label camara");
    //qDebug("----------------");
    //qDebug("----------------");

    _LabelCamara->setPixmap(QPixmap(":/images/backgrounds/set_0/manos_3_640x480.png"));
    _LabelCamara->show();

    QParallelAnimationGroup *grupoParaleloDeAnimaciones = new QParallelAnimationGroup(_LabelCamara);

    QPropertyAnimation *propiedadTransparencia;

    if (QGraphicsOpacityEffect *effect =
            (static_cast<QGraphicsOpacityEffect*>(
                 _LabelCamara->graphicsEffect())))
    {
        propiedadTransparencia = new QPropertyAnimation(effect, "opacity");
        propiedadTransparencia->setStartValue(0.0);
        propiedadTransparencia->setEndValue(1.0);
        grupoParaleloDeAnimaciones->addAnimation(propiedadTransparencia);
    }

    QPropertyAnimation *animacionFondoAunmentarTam = new QPropertyAnimation(_LabelCamara, "size");
    animacionFondoAunmentarTam->setStartValue(QSize(0,0));
    animacionFondoAunmentarTam->setEndValue(QSize(Constants::RESOLUCION_W,Constants::RESOLUCION_H));
    grupoParaleloDeAnimaciones->addAnimation(animacionFondoAunmentarTam);

    for (int i = 0; i < grupoParaleloDeAnimaciones->animationCount(); ++i) {
        QPropertyAnimation *anim = qobject_cast<QPropertyAnimation *>(grupoParaleloDeAnimaciones->animationAt(i));
        anim->setEasingCurve(QEasingCurve::Linear);
        anim->setDuration(Constants::DURACION_ANIMACION_LABEL_CAMARA);
    }

    grupoParaleloDeAnimaciones->start();

    connect(grupoParaleloDeAnimaciones,SIGNAL(finished()),this,SLOT(iniciarCamara()));

}

void Piezas::ocultarFrameLabel()
{

    //_LabelCamara->show();

    //qDebug("----------------");
    //qDebug("----------------");
    //qDebug("Ocultando Label camara");
    //qDebug("----------------");
    //qDebug("----------------");

    QParallelAnimationGroup *grupoParaleloDeAnimaciones = new QParallelAnimationGroup(_LabelCamara);

    QPropertyAnimation *propiedadTransparencia;

    if (QGraphicsOpacityEffect *effect =
            (static_cast<QGraphicsOpacityEffect*>(
                 _LabelCamara->graphicsEffect())))
    {
        propiedadTransparencia = new QPropertyAnimation(effect, "opacity");
        propiedadTransparencia->setStartValue(1.0);
        propiedadTransparencia->setEndValue(0.0);
        grupoParaleloDeAnimaciones->addAnimation(propiedadTransparencia);
    }

    QPropertyAnimation *animacionFondoAunmentarTam = new QPropertyAnimation(_LabelCamara, "size");
    animacionFondoAunmentarTam->setStartValue(_LabelCamara->size());
    animacionFondoAunmentarTam->setEndValue(QSize(0,0));
    grupoParaleloDeAnimaciones->addAnimation(animacionFondoAunmentarTam);

    for (int i = 0; i < grupoParaleloDeAnimaciones->animationCount(); ++i) {
        QPropertyAnimation *anim = qobject_cast<QPropertyAnimation *>(grupoParaleloDeAnimaciones->animationAt(i));
        anim->setEasingCurve(QEasingCurve::Linear);
        anim->setDuration(Constants::DURACION_ANIMACION_LABEL_CAMARA);
    }

    grupoParaleloDeAnimaciones->start();

    ui->scrollArea->setEnabled(true);

    connect(grupoParaleloDeAnimaciones,SIGNAL(finished()),this,SLOT(aumentarScrollArea()));

}


void Piezas::actualizarImagen(int pID, QString pRutaImagenPersonalizada)
{
    _ListaPiezas[pID]->actualizarImagen(pRutaImagenPersonalizada);
    emit piezaPersonalizada(pID);
}

void Piezas::actualizarDescripcionFuncion(int pID,
                                          QString pFuncion,
                                          QString pDescripcion)
{
    _ListaPiezas[pID]->actualizarDescripcionFuncion(pFuncion,
                                                    pDescripcion);
}



/*Logica:
  La pieza emite una señal emitiendo el ID de la pieza
  a modificar
  Se llama a la función:
  cambiarPieza(int pID)

  Luego:
  iniciarCamara()
  iniciarCamaraAux()


*/


//Respaldos

//    // Update mouse cursor position in mouseCursorPosLabel in main window
//    mouseCursorPosLabel->setText(QString("(")+QString::number(frameLabel->getMouseCursorPos().x())+
//                                 QString(",")+QString::number(frameLabel->getMouseCursorPos().y())+
//                                 QString(")"));
//    // Show ROI-adjusted cursor position if camera is connected
//    if(isCameraConnected)
//        mouseCursorPosLabel->setText(mouseCursorPosLabel->text()+
//                                     QString(" [")+QString::number(frameLabel->getMouseCursorPos().x()-(640-controller->processingThread->getCurrentROI().width)/2)+
//                                     QString(",")+QString::number(frameLabel->getMouseCursorPos().y()-(480-controller->processingThread->getCurrentROI().height)/2)+
//                                     QString("]"));

// Update mouse cursor position in mouseCursorPosLabel in main window
//    QString posCursor;

//    // Update mouse cursor position in mouseCursorPosLabel in main window
//    setText(QString("(")+QString::number(frameLabel->getMouseCursorPos().x())+
//                                 QString(",")+QString::number(frameLabel->getMouseCursorPos().y())+
//                                 QString(")"));
//    // Show ROI-adjusted cursor position if camera is connected
//    if(isCameraConnected)
//        mouseCursorPosLabel->setText(mouseCursorPosLabel->text()+
//                                     QString(" [")+QString::number(frameLabel->getMouseCursorPos().x()-(640-controller->processingThread->getCurrentROI().width)/2)+
//                                     QString(",")+QString::number(frameLabel->getMouseCursorPos().y()-(480-controller->processingThread->getCurrentROI().height)/2)+
//                                     QString("]"));


//    // Show ROI-adjusted cursor position if camera is connected
//    if(isCameraConnected)
//    {
//        posCursor = QString(" [")+QString::number(_LabelCamara->getMouseCursorPos().x()-(640-_Controller->processingThread->getCurrentROI().width)/2)+
//                QString(",")+QString::number(_LabelCamara->getMouseCursorPos().y()-(480-_Controller->processingThread->getCurrentROI().height)/2)+
//                QString("]");
//    }
//    else
//    {
//        posCursor = QString("(")+QString::number(_LabelCamara->getMouseCursorPos().x())+
//                QString(",")+QString::number(_LabelCamara->getMouseCursorPos().y())+
//                QString(")");
//    }

//    //qDebug() <<"***";
//    //qDebug() <<"Posicion del cursor";
//    //qDebug() << posCursor;
//    //qDebug() <<"***";
