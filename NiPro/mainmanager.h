#ifndef MAINMANAGER_H
#define MAINMANAGER_H

#include <QDebug>
#include <QObject>

#include "administradorpiezas.h"


//class QThread;

class AdministradorProcesamientoImagenes : public QObject
{
    Q_OBJECT

public:

    // Gets access to Singleton instance
    static AdministradorProcesamientoImagenes *getInstance();

    // Gets access to Singleton instance
    static AdministradorProcesamientoImagenes *getInstance(int pTypeMotionDetector);

    static void destroy();

    //To show Sub-administrators State
    void mostrarEstado();

    void asignarAdministradorPiezas(AdministradorPiezas
                                    *pAdministrador);


    const PiezaLogica* at(int pIndex);

private:

    // The constructor is private to avoid the construction
    // additional class
    AdministradorProcesamientoImagenes(QObject *parent = 0);

    AdministradorProcesamientoImagenes(int pTypeMotionDetector, QObject *parent);

    // Destructor
    virtual ~AdministradorProcesamientoImagenes();

    // Pointer to the singleton
    static AdministradorProcesamientoImagenes *_Singleton;

    //Sub-administrator
    AdministradorPiezas *_AdminstradorPiezas;



};

#endif // MAINMANAGER_H
