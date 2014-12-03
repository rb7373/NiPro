#ifndef BOTONANIMADOA_H
#define BOTONANIMADOA_H

#include <QStateMachine>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QEventTransition>
#include <QPushButton>
#include <QDebug>
#include <QLabel>
#include <QGraphicsOpacityEffect>

#include "constants.h"

class BotonAnimadoA : public QPushButton
{
    Q_OBJECT
public:
    explicit BotonAnimadoA(QWidget *parent = 0);
    void iniciarAnimacion();
    void crearMaquina();
    void crearEstados();
    void crearConexiones();
    void crearTransiciones();
    void agregarEstados();
    void setDuracionAnimacion(int pDuracion);
    void setCambioTamXY(int pCambioX,int pCambioY);
    void setTamIconoXY(int pTamX,int pTamY);
    void setCambioPosicion(int pCambio);
    void setPosicionInicialXY(int pPosX, int pPosY);
    void setTexto(QString pTexto);
    void centrarTexto();
    void setID(int pID);

    void setCambioDeTam(bool pCambio);
    void setCambioDePos(bool pCambioPos);
    void setCambioDeTransp(bool pCambioTransparencia);
    void setTipoInterpolacion(QEasingCurve pTipo);

    
signals:
    
public slots:
    //Animaciones
    void animacionAbajoPeq();
    void animacionArribaGrande();
    void animacionClick();

private:
    QStateMachine *maquinaDeEstados;
    QParallelAnimationGroup *grupoDeAnimaciones;
    QPropertyAnimation *animacionCambioPosicion;
    QPropertyAnimation *animacionCambioTam;
    QPropertyAnimation *animacionCambioTransparencia;
    QGraphicsOpacityEffect *effect;
    QState *estado1AbajoPeq;
    QState *estado2ArribaGrande;
    QState *estado3Click;
    QEventTransition *_EnterTransition;
    QEventTransition *_LeaveTransition;
    QEventTransition *_PressTransition;
    QEventTransition *_ReleaseTransition;
    QLabel *_LabelTexto;


    int  _DuracionAnimacion;

    int  _CambioTamIconoX;
    int  _CambioTamIconoY;

    int  _TamInicialIconoX;
    int  _TamIconoInicialY;

    int  _CambioPosicionBoton;

    int  _PosicionInicialX;
    int  _PosicionInicialY;
    int _ID;

    bool _CambioDePosicion;
    bool _CambioDeTam;
    bool _CambioDeTransparencia;

    QEasingCurve _TipoInterpolacion;
    
};

#endif // BOTONANIMADOA_H
