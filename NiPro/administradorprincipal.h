#ifndef ADMINISTRADORPRINCIPAL_H
#define ADMINISTRADORPRINCIPAL_H

#include <QObject>
#include <QDebug>

#include "administradorpiezas.h"
#include "administradorxml.h"
#include "piezalogica.h"
#include "subprocesadorimagenes.h"
//#include "mainmanager.h"

class AdministradorPrincipal : public QObject
{
    Q_OBJECT
public:
    explicit AdministradorPrincipal(QObject *parent = 0);
    virtual ~AdministradorPrincipal();
    AdministradorPiezas *_AdministradorPiezas;



private:

    AdministradorXML *_AdministradorXML;
    SubProcesadorImagenes *_SubProcesadorImagenes;

private:
    void inicializarPiezas();

signals:
    void administradorPiezasCreado(AdministradorPiezas *pAdministradorPiezas);

    void nuevaDescripcionFuncion(int pID,
                                 QString pFuncion,
                                 QString pDescripcion);



public slots:
    void actualizarPieza(int pID);
    void guardarXML();
    void agregarPiezaLogica(int pID,
                            int pErodeNumberOfIterations,
                            int pColorDistanceThreshold,
                            int pR,
                            int pG,
                            int pB,
                            QString pFuncion,
                            QString pDescripcion);

};

#endif // ADMINISTRADORPRINCIPAL_H
