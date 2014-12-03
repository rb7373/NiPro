#ifndef BOTONANIMADOABOOLDOSESTADOS_H
#define BOTONANIMADOABOOLDOSESTADOS_H

#include "botonanimadoa.h"
#include "QString"

class BotonAnimadoABoolDosEstados : public BotonAnimadoA
{
    Q_OBJECT
public:
    explicit BotonAnimadoABoolDosEstados(QWidget *parent = 0);
    void setIconsPath(QString pIconStateSelectedOn,
                      QString pIconStateSelectedOff);

    
signals:
    
public slots:

private:
    QIcon icon;
    
};

#endif // BOTONANIMADOABOOLDOSESTADOS_H
