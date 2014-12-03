#include "administradorxml.h"

AdministradorXML::AdministradorXML(QObject *parent) :
    QObject(parent)
{
    _IsRaizAsignalada = false;
}

AdministradorXML::~AdministradorXML()
{
    qDebug() << "###";
    qDebug() << "Se ha liberado memoria del administrador de XMl";
    qDebug() << "###";
}

bool AdministradorXML::leerArchivo(QString fileName)
{
    //qDebug("Leyendo archivo");
    _RutaArchivo = fileName;
    QFile file(_RutaArchivo);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Error: No se pudo leer el archivo " << _RutaArchivo
                 << ": " << file.errorString();
        return false;
    }
    QString errorStr;
    int errorLine;
    int errorColumn;
    if (!_DocumentoActual.setContent(&file, false, &errorStr, &errorLine,
                                     &errorColumn)) {
        qDebug() << "Error: en la linea " << errorLine << ", "
                 << "columna " << errorColumn << ": "
                 << errorStr;
        return false;
    }
    QDomElement root = _DocumentoActual.documentElement();
    if (root.tagName() != "NiPro") {
        qDebug() << "Error: No es un archivo del proyecto NiPro";
        return false;
    }
    _Root = root;
    _IsRaizAsignalada = true;
    return true;
}

void AdministradorXML::procesarRaiz(const QDomElement &element)
{
    if (_IsRaizAsignalada == true)
    {
        //qDebug("Procesando raiz");
        QDomNode child = element.firstChild();
        if (!child.isNull() && child.toElement().tagName() == "piezas" )
        {
            //qDebug("Procesando nodo piezas");
            child = child.firstChild();
            int numeroPieza = 0;
            while (!child.isNull()) {
                QDomElement piezaTemp = child.toElement();
                //qDebug() <<  "Tag: " << piezaTemp.tagName();
                if (piezaTemp.tagName() == "pieza") {
                    //qDebug() << "Pieza: "<< numeroPieza << " procesada";
                    int erodeNumberOfIterations =
                            (piezaTemp.attribute("erodeNumberOfIterations")).toInt();
                    int colorDistanceThreshold =
                            (piezaTemp.attribute("colorDistanceThreshold").toInt());


                    int r = (piezaTemp.attribute("r").toInt());
                    int g = (piezaTemp.attribute("g").toInt());
                    int b = (piezaTemp.attribute("b").toInt());

                    QString funcion =  piezaTemp.attribute("funcion");
                    QString descripcion =  piezaTemp.attribute("descripcion");

                    //qDebug("emitiendo pieza");

                    emit nuevaPieza(numeroPieza,
                                    erodeNumberOfIterations,
                                    colorDistanceThreshold,
                                    r,
                                    g,
                                    b,
                                    funcion,
                                    descripcion);
                    numeroPieza++;
                }
                child = child.nextSibling();
            }
        }
    }

}

void AdministradorXML::procesarPiezas()
{
    procesarRaiz(_Root);
}

void AdministradorXML::actualizarPiezaLogica(int pId,
                                             int pR,
                                             int pG,
                                             int pB)
{

    actualizarPiezaLogica(pId,
                          Constants::DEFAULT_ERODE_ITERATIONS,
                          Constants::DEFAULT_COLOR_DISTANCE_THRESHOLD,
                          pR,
                          pG,
                          pB);

}

void AdministradorXML::actualizarPiezaLogica(int pID,
                                             int pErodeNumberOfIterations,
                                             int pColorDistanceThreshold,
                                             int pR,
                                             int pG,
                                             int pB)
{
    if (_IsRaizAsignalada == true)
    {
        qDebug() << "###";
        qDebug() << "AdministradorXML";
        qDebug() << "actualizando pieza";
        qDebug() << "###";

        QDomNode child = _Root.firstChild();
        if (!child.isNull() && child.toElement().tagName() == "piezas" )
        {
            qDebug("Procesando nodo piezas");
            child = child.firstChild();
            int numeroPieza = 0;
            while (!child.isNull()) {
                QDomElement piezaTemp = child.toElement();
                //qDebug() <<  "Tag: " << piezaTemp.tagName();
                if (piezaTemp.tagName() == "pieza" && numeroPieza == pID) {
                    //qDebug() << "Pieza: "<< numeroPieza << " proceda";

                    piezaTemp.setAttribute("erodeNumberOfIterations",
                                           pErodeNumberOfIterations);

                    piezaTemp.setAttribute("colorDistanceThreshold",
                                           pColorDistanceThreshold);

                    piezaTemp.setAttribute("r",
                                           pR);

                    piezaTemp.setAttribute("g",
                                           pG);

                    piezaTemp.setAttribute("b",
                                           pB);

                }
                numeroPieza++;
                child = child.nextSibling();
            }
        }
    }

}

void AdministradorXML::guardarXML()
{
    qDebug()  << "INICIA: GUARDADO";
    const int Indent = 4;
    QFile file(_RutaArchivo);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Error: No se pudo leer el archivo " << _RutaArchivo
                 << ": " << file.errorString();
        return;
    }
    QTextStream out(&file);
    //QDomNode xmlNode = _DocumentoActual.createProcessingInstruction("xml",                                               "version=\"1.0\" encoding=\"ISO-8859-1\"");
    //_DocumentoActual.insertBefore(xmlNode, _DocumentoActual.firstChild());
    _DocumentoActual.save(out, Indent);
    file.close();
}




