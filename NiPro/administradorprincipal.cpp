#include "administradorprincipal.h"

AdministradorPrincipal::AdministradorPrincipal(QObject *parent) :
    QObject(parent)
{
    _AdministradorXML = new AdministradorXML(this);
    _AdministradorPiezas = new AdministradorPiezas(this);
    //AdministradorProcesamientoImagenes::getInstance()->asignarAdministradorPiezas(_AdministradorPiezas);

    _SubProcesadorImagenes = new SubProcesadorImagenes();
    connect(_AdministradorXML,SIGNAL(nuevaPieza(int,int,int,int,int,int,QString,QString)),
            this,SLOT(agregarPiezaLogica(int,int,int,int,int,int,QString,QString)));


    inicializarPiezas();
}

AdministradorPrincipal::~AdministradorPrincipal()
{
    qDebug() << "###";
    qDebug() << "Se ha liberado memoria del administrador de Principal";
    qDebug() << "###";
}

void AdministradorPrincipal::inicializarPiezas()
{
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    QString rutaArchivo = QDir::currentPath()+"/parametros/settings.xml";
    _AdministradorXML->leerArchivo(rutaArchivo);
    _AdministradorXML->procesarPiezas();
}

void AdministradorPrincipal::actualizarPieza(int pID)
{

    _SubProcesadorImagenes->obtenerColoresPrincipales(pID);

    int r = _SubProcesadorImagenes->getColorR();
    int g = _SubProcesadorImagenes->getColorG();
    int b = _SubProcesadorImagenes->getColorB();

    _AdministradorPiezas->actualizarPiezaLogica(pID,
                                                r,
                                                g,
                                                b);

    _AdministradorXML->actualizarPiezaLogica(pID,
                                             r,
                                             g,
                                             b);





    //        _AdministradorXML->actualizarPiezaLogica(pID);

    //        _AdministradorPiezas->actualizarPiezaLogica(pID);
}

void AdministradorPrincipal::agregarPiezaLogica(int pID,
                                                int pErodeNumberOfIterations,
                                                int pColorDistanceThreshold,
                                                int pR,
                                                int pG,
                                                int pB,
                                                QString pFuncion,
                                                QString pDescripcion)
{

    _AdministradorPiezas->agregarPiezaLogica(pID,
                                             pErodeNumberOfIterations,
                                             pColorDistanceThreshold,
                                             pR,
                                             pG,
                                             pB);

    emit nuevaDescripcionFuncion(pID,
                                 pFuncion,
                                 pDescripcion);
}

void AdministradorPrincipal::guardarXML()
{
    qDebug() << "###";
    qDebug() << "Guardando XML";
    qDebug() << "###";

    _AdministradorXML->guardarXML();
}


