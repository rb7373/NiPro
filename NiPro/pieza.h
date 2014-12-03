#ifndef PIEZA_H
#define PIEZA_H

#include <QWidget>
#include <QVBoxLayout>

#include "botonanimadoa.h"
#include "constants.h"
#include "constantes.h"


namespace Ui {
class pieza;
}

class Pieza : public QWidget
{
    Q_OBJECT
    
public:
    explicit Pieza(QString pRutaImagenDefecto,
                   QString pRutaImagenPersonalizada,
                   int pID,
                   QWidget *parent = 0);
    void crearObjetos();
    void setDescripcion(QString pDescripcion);
    void actualizarImagen(QString pRutaIconoPersonalizado);
    void actualizarDescripcionFuncion(QString pFuncion,
                                      QString pDescripcion);

    ~Pieza();

private slots:
    void slotCambiarPieza();


signals:
    void signalCambiarPieza(int pID);


    
private:
    Ui::pieza *ui;
    int _ID;

    //botones
    BotonAnimadoA *_PushButtonImagenDigital;

    //botones
    BotonAnimadoA *_PushButtonImagenPersonalizada;
    BotonAnimadoA *_BottunTakePhoto;

    QString _Texto;

    QString _RutaImagenDefecto;
    QString _RutaImagenPersonalizada;
    int _FactorEscala;
    int _FactorCambio;

};

#endif // PIEZA_H
