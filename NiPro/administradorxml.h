#ifndef ADMINISTRADORXML_H
#define ADMINISTRADORXML_H

#include <QObject>
#include <QDebug>
#include <QDomDocument>
#include <QFile>
#include "constants.h"


class AdministradorXML : public QObject
{
    Q_OBJECT
public:
    explicit AdministradorXML(QObject *parent = 0);
    virtual ~AdministradorXML();

    //Una pieza ya existente se le modifican los parametros
    void actualizarPiezaLogica(int pId,
                               int pR,
                               int pG,
                               int pB);

    //Una pieza ya existente se le modifican los parametros
    void actualizarPiezaLogica(int pID,
                               int pErodeNumberOfIterations,
                               int pColorDistanceThreshold,
                               int pR,
                               int pG,
                               int pB);

    void guardarXML();

private:
    QDomDocument _DocumentoActual;
    QDomElement _Root;
    QString _RutaArchivo;
    bool _IsRaizAsignalada;

public:
    bool leerArchivo(QString fileName);
    void procesarPiezas();

private:
    void procesarRaiz(const QDomElement &element);

signals:
    //Emite que se ha encontrado una nueva pieza
    void nuevaPieza(int pID,
                    int pErodeNumberOfIterations,
                    int pColorDistanceThreshold,
                    int pR,
                    int pG,
                    int pB,
                    QString pFuncion,
                    QString pDescripcion);
    
public slots:

};

#endif // ADMINISTRADORXML_H
