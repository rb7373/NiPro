#include "botonanimadoabooldosestados.h"

BotonAnimadoABoolDosEstados::BotonAnimadoABoolDosEstados(QWidget *parent) :
    BotonAnimadoA(parent)
{
}

void BotonAnimadoABoolDosEstados::setIconsPath(QString pIconStateSelectedOn,
                                               QString pIconStateSelectedOff)
{

    icon.addFile(pIconStateSelectedOn, QSize(), QIcon::Selected, QIcon::On);
    icon.addFile(pIconStateSelectedOff, QSize(), QIcon::Selected, QIcon::Off);

    setIcon(icon);
    setCheckable(true);
}
