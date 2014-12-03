#include "mainmanager.h"

// Global static pointer used to ensure a single instance of the class

AdministradorProcesamientoImagenes *AdministradorProcesamientoImagenes::_Singleton = 0;

/* This function is called to create an instance of the class.
   Calling the constructor publicly is not allowed. The constructor
   is private and is only called by this Instance function.
*/

AdministradorProcesamientoImagenes* AdministradorProcesamientoImagenes::getInstance()
{
    // Only allow one instance of class to be generated.
    if (_Singleton == 0)
    {
        _Singleton = new AdministradorProcesamientoImagenes;
        qDebug() << "Se ha creado el ADMINISTRADOR PROCESAMIENTO IMAGENES";
    }
    return _Singleton;
}

AdministradorProcesamientoImagenes* AdministradorProcesamientoImagenes::getInstance(int pTypeMotionDetector)
{
    // Only allow one instance of class to be generated.
    if (_Singleton == 0)
    {
        _Singleton = new AdministradorProcesamientoImagenes;
        qDebug() << "Se ha creado el ADMINISTRADOR PROCESAMIENTO IMAGENES";
    }



    return _Singleton;
}


// Releases the singleton instance of this controller.
void AdministradorProcesamientoImagenes::destroy() {
    if (_Singleton != 0) {
        delete _Singleton;
        _Singleton= 0;
    }
}


AdministradorProcesamientoImagenes::~AdministradorProcesamientoImagenes()
{
    qDebug() << "Se ha destruido el administrador de imagenes";

    // Release the sub-administrators memory

}


AdministradorProcesamientoImagenes::AdministradorProcesamientoImagenes(QObject *parent) :
    QObject(parent)
{


}

AdministradorProcesamientoImagenes::AdministradorProcesamientoImagenes(int pTypeMotionDetector, QObject *parent) :
    QObject(parent)
{
    //Creating sub-administrators


}

void AdministradorProcesamientoImagenes::mostrarEstado()
{
    qDebug() << "Administrador Imagenes Activo";

}

void AdministradorProcesamientoImagenes::asignarAdministradorPiezas(AdministradorPiezas
                                                                    *pAdministrador)
{

    _AdminstradorPiezas = pAdministrador;

}

const PiezaLogica* AdministradorProcesamientoImagenes::at(int pIndex)
{
    return _AdminstradorPiezas->at(pIndex);
}


