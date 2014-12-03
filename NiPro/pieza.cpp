#include "pieza.h"
#include "ui_pieza.h"

Pieza::Pieza(QString pRutaImagenDefecto,
             QString pRutaImagenPersonalizada,
             int pID, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pieza)
{
    ui->setupUi(this);

    _RutaImagenDefecto = pRutaImagenDefecto;
    _RutaImagenPersonalizada = pRutaImagenPersonalizada;

    _FactorEscala = 3;
    _FactorCambio = 2;

    crearObjetos();
    _ID = pID;

    ui->labelDescripcion->setStyleSheet("background-color:rgb(89,41,93,193);\nborder-style: ridge;\nborder-width: 4px;\nborder-radius: 10px;\nborder-color: rgb(89,41,93,193);\nfont: 75 14pt 'Comic Sans MS';\ncolor: white;\npadding: 6px; \n");



}

Pieza::~Pieza()
{
    delete ui;
}

void Pieza::crearObjetos()
{
    //Imagen por defecto

    _PushButtonImagenDigital = new BotonAnimadoA(this);

    _PushButtonImagenDigital->setFocusPolicy(Qt::NoFocus);
    _PushButtonImagenDigital->setFlat(true);

    _PushButtonImagenDigital->setStyleSheet(Constants::TRANSPARENT_BACKGROUND);

    _PushButtonImagenDigital->setIconSize(QSize(Constants::SIZE_ICON_X*_FactorEscala,
                                                Constants::SIZE_ICON_Y*_FactorEscala));
    _PushButtonImagenDigital->setDuracionAnimacion(Constants::DURACION_ANIMACION_BOTON);
    _PushButtonImagenDigital->setCambioTamXY(Constants::CHANGE_SIZE_BUTTON_X*_FactorCambio,
                                             Constants::CHANGE_SIZE_BUTTON_Y*_FactorCambio);
    _PushButtonImagenDigital->setIcon(QIcon(_RutaImagenDefecto));

    _PushButtonImagenDigital->setTamIconoXY(Constants::SIZE_ICON_X*_FactorEscala,
                                            Constants::SIZE_ICON_Y*_FactorEscala);

    _PushButtonImagenDigital->setCambioDeTam(true);
    _PushButtonImagenDigital->setTipoInterpolacion(QEasingCurve::OutBounce);

    _PushButtonImagenDigital->setGeometry(0,
                                          0,
                                          Constants::SIZE_ICON_X*_FactorEscala,
                                          Constants::SIZE_ICON_Y*_FactorEscala);

    _PushButtonImagenDigital->setPosicionInicialXY(0,0);

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
    _BottunTakePhoto->setGeometry(190,
                                  100,
                                  Constants::SIZE_ICON_X+
                                  Constants::INCREASE_SIZE_20,
                                  Constants::SIZE_ICON_Y+
                                  Constants::INCREASE_SIZE_20);

    _BottunTakePhoto->setPosicionInicialXY(190,
                                           100);

    _BottunTakePhoto->setTexto("<font color='white'>Cambiar</font>");
    _BottunTakePhoto->centrarTexto();

    connect(_BottunTakePhoto,SIGNAL(clicked()),this,SLOT(slotCambiarPieza()));

    //Imagen ingresada por el usuario

    _PushButtonImagenPersonalizada = new BotonAnimadoA(this);

    _PushButtonImagenPersonalizada->setFocusPolicy(Qt::NoFocus);
    _PushButtonImagenPersonalizada->setFlat(true);

    _PushButtonImagenPersonalizada->setStyleSheet(Constants::TRANSPARENT_BACKGROUND);

    _PushButtonImagenPersonalizada->setIconSize(QSize(Constants::SIZE_ICON_X*_FactorEscala,
                                                      Constants::SIZE_ICON_Y*_FactorEscala));
    _PushButtonImagenPersonalizada->setDuracionAnimacion(Constants::DURACION_ANIMACION_BOTON);
    _PushButtonImagenPersonalizada->setCambioTamXY(Constants::CHANGE_SIZE_BUTTON_X*_FactorCambio,
                                                   Constants::CHANGE_SIZE_BUTTON_Y*_FactorCambio);

    _PushButtonImagenPersonalizada->setIcon(QIcon(_RutaImagenPersonalizada));

    _PushButtonImagenPersonalizada->setTamIconoXY(Constants::SIZE_ICON_X*_FactorEscala,
                                                  Constants::SIZE_ICON_Y*_FactorEscala);

    _PushButtonImagenPersonalizada->setCambioDeTam(true);
    _PushButtonImagenPersonalizada->setTipoInterpolacion(QEasingCurve::OutBounce);

    _PushButtonImagenPersonalizada->setGeometry(_BottunTakePhoto->x()+
                                                _BottunTakePhoto->width(),
                                                0,
                                                Constants::SIZE_ICON_X*_FactorEscala,
                                                Constants::SIZE_ICON_Y*_FactorEscala);

    _PushButtonImagenPersonalizada->setPosicionInicialXY(_BottunTakePhoto->x()+
                                                         _BottunTakePhoto->width(),
                                                         0);

}

void Pieza::setDescripcion(QString pDescripcion)
{
    ui->labelDescripcion->setText(pDescripcion);
}

void Pieza::slotCambiarPieza()
{
    emit signalCambiarPieza(_ID);
}

void Pieza::actualizarImagen(QString pRutaIconoPersonalizado)
{
    _RutaImagenPersonalizada = pRutaIconoPersonalizado;

    _PushButtonImagenPersonalizada->setIcon(QIcon(_RutaImagenPersonalizada));



}

void Pieza::actualizarDescripcionFuncion(QString pFuncion,
                                         QString pDescripcion)
{
    ui->labelDescripcion->setText(pFuncion+ "\n" +
                                  pDescripcion);

}


