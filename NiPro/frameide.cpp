#include "frameide.h"
#include "ui_frameide.h"

FrameIDE::FrameIDE(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FrameIDE)
{
    ui->setupUi(this);

    crearObjetos();
    crearBlques();
    iniciarConfiguracionPiezas();

    connect(ui->pushButtonCerrar, SIGNAL(clicked()), this, SLOT(close()));

    connect(ui->pushButtonPlay,SIGNAL(clicked()),this,SLOT(iniciarDebugger()));
    //connect(ui->pushButtonPlay,SIGNAL(clicked()),this,SLOT(mostrarPiezas()));

    QDir::setCurrent(QCoreApplication::applicationDirPath());
    path = QDir::currentPath()+"/proyectos";




}



FrameIDE::~FrameIDE()
{
    qDebug("Liberando memoria IDE");
    delete ui;
}

void FrameIDE::iniciarDebugger()
{
    //obstaclesList->setEnabled(false);
    int id = 0;
    int size = mapWidget->piecePixmaps.size();
    for (int i = 0; i < size; i++)
    {
        id = mapWidget->pieceIDs.at(i);
        if (id == 2)
        {
            mapWidget->piecePixmaps[i] = QPixmap(":/images/icons/set_0/fichas/pieza27.png").scaled(QSize(Constantes::intIconSize, Constantes::intIconSize),Qt::KeepAspectRatio, Qt::SmoothTransformation);
            mapWidget->update(mapWidget->pieceRects.at(i));
        }
//        else if ()
//        {

//        }
//        else if ()
//        {

//        }
//        else if ()
//        {

//        }
//        else if ()
//        {

//        }

    }
}

void FrameIDE::crearObjetos()
{
    obstaclesList = new ObstaclesList(this);
    obstaclesList->move(35,80);
    obstaclesList->setStyleSheet("color:rgb(0,95,114,255); border-radius: 10px; border-style: outset;border-width: 1px; border-color:rgb(0,95,114,255);");

    mapWidget = new MapWidget(this);
    mapWidget->move(200,80);
    mapWidget->setStyleSheet("color:rgb(0,95,114,255); border-radius: 10px; border-style: outset;border-width: 1px; border-color:rgb(0,95,114,255);");

}

void FrameIDE::crearBlques()
{
    obstaclesList->clear();

    for (int i = 0; i < Constants::CANTIDAD_PIEZAS; i++)
    {
        cargarBloque(":/images/icons/set_0/fichas/pieza" + QString::number(i) + ".png", i);
    }

    mapWidget->clear();
}

void FrameIDE::mostrarPiezas()
{

    qDebug() << "-Matriz-";



    int size = mapWidget->pieceIDs.count();
    for (int i = 0; i < size; i++)
    {

        //qDebug() << "ID: " << mapWidget->pieceIDs.at(i);
        int pX;
        int pY;
        pX = mapWidget->pieceRects.at(i).x();
        pY = mapWidget->pieceRects.at(i).y();
        pX = pX/Constantes::sizeSquare;;
        pY = pY/Constantes::sizeSquare;
        //qDebug() << "X: " << pX << " Y: " << pY;

        matrizConfiguacionPiezas[pY][pX] = mapWidget->pieceIDs.at(i);

    }

    QString matriz = "{";
    for (int i = 0;  i < Constants::CANTIDAD_PIEZAS_TABLERO_Y; i++)
    {
        matriz += "\n{";
        for (int j = 0;  j < Constants::CANTIDAD_PIEZAS_TABLERO_X; j++)
        {
            matriz += QString::number(matrizConfiguacionPiezas[i][j]+1);
            if ( j <  Constants::CANTIDAD_PIEZAS_TABLERO_X-1)
            {
                matriz += ",";
            }
        }
        if ( i <  Constants::CANTIDAD_PIEZAS_TABLERO_Y-1)
        {
            matriz += "},";
        }
        else
        {
            matriz += "}";
        }

    }
    matriz += "\n}";
    qDebug() << matriz;
    qDebug() << "FIN de matriz";


}

void  FrameIDE::cargarBloque(QString pRuta, int pId)
{
    QPixmap pieceImage(pRuta);
    pieceImage = pieceImage.scaled(QSize(Constantes::intIconSize*Constantes::FACTOR_CRECIMIENTO,
                                         Constantes::intIconSize*Constantes::FACTOR_CRECIMIENTO),
                                   Qt::KeepAspectRatio, Qt::SmoothTransformation);

    obstaclesList->addPiece(pieceImage, QPoint(0, 0), pId);

}

void FrameIDE::iniciarConfiguracionPiezas()
{
    mapWidget->clear();
    for (int i = 0;  i < Constants::CANTIDAD_PIEZAS_TABLERO_Y; i++)
    {
        for (int j = 0;  j < Constants::CANTIDAD_PIEZAS_TABLERO_X; j++)
        {
            matrizConfiguacionPiezas[i][j] = -1;
            //listaConfiguracionPiezas.append(-1);
        }
    }
}

void FrameIDE::preEstablecerConfiguracionPiezas(QList<int> pLista)
{
    //int numeroLabel = rowR*Constants::CANTIDAD_PIEZAS_TABLERO_X+colR;
    int totalElementos = pLista.size();
    int row = 0;
    int col = 0;
    for (int i = 0; i  < totalElementos; i++)
    {
        int id = pLista.at(i);
        if (id != -1)
        {
            row = i / Constants::CANTIDAD_PIEZAS_TABLERO_X;
            col = i % Constants::CANTIDAD_PIEZAS_TABLERO_X;
            matrizConfiguacionPiezas [row][col] = id;
            mapWidget->agregarNuevaPieza(id, row, col);
        }
    }
}

void FrameIDE::guardar()
{
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         ("Guardar archivo"), path,
                                                         ("txt(*.txt);;All Files(*)"));

    if(nombreArchivo.isEmpty())
        return;

    QFile archivo(nombreArchivo);
    if (archivo.open(QIODevice::WriteOnly|QIODevice::Text))
    {

        archivo.write(matrizToProyecto().toUtf8());
    }

}

void FrameIDE::abrir()
{
    QString nombreArchivo = QFileDialog::getOpenFileName(this,
                                                         ("Abrir archivo"), path,
                                                         ("txt(*.txt);;All Files(*)"));
    if (!nombreArchivo.isEmpty())
    {
        QFile archivo(nombreArchivo);

        if (archivo.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            QString codigo = QString::fromUtf8(archivo.readAll());
            qDebug() << codigo;
            proyectoToMatriz(codigo);
        }
    }

}






void FrameIDE::on_pushButtonPlayAbrir_clicked()
{
    abrir();
    mostrarPiezas();
}

void FrameIDE::on_pushButtonPlayGuardar_released()
{
    guardar();
    mostrarPiezas();
}

QString FrameIDE::matrizToProyecto()
{

    int size = mapWidget->pieceIDs.count();
    for (int i = 0; i < size; i++)
    {
        int pX;
        int pY;
        pX = mapWidget->pieceRects.at(i).x();
        pY = mapWidget->pieceRects.at(i).y();
        pX = pX/Constantes::sizeSquare;;
        pY = pY/Constantes::sizeSquare;
        matrizConfiguacionPiezas[pY][pX] = mapWidget->pieceIDs.at(i);
    }

    QString matriz = "";
    for (int i = 0;  i < Constants::CANTIDAD_PIEZAS_TABLERO_Y; i++)
    {
        //matriz += "\n";
        for (int j = 0;  j < Constants::CANTIDAD_PIEZAS_TABLERO_X; j++)
        {
            matriz += QString::number(matrizConfiguacionPiezas[i][j]);
            if ( j <  Constants::CANTIDAD_PIEZAS_TABLERO_X-1)
            {
                matriz += ",";
            }
        }
        if ( i <  Constants::CANTIDAD_PIEZAS_TABLERO_Y-1)
        {
            matriz += ",";
        }
    }
    //matriz += "\n";

    return matriz;
}

void FrameIDE::limpiarPantalla()
{
    //Cambiar -Solucion rapida- Reiniciar todo
    crearBlques();

    for (int i = 0;  i < Constants::CANTIDAD_PIEZAS_TABLERO_Y; i++)
    {
        for (int j = 0;  j < Constants::CANTIDAD_PIEZAS_TABLERO_X; j++)
        {
            matrizConfiguacionPiezas[i][j] = -1;
        }
    }

}


void FrameIDE::proyectoToMatriz(QString pProyecto)
{
    QList <int> listaIds; //Guarda los ids temporales
    QStringList listaPiezas = pProyecto.split(",", QString::SkipEmptyParts);
    int size   = listaPiezas.size();
    bool ok = false;
    int idInt;
    QString idString;
    for (int i = 0; i < size; i++)
    {
        idString = listaPiezas.at(i);
        idInt = idString.toInt(&ok);

        if (ok)
        {
            listaIds.append(idInt);
            //qDebug() << "i= " << listaIds.at(i);
        }
        else
        {
            return;
        }
    }

    int totalElementos = listaIds.size();

    if (totalElementos == Constants::CANTIDAD_PIEZAS_TABLERO_X*
            Constants::CANTIDAD_PIEZAS_TABLERO_Y)
    {

        limpiarPantalla();

        int row = 0;
        int col = 0;

        for (int i = 0; i  < totalElementos; i++)
        {
            int id = listaIds.at(i);
            if (id != -1)
            {
                row = i / Constants::CANTIDAD_PIEZAS_TABLERO_X;
                col = i % Constants::CANTIDAD_PIEZAS_TABLERO_X;
                matrizConfiguacionPiezas [row][col] = id;
                mapWidget->agregarNuevaPieza(id, row, col);

            }
        }
    }
}

void FrameIDE::on_pushButtonTrash_released()
{
    limpiarPantalla();
}
