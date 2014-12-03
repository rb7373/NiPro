#include "frametablero.h"
#include "ui_frametablero.h"

//#define FILAS_PIEZAS 8
//#define COLUMNAS_PIEZAS 12

FrameTablero::FrameTablero(AdministradorPiezas *pAdministradorPiezas,
                           QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameTablero)
{
    ui->setupUi(this);

    connect(ui->pushButtonCerrar,SIGNAL(clicked()),this,SLOT(deleteLater()));

    _AdministradorPiezas = pAdministradorPiezas;

    widthPieza = 64;
    heightPieza = 64;
    separacionX = 10;
    separacionY = 10;

    widthPiezaTotal = widthPieza + separacionX;
    heightPiezaTotal = heightPieza + separacionY;

    widthTablero = Constants::CANTIDAD_PIEZAS_TABLERO_X*(widthPieza+separacionX);
    heightTablero = Constants::CANTIDAD_PIEZAS_TABLERO_Y*(heightPieza+separacionY);

    resize(Constantes::TAM_X,Constantes::TAM_Y);

    int origenX = (width() - (widthTablero))/2;
    int origenY = (height() - (heightTablero))/2;

    QLabel *labelTemp;
    //int index = 0;
    for (int i = 0;  i < Constants::CANTIDAD_PIEZAS_TABLERO_Y; i++)
    {
        for (int j = 0;  j < Constants::CANTIDAD_PIEZAS_TABLERO_X; j++)
        {
            labelTemp = new QLabel(this);
            //labelTemp->setPixmap(QPixmap(QString::fromUtf8(":/images/icons/set_0/nothing.png")));
            labelTemp->setScaledContents(true);
            labelTemp->setGeometry(origenX+j*widthPieza+separacionX,origenY+i*heightPieza+separacionY,widthPieza,heightPieza);
            //labelTemp->setStyleSheet("background-color:rgb(255,255,255,255); color:rgb(0,95,114,255); border-radius: 10px; border-style: outset; border-width: 1px; border-color:rgb(0,95,114,255);");
            labelTemp->setStyleSheet("background-color:rgb(0,0,0,0); color:rgb(0,0,0,0);  border-style: outset; border-width: 1px; border-color:rgb(0,0,0,0);");
            _Piezas.append(labelTemp);
            _ListaPiezasID.append(-1); //se inicializan los ids
            matrizEstadoAnterior[i][j] = false;
            matrizEstadoActual[i][j] = false;
            ////qDebug()"Insertando en la matriz");
            ////qDebug()) <<"index: "<< index++;
            ////qDebug()) <<"conponente ("<< i <<" ,"<< j<<")";

        }
    }

    escalaX = ((Constants::CANTIDAD_PIEZAS_TABLERO_X*widthPiezaTotal))/(Constants::RESOLUCION_W+0.0);
    escalaY = ((Constants::CANTIDAD_PIEZAS_TABLERO_Y*heightPiezaTotal))/(Constants::RESOLUCION_H+0.0);


    ////qDebug()) << "escala x = " << escalaX;
    ////qDebug()) << "escala  y = " << escalaY;



    isCameraConnected = false;
    isPaused = true;

    crearObjetos();

}



FrameTablero::~FrameTablero()
{
    delete ui;

    // Disconnect camera if connected
    if(isCameraConnected)
    {
        disconnectCamera();
    }
}

void FrameTablero::disconnectCamera()
{
    // Check if camera is connected
    if(_Controller->captureThread->isCameraConnected())
    {
        // Disconnect connections

        disconnect(_Controller->processingThread,SIGNAL(nuevaPieza(float,float,float,float,int)),
                   0,0);
        disconnect(this,SIGNAL(newImageProcessingFlags(struct ImageProcessingFlags)),_Controller->processingThread,SLOT(updateImageProcessingFlags(struct ImageProcessingFlags)));
        disconnect(this,SIGNAL(newImageProcessingSettings(struct ImageProcessingSettings)),_Controller->processingThread,SLOT(updateImageProcessingSettings(struct ImageProcessingSettings)));

        disconnect(_Controller->processingThread,SIGNAL(iniciaProcesamientoEspecial(bool)), 0,0);


        // Reset flag
        isCameraConnected=false;

        // Disconnect camera
        _Controller->disconnectCamera();

    }
    // Display error dialog
    else
        QMessageBox::warning(0,"ERROR:","La camara ya se encuentra conectada");
} // disconnectCamera()

void FrameTablero::reActulizarPantalla(bool inicia)
{
    if (isPaused == false)
    {
        if (inicia)
        {
            //qDebug()) <<"------------------------";
            //qDebug()) <<"INICIA";
            //qDebug()) <<"------------------------";
            for (int i = 0;  i < Constants::CANTIDAD_PIEZAS_TABLERO_Y; i++)
            {
                for (int j = 0;  j < Constants::CANTIDAD_PIEZAS_TABLERO_X; j++)
                {
                    matrizEstadoAnterior[i][j] = matrizEstadoActual[i][j];
                    matrizEstadoActual[i][j] = false;
                }
            }
        }
        else
        {
            ////qDebug()) <<"------------------------";
            ////qDebug()) <<"FINALIZA";
            ////qDebug()) <<"------------------------";
            for (int i = 0;  i < Constants::CANTIDAD_PIEZAS_TABLERO_Y; i++)
            {
                for (int j = 0;  j < Constants::CANTIDAD_PIEZAS_TABLERO_X; j++)
                {
                    if ( (matrizEstadoActual[i][j] == false) &&  (matrizEstadoAnterior[i][j] == true))
                    {
                        ////qDebug()) <<"------------------------";
                        ////qDebug()) << i <<" ,"<< j;
                        int numeroLabel = i*Constants::CANTIDAD_PIEZAS_TABLERO_X+j;
                        //_Piezas[numeroLabel]->setPixmap(QPixmap(QString::fromUtf8(":/images/icons/set_0/nothing.png")));
                        _Piezas[numeroLabel]->setPixmap(0);
                        _ListaPiezasID[numeroLabel] = -1;

                    }
                }
            }
        }
    }
}

void FrameTablero::actualizarPiezas(float pX,
                                    float pY,
                                    float pWidth,
                                    float pHeight,
                                    int pID)
{

    bool size = pWidth < 100 &&
            pWidth > 10 &&
            pHeight < 100 &&
            pHeight > 10;


    if (isPaused == false && size == true)
    {

        double nuevaPosX = pX*(escalaX+ 0.0);
        double nuevaPosY = pY*(escalaY+ 0.0) ;
        double col = nuevaPosX/ (widthPiezaTotal + 0.0);
        double row = nuevaPosY/ (heightPiezaTotal + 0.0);

        //qDebug()"Actualizando piezas GUI");
        //qDebug()"Numeros importantes");

        //qDebug()) << "wP = " << widthTablero;
        //qDebug()) << "hP = " << heightTablero;
        //qDebug()) << "id = " << pID;

        //    QString rutaIcon = ":/images/icons/set_0/fichas/pieza" + QString::number(pID) + ".png";
        //    float x = factorX*pX;
        //    float y = factorY*pY;

        //    float numberLabelX =  x / 9;
        //    float numberLabelY = y / 5;

        //qDebug()"Actualizando piezas GUI");
        //    //qDebug()"Numeros recibidos");
        //    //qDebug()) << "x = " << pX;
        //    //qDebug()) << "y = " << pY;
        //    //qDebug()) << "w = " << pWidth;
        //    //qDebug()) << "h = " << pHeight;
        //    //qDebug()) << "id = " << pID;

        //    //qDebug()) << "row = " << row;
        //    //qDebug()) << "col = " << col;

        //qDebug()) << "xO = " << pX;
        //qDebug()) << "yO = " << pY;
        //qDebug()) << "xN = " << nuevaPosX;
        //qDebug()) << "yN = " << nuevaPosY;

        //    //qDebug()) << "id = " << pID;

        //        int rowR = floor( row); //Se redondea
        //        int colR = floor( col); //Se redondea


        int rowR = floor( row + 0.5); //Se redondea
        int colR = floor( col + 0.5); //Se redondea

        //qDebug()) << "row = " << rowR;
        //qDebug()) << "col = " << colR;
        ////qDebug()) << "Cantidad de labels" << _Piezas.size();

        int numeroLabel = rowR*Constants::CANTIDAD_PIEZAS_TABLERO_X+colR;
        if (_Piezas.size() > numeroLabel)
        {
            _ListaPiezasID[numeroLabel] = pID;
            _Piezas[numeroLabel]->setPixmap(":/images/icons/set_0/fichas/pieza" + QString::number(pID) + ".png");
            matrizEstadoActual[rowR][colR] = true;
        }
        //    //qDebug()) << row << ", " << col;
    }

}

void FrameTablero::crearObjetos()
{
    // Create controller
    _Controller = new Controller(this);
    //Controlador
    //connect(_Controller,SIGNAL(camDisconnected()),this,SLOT(actulizarPlay()));
    connect(ui->pushButtonPlay,SIGNAL(clicked()),this,SLOT(actulizarPlay()));
    connect(ui->pushButtonStop,SIGNAL(clicked()),this,SLOT(actualizarStop()));
    connect(ui->pushButtonPause,SIGNAL(clicked()),this,SLOT(actualizarPause()));

}


void FrameTablero::actulizarPlay()
{

    ui->pushButtonPlay->setEnabled(false);
    ui->pushButtonStop->setEnabled(true);
    ui->pushButtonPause->setEnabled(true);
    isPaused = false;

    if (isCameraConnected == false)
    {
        connectToCamera();
    }

}

void FrameTablero::actualizarStop()
{

    ui->pushButtonPlay->setEnabled(true);
    ui->pushButtonStop->setEnabled(false);
    ui->pushButtonPause->setEnabled(false);

    // Disconnect camera if connected
    if(isCameraConnected)
    {
        _Controller->disconnectCamera();
        isCameraConnected = false;
        isPaused = true;
    }
}

void FrameTablero::actualizarPause()
{

    ui->pushButtonPlay->setEnabled(true);
    ui->pushButtonStop->setEnabled(true);
    ui->pushButtonPause->setEnabled(false);
    isPaused = true;

}




void FrameTablero::connectToCamera()
{

    if (isCameraConnected == false)
    {
        //qDebug()"Activando camara");

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
            ui->pushButtonPlay->setEnabled(false);
            ui->pushButtonStop->setEnabled(true);
            ui->pushButtonPause->setEnabled(true);
        }
        // Display error dialog if camera connection is unsuccessful
        else
        {
            QMessageBox::warning(0,"ERROR:","No se pudo conectar la camara");
        }
    }
    else
    {
        //nada importante por el momento
        ui->pushButtonPlay->setEnabled(false);
        ui->pushButtonStop->setEnabled(true);
        ui->pushButtonPause->setEnabled(true);
    }

} // connectToCamera()


void FrameTablero::connectToCameraAux()
{
    _Controller->processingThread->_AdministradorPiezas = _AdministradorPiezas;

    // Create connection between processing thread (emitter)
    // and GUI thread (receiver/listener)
    //connect(_Controller->processingThread,SIGNAL(newFrame(QImage)),this,SLOT(updateFrame(QImage)));


    connect(_Controller->processingThread,SIGNAL(nuevaPieza(float,float,float,float,int)),
            this,SLOT(actualizarPiezas(float,
                                       float,
                                       float,
                                       float,
                                       int)));

    connect(_Controller->processingThread,SIGNAL(iniciaProcesamientoEspecial(bool)), this, SLOT(reActulizarPantalla(bool)));



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

    ////qDebug()) << "Ancho: " << sourceWidth;
    ////qDebug()) << "Ancho: " << sourceHeight;

    // Set text in labels in main window
    //Modiciar
}


void FrameTablero::initializeImageProcessingFlagsStructure()
{

    imageProcessingFlags.grayscaleOn = Constants::DEFAULT_GRAYSCALE;
    imageProcessingFlags.smoothOn = Constants::DEFAULT_SMOOTH;
    imageProcessingFlags.dilateOn = Constants::DEFAULT_DILATE;
    imageProcessingFlags.erodeOn = Constants::DEFAULT_ERODE;
    imageProcessingFlags.flipOn = Constants::DEFAULT_FLIP;
    imageProcessingFlags.cannyOn = Constants::DEFAULT_CANNY;
    imageProcessingFlags.encontrarPiezas = Constants::DEFAULT_FIND_PIECES;
    imageProcessingFlags.encontrarPieza = true;


} // initializeImageProcessingFlagsStructure()

void FrameTablero::updateStoredSettings()
{
    resetAllToDefaults();
    emit newImageProcessingSettings(imageProcessingSettings);
} // updateStoredSettings()

void FrameTablero::resetAllToDefaults()
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


///////////////////////////
///BEGINNIG: GETS
///////////////////////////

int FrameTablero::getDeviceNumber()
{

    return Constants::DEFAULT_CAMERA_DEV_NO;

} // getDeviceNumber()

int FrameTablero::getImageBufferSize()
{

    return Constants::DEFAULT_IMAGE_BUFFER_SIZE;

} // getImageBufferSize()

bool FrameTablero::getDropFrameCheckBoxState()
{

    return Constants::DEFAULT_DROP_FRAMES;

} // getDropFrameCheckBoxState()


int FrameTablero::getCaptureThreadPrio()
{
    return Constants::DEFAULT_CAP_THREAD_PRIO;

} // getCaptureThreadPrio()

int FrameTablero::getProcessingThreadPrio()
{
    return Constants::DEFAULT_PROC_THREAD_PRIO;
} // getProcessingThreadPrio()

void FrameTablero::on_pushButtonUpdate_clicked()
{


    actualizarPause();

    comprobarCambios();

    actualizarStop();

    FrameIDE *IDE = new FrameIDE(parentWidget());



    IDE->preEstablecerConfiguracionPiezas(_ListaPiezasID);

    IDE->show();

    close();
}

void FrameTablero::comprobarCambios()
{
    for (int i = 0;  i < Constants::CANTIDAD_PIEZAS_TABLERO_Y; i++)
    {
        for (int j = 0;  j < Constants::CANTIDAD_PIEZAS_TABLERO_X; j++)
        {
            if ( (matrizEstadoActual[i][j] == false) &&  (matrizEstadoAnterior[i][j] == true))
            {
                int numeroLabel = i*Constants::CANTIDAD_PIEZAS_TABLERO_X+j;
                _Piezas[numeroLabel]->setPixmap(0);
                _ListaPiezasID[numeroLabel] = -1;
            }
        }
    }
}


