#include "botonanimadoa.h"

BotonAnimadoA::BotonAnimadoA(QWidget *parent) :
    QPushButton(parent)
{

    //defaul settings
    _DuracionAnimacion = 2000;
    _CambioTamIconoX = 10;
    _CambioTamIconoY = 10;
    _TamInicialIconoX = 48;
    _TamIconoInicialY = 48;
    _CambioPosicionBoton = 20;
    _PosicionInicialX = 100;
    _PosicionInicialY = 100;

    _LabelTexto = new QLabel(this);
    _LabelTexto->setStyleSheet(Constants::TRANSPARENT_BACKGROUND);
    effect = new QGraphicsOpacityEffect(this);
    effect->setOpacity(0.0);
    _LabelTexto->setGraphicsEffect(effect);

    setCambioDePos(false);
    setCambioDeTam(false);
    setCambioDeTransp(false);

    //defaul settings

    _TipoInterpolacion = _TipoInterpolacion;

    iniciarAnimacion();
}

///***///
//METODOS PUBLICOS
///***///

void BotonAnimadoA::setDuracionAnimacion(int pDuracion)
{
    _DuracionAnimacion = pDuracion;
}

void BotonAnimadoA::setCambioTamXY(int pCambioX,int pCambioY)
{
    _CambioTamIconoX = pCambioX;
    _CambioTamIconoY = pCambioY;
}

void BotonAnimadoA::setTamIconoXY(int pTamX,int pTamY)
{
    _TamInicialIconoX = pTamX;
    _TamIconoInicialY = pTamY;
}

void BotonAnimadoA::setCambioPosicion(int pCambio)
{
    _CambioPosicionBoton = pCambio;
}

void BotonAnimadoA::setPosicionInicialXY(int pPosX, int pPosY)
{
    _PosicionInicialX = pPosX;
    _PosicionInicialY = pPosY;
}

void BotonAnimadoA::setTexto(QString pTexto)
{
    _LabelTexto->setText(pTexto);
}

void BotonAnimadoA::centrarTexto()
{

    _LabelTexto->setAlignment(Qt::AlignHCenter);
    _LabelTexto->setGeometry((width()-_LabelTexto->width())/2,-4,
                             _LabelTexto->width(),_LabelTexto->height());

}

void BotonAnimadoA::iniciarAnimacion()
{

    //Se crea maquina para que prosese los estados
    crearMaquina();

    //Se crean los estados
    crearEstados();

    //Se agregan los estados a la maquina de estados
    agregarEstados();


    //Se crean conexiones
    crearConexiones();

    //Se crean las transiciones entre los estados
    crearTransiciones();


    /**********************/
    //
    /**********************/

    //Se inicializa la maquina de estados,
    //En el estado estadoAbajoPeq
    maquinaDeEstados->setInitialState(estado1AbajoPeq);
    maquinaDeEstados->start();

}

void BotonAnimadoA::crearMaquina()
{
    /**********************/
    //
    /**********************/

    maquinaDeEstados = new QStateMachine(this);

}


void BotonAnimadoA::crearEstados()
{
    /**********************/
    //
    /**********************/

    estado1AbajoPeq = new QState();
    estado2ArribaGrande = new QState();
    estado3Click = new QState();

}

void BotonAnimadoA::agregarEstados()
{

    /**********************/
    //
    /**********************/

    maquinaDeEstados->addState(estado1AbajoPeq);
    maquinaDeEstados->addState(estado2ArribaGrande);
    maquinaDeEstados->addState(estado3Click);

}

void BotonAnimadoA::crearConexiones()
{
    /**********************/
    //
    /**********************/

    /*Al entrar al estadoestadoAbajoPeq se activa la animación animacionAbajoPeq
      */
    QObject::connect(estado1AbajoPeq, SIGNAL(entered()), this, SLOT(animacionAbajoPeq()));

    /*Al entrar al estadoArribaGrande se activa la animación animacionArribaGrande
      */
    QObject::connect(estado2ArribaGrande, SIGNAL(entered()), this, SLOT(animacionArribaGrande()));


    /*Al entrar al estadoClick se activa la animación
      */
    QObject::connect(estado3Click, SIGNAL(entered()), this, SLOT(animacionClick()));

}

void BotonAnimadoA::crearTransiciones()
{
    /**********************/
    //
    /**********************/

    /*Si se encuentra en el estado "estado1AbajoPeq" y recibe el evento QEvent::MouseButtonPress,
      entonces
      pasar al estado "estado3Click"
    */
    _EnterTransition = new QEventTransition(this, QEvent::MouseButtonPress);
    _EnterTransition->setTargetState(estado3Click);
    estado1AbajoPeq->addTransition(_EnterTransition);

    /*Si se encuentra en el estado "estado1AbajoPeq" y recibe el evento Enter, entonces
      pasar al estado "estado2ArribaGrande"
    */
    _EnterTransition = new QEventTransition(this, QEvent::Enter);
    _EnterTransition->setTargetState(estado2ArribaGrande);
    estado1AbajoPeq->addTransition(_EnterTransition);

    /*Si se encuentra en el estado "estado2ArribaGrande" y recibe el evento Leave, entonces
      pasar al estado "estado1AbajoPeq"
    */
    _LeaveTransition = new QEventTransition(this, QEvent::Leave);
    _LeaveTransition->setTargetState(estado1AbajoPeq);
    estado2ArribaGrande->addTransition(_LeaveTransition);

    /*Si se encuentra en el estado "estado2ArribaGrande" y recibe el evento MouseButtonPress,
      entonces
      pasar al estado "estado3Click"
    */
    _PressTransition = new QEventTransition(this, QEvent::MouseButtonPress);
    _PressTransition->setTargetState(estado3Click);
    estado2ArribaGrande->addTransition(_PressTransition);

    /*Si se encuentra en el estado "estado3Click" y recibe el evento MouseButtonRelease,
      entonces
      pasar al estado "estado1AbajoPeq"
    */
    _ReleaseTransition = new QEventTransition(this, QEvent::MouseButtonRelease);
    _ReleaseTransition->setTargetState(estado1AbajoPeq);
    estado3Click->addTransition(_ReleaseTransition);

    /*Si se encuentra en el estado "estado3Click" y recibe el evento Leave,
      entonces
      pasar al estado "estado1AbajoPeq"
    */
    _ReleaseTransition = new QEventTransition(this, QEvent::Leave);
    _ReleaseTransition->setTargetState(estado1AbajoPeq);
    estado3Click->addTransition(_ReleaseTransition);

}


///***///
//SLOTS
///***///

void BotonAnimadoA::animacionAbajoPeq()
{
    //qDebug() << "Animacion: Disminuye de Tam";

    /**********************/
    //
    /**********************/

    grupoDeAnimaciones = new QParallelAnimationGroup(maquinaDeEstados);

    if (_CambioDePosicion){
        //La propiedad a ser interpolada es la posicion del botón ("pos")
        animacionCambioPosicion = new QPropertyAnimation(this, "pos",grupoDeAnimaciones);
        animacionCambioPosicion->setDuration(_DuracionAnimacion);
        animacionCambioPosicion->setStartValue(QPoint(this->pos()));
        animacionCambioPosicion->setEndValue(QPoint(_PosicionInicialX,_PosicionInicialY
                                                    + _CambioPosicionBoton));

        animacionCambioPosicion->setEasingCurve(_TipoInterpolacion);
        grupoDeAnimaciones->addAnimation(animacionCambioPosicion);

    }

    if (_CambioDeTam)
    {
        //La propiedad a ser interpolada es el Tam del icono del botón ("iconSize")
        animacionCambioTam = new QPropertyAnimation(this, "iconSize",grupoDeAnimaciones);
        animacionCambioTam->setDuration(_DuracionAnimacion);
        animacionCambioTam->setStartValue(this->iconSize());
        animacionCambioTam->setEndValue(QSize(_TamInicialIconoX - _CambioTamIconoX,
                                              _TamIconoInicialY - _CambioTamIconoY));

        //Tipo de interpolación
        animacionCambioTam->setEasingCurve(_TipoInterpolacion);
        grupoDeAnimaciones->addAnimation(animacionCambioTam);

    }

    if (_CambioDeTransparencia)
    {
        animacionCambioTransparencia = new QPropertyAnimation(effect, "opacity",grupoDeAnimaciones);
        animacionCambioTransparencia->setStartValue(effect->opacity());
        animacionCambioTransparencia->setEndValue(0.0);
        animacionCambioTransparencia->setDuration(_DuracionAnimacion);
        animacionCambioTransparencia->setEasingCurve(_TipoInterpolacion);
        grupoDeAnimaciones->addAnimation(animacionCambioTransparencia);

    }

    grupoDeAnimaciones->start(QAbstractAnimation::DeleteWhenStopped);


}


void BotonAnimadoA::animacionArribaGrande()
{

    //qDebug() << "Animacion: Aumenta de Tam";

    grupoDeAnimaciones = new QParallelAnimationGroup(maquinaDeEstados);


    if (_CambioDePosicion){
        //La propiedad a ser interpolada es la posición del botón: "pos"
        animacionCambioPosicion = new QPropertyAnimation(this, "pos",grupoDeAnimaciones);


        animacionCambioPosicion->setDuration(_DuracionAnimacion);
        animacionCambioPosicion->setStartValue(QPoint(this->pos()));
        animacionCambioPosicion->setEndValue(QPoint(_PosicionInicialX,_PosicionInicialY
                                                    - _CambioPosicionBoton));
        //Tipo de interpolación
        animacionCambioPosicion->setEasingCurve(_TipoInterpolacion);

        grupoDeAnimaciones->addAnimation(animacionCambioPosicion);

    }

    if (_CambioDeTam)
    {
        //La propiedad a ser interpolada es el Tam del icono del botón: "iconSize"
        animacionCambioTam = new QPropertyAnimation(this, "iconSize",grupoDeAnimaciones);
        animacionCambioTam->setDuration(_DuracionAnimacion);
        animacionCambioTam->setStartValue(this->iconSize());
        animacionCambioTam->setEndValue(QSize(_TamInicialIconoX,_TamIconoInicialY));

        //Tipo de interpolación
        animacionCambioTam->setEasingCurve(_TipoInterpolacion);

        grupoDeAnimaciones->addAnimation(animacionCambioTam);

    }

    if (_CambioDeTransparencia)
    {
        animacionCambioTransparencia = new QPropertyAnimation(effect, "opacity",grupoDeAnimaciones);
        animacionCambioTransparencia->setStartValue(effect->opacity());
        animacionCambioTransparencia->setEndValue(1.0);
        animacionCambioTransparencia->setDuration(_DuracionAnimacion);
        animacionCambioTransparencia->setEasingCurve(_TipoInterpolacion);
        grupoDeAnimaciones->addAnimation(animacionCambioTransparencia);

    }

    grupoDeAnimaciones->start(QAbstractAnimation::DeleteWhenStopped);

}


void BotonAnimadoA::animacionClick()
{

//    //qDebug() << "Animacion Click";

    //qDebug() << this->pos().x();
    //qDebug() << this->pos().y();



}

void BotonAnimadoA::setID(int pID)
{
    _ID = pID;
}

void BotonAnimadoA::setCambioDePos(bool pCambioPos)
{
    _CambioDePosicion = pCambioPos;
}

void BotonAnimadoA::setCambioDeTam(bool pCambioTam)
{
    _CambioDeTam = pCambioTam;
}

void BotonAnimadoA::setCambioDeTransp(
        bool pCambioTransparencia)
{
    _CambioDeTransparencia = pCambioTransparencia;
}

void BotonAnimadoA::setTipoInterpolacion(QEasingCurve pTipo)
{
    _TipoInterpolacion = pTipo;
}
