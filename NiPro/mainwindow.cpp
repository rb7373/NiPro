#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Se crea el administrador principal de la aplicacion
    _Administrador = new AdministradorPrincipal(this);
    _AdministradorPiezas = _Administrador->_AdministradorPiezas;

    //Modificacion de la ventana

    _FactorEscala = 3;
    _FactorCambio = 2;

    //setStyleSheet(Constantes::FONDO_NEGRO);
    setWindowTitle(Constantes::TITULO_PRINCIPAL);
    resize(Constantes::TAM_X,Constantes::TAM_Y);

    //Se crean los objetos necesarios
    crearObjetos();
    //Se modifican los objetos creados
    modificarObjetos();

    //Se inician las animaciones
    iniciarAnimaciones();

    centrarVentana();

    //AdministradorProcesamientoImagenes::getInstance()->mostrarEstado();

}

MainWindow::~MainWindow()
{
    delete ui;

    //AdministradorProcesamientoImagenes::destroy();
}


void MainWindow::crearObjetos()
{
    _AreaPrincipal = new QWidget(this);
    _BottunPieces = new BotonAnimadoA(_AreaPrincipal);
    _BottunSettings = new BotonAnimadoA(_AreaPrincipal);
    _BottunPantallaProgramacion= new BotonAnimadoA(_AreaPrincipal);
    _BottunIDEProgramacion= new BotonAnimadoA(_AreaPrincipal);

}

void MainWindow::modificarObjetos()
{
    _AreaPrincipal->setStyleSheet(Constantes::FONDO_NEGRO);
    _BottunPieces->setFocusPolicy(Qt::NoFocus);
    _BottunPieces->setFlat(true);
    _BottunPieces->setStyleSheet(Constants::TRANSPARENT_BACKGROUND+
                                 Constants::TITLE_BUTTON_COMIC);

    _BottunPieces->setIconSize(QSize(Constants::SIZE_ICON_X*_FactorEscala,
                                     Constants::SIZE_ICON_Y*_FactorEscala));

    _BottunPieces->setDuracionAnimacion(Constants::DURACION_ANIMACION_BOTON);
    _BottunPieces->setCambioTamXY(Constants::CHANGE_SIZE_BUTTON_X*_FactorCambio,
                                  Constants::CHANGE_SIZE_BUTTON_Y*_FactorCambio);

    _BottunPieces->setIcon(QIcon(Constants::PATH_ICON_PIECES));

    _BottunPieces->setTamIconoXY(Constants::SIZE_ICON_X*_FactorEscala,
                                 Constants::SIZE_ICON_Y*_FactorEscala);

    _BottunPieces->setCambioPosicion(Constants::CHANGE_POS_BUTTON);

    _BottunPieces->setCambioDeTam(true);
    _BottunPieces->setCambioDePos(true);
    _BottunPieces->setCambioDeTransp(true);
    _BottunPieces->setTipoInterpolacion(QEasingCurve::OutBounce);

    //Correction in size in order to show the button text
    _BottunPieces->setGeometry(0,
                               0,
                               Constants::SIZE_ICON_X*_FactorEscala+
                               Constants::INCREASE_SIZE_40,
                               Constants::SIZE_ICON_Y*_FactorEscala+
                               Constants::INCREASE_SIZE_40);

    _BottunPieces->setPosicionInicialXY(20,
                                        Constants::POS_BUTTON_CAMERA_CHECK_Y+100);


    _BottunPieces->setTexto(Constants::TITLE_BUTTON_PIECES);
    _BottunPieces->centrarTexto();

    connect(_BottunPieces,SIGNAL(clicked()),this,SLOT(mostrarPiezas()));

    _BottunSettings->setFocusPolicy(Qt::NoFocus);
    _BottunSettings->setFlat(true);
    _BottunSettings->setStyleSheet(Constants::TRANSPARENT_BACKGROUND+
                                   Constants::TITLE_BUTTON_COMIC);

    _BottunSettings->setIconSize(QSize(Constants::SIZE_ICON_X*_FactorEscala,
                                       Constants::SIZE_ICON_Y*_FactorEscala));

    _BottunSettings->setDuracionAnimacion(Constants::DURACION_ANIMACION_BOTON);
    _BottunSettings->setCambioTamXY(Constants::CHANGE_SIZE_BUTTON_X,
                                    Constants::CHANGE_SIZE_BUTTON_Y);
    _BottunSettings->setIcon(QIcon(Constants::PATH_ICON_SETTINGS));

    _BottunSettings->setTamIconoXY(Constants::SIZE_ICON_X*_FactorEscala,
                                   Constants::SIZE_ICON_Y*_FactorEscala);

    _BottunSettings->setCambioPosicion(Constants::CHANGE_POS_BUTTON);

    _BottunSettings->setCambioDeTam(true);
    _BottunSettings->setCambioDePos(true);
    _BottunSettings->setCambioDeTransp(true);
    _BottunSettings->setTipoInterpolacion(QEasingCurve::OutBounce);

    //Correction in size in order to show the button text
    _BottunSettings->setGeometry(_BottunPieces->x()+
                                 _BottunPieces->width(),
                                 0,
                                 Constants::SIZE_ICON_X*_FactorEscala+
                                 Constants::INCREASE_SIZE_40,
                                 Constants::SIZE_ICON_Y*_FactorEscala+
                                 Constants::INCREASE_SIZE_40);

    _BottunSettings->setPosicionInicialXY(_BottunPieces->x()+
                                          _BottunPieces->width(),
                                          Constants::POS_BUTTON_CAMERA_CHECK_Y+100);


    _BottunSettings->setTexto(Constants::TITLE_BUTTON_PRUEBAS);
    _BottunSettings->centrarTexto();

    connect(_BottunSettings,SIGNAL(clicked()),this,SLOT(mostrarPruebas()));



    _BottunPantallaProgramacion->setFocusPolicy(Qt::NoFocus);
    _BottunPantallaProgramacion->setFlat(true);
    _BottunPantallaProgramacion->setStyleSheet(Constants::TRANSPARENT_BACKGROUND+
                                               Constants::TITLE_BUTTON_COMIC);

    _BottunPantallaProgramacion->setIconSize(QSize(Constants::SIZE_ICON_X*_FactorEscala,
                                                   Constants::SIZE_ICON_Y*_FactorEscala));

    _BottunPantallaProgramacion->setDuracionAnimacion(Constants::DURACION_ANIMACION_BOTON);
    _BottunPantallaProgramacion->setCambioTamXY(Constants::CHANGE_SIZE_BUTTON_X,
                                                Constants::CHANGE_SIZE_BUTTON_Y);
    _BottunPantallaProgramacion->setIcon(QIcon(Constants::PATH_ICON_PROGRAMMING));

    _BottunPantallaProgramacion->setTamIconoXY(Constants::SIZE_ICON_X*_FactorEscala,
                                               Constants::SIZE_ICON_Y*_FactorEscala);

    _BottunPantallaProgramacion->setCambioPosicion(Constants::CHANGE_POS_BUTTON);

    _BottunPantallaProgramacion->setCambioDeTam(true);
    _BottunPantallaProgramacion->setCambioDePos(true);
    _BottunPantallaProgramacion->setCambioDeTransp(true);
    _BottunPantallaProgramacion->setTipoInterpolacion(QEasingCurve::OutBounce);

    //Correction in size in order to show the button text
    _BottunPantallaProgramacion->setGeometry(_BottunSettings->x()+
                                             _BottunSettings->width(),
                                             0,
                                             Constants::SIZE_ICON_X*_FactorEscala+
                                             Constants::INCREASE_SIZE_40,
                                             Constants::SIZE_ICON_Y*_FactorEscala+
                                             Constants::INCREASE_SIZE_40);

    _BottunPantallaProgramacion->setPosicionInicialXY(_BottunSettings->x()+
                                                      _BottunSettings->width(),
                                                      Constants::POS_BUTTON_CAMERA_CHECK_Y+100);


    _BottunPantallaProgramacion->setTexto(Constants::TITLE_BUTTON_PROGRAMACION);
    _BottunPantallaProgramacion->centrarTexto();

    connect(_BottunPantallaProgramacion,SIGNAL(clicked()),this,SLOT(mostrarPantallaProgramacion()));


    _BottunIDEProgramacion->setFocusPolicy(Qt::NoFocus);
    _BottunIDEProgramacion->setFlat(true);
    _BottunIDEProgramacion->setStyleSheet(Constants::TRANSPARENT_BACKGROUND+
                                          Constants::TITLE_BUTTON_COMIC);

    _BottunIDEProgramacion->setIconSize(QSize(Constants::SIZE_ICON_X*_FactorEscala,
                                              Constants::SIZE_ICON_Y*_FactorEscala));

    _BottunIDEProgramacion->setDuracionAnimacion(Constants::DURACION_ANIMACION_BOTON);
    _BottunIDEProgramacion->setCambioTamXY(Constants::CHANGE_SIZE_BUTTON_X,
                                           Constants::CHANGE_SIZE_BUTTON_Y);
    _BottunIDEProgramacion->setIcon(QIcon(Constants::PATH_ICON_PROGRAMMING_IDE));

    _BottunIDEProgramacion->setTamIconoXY(Constants::SIZE_ICON_X*_FactorEscala,
                                          Constants::SIZE_ICON_Y*_FactorEscala);

    _BottunIDEProgramacion->setCambioPosicion(Constants::CHANGE_POS_BUTTON);

    _BottunIDEProgramacion->setCambioDeTam(true);
    _BottunIDEProgramacion->setCambioDePos(true);
    _BottunIDEProgramacion->setCambioDeTransp(true);
    _BottunIDEProgramacion->setTipoInterpolacion(QEasingCurve::OutBounce);

    //Correction in size in order to show the button text
    _BottunIDEProgramacion->setGeometry(_BottunPantallaProgramacion->x()+
                                        _BottunPantallaProgramacion->width(),
                                        0,
                                        Constants::SIZE_ICON_X*_FactorEscala+
                                        Constants::INCREASE_SIZE_40,
                                        Constants::SIZE_ICON_Y*_FactorEscala+
                                        Constants::INCREASE_SIZE_40);

    _BottunIDEProgramacion->setPosicionInicialXY(_BottunPantallaProgramacion->x()+
                                                 _BottunPantallaProgramacion->width(),
                                                 Constants::POS_BUTTON_CAMERA_CHECK_Y+100);


    _BottunIDEProgramacion->setTexto(Constants::TITLE_BUTTON_IDE);
    _BottunIDEProgramacion->centrarTexto();

    connect(_BottunIDEProgramacion,SIGNAL(clicked()),this,SLOT(mostrarIDE()));

}

void MainWindow::centrarAreaPrincipal()
{
    int tamXMainWindows = size().width();

    if (tamXMainWindows >= Constantes::TAM_X)
    {
        _AreaPrincipal->setGeometry((tamXMainWindows - Constantes::TAM_X) / 2,_AreaPrincipal->pos().y(),
                                    Constantes::TAM_X, Constantes::TAM_Y);

    }

    int tamYMainWindows = size().height();

    if (tamYMainWindows >= Constantes::TAM_Y)
    {
        _AreaPrincipal->setGeometry(_AreaPrincipal->pos().x(),(tamXMainWindows - Constantes::TAM_X) / 2,
                                    Constantes::TAM_X, Constantes::TAM_Y);
    }

}


void MainWindow::centrarVentana()
{
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,
                                          Qt::AlignCenter, this->size(), qApp->desktop()->availableGeometry()));
    //    int W = qApp->desktop()->availableGeometry().width();
    //    int H = qApp->desktop()->availableGeometry().height();

    //    move(0,0);

    //    setMinimumSize(W,H);
    //    setMaximumSize(W,H);
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    centrarAreaPrincipal();
}



void MainWindow::iniciarAnimaciones()
{

}

void MainWindow::mostrarPiezas()
{
    Piezas *piezas = new Piezas(_AdministradorPiezas, _AreaPrincipal);
    connect(piezas, SIGNAL(piezaPersonalizada(int)),_Administrador,SLOT(actualizarPieza(int)));
    connect(_Administrador,SIGNAL(nuevaDescripcionFuncion(int,QString,QString))
            ,piezas,SLOT(actualizarDescripcionFuncion(int,QString,QString)));
    connect(piezas, SIGNAL(destroyed()),_Administrador,SLOT(guardarXML()));
    piezas->show();
}

void MainWindow::mostrarPruebas()
{
    PruebasFichas *pruebas = new PruebasFichas(_AdministradorPiezas, _AreaPrincipal);

    pruebas->show();
}

void MainWindow::mostrarPantallaProgramacion()
{
    FrameTablero *tablero = new FrameTablero(_AdministradorPiezas, _AreaPrincipal);

    tablero->show();
}

void MainWindow::mostrarIDE()
{
    FrameIDE *IDE = new FrameIDE(_AreaPrincipal);

    IDE->show();
}








