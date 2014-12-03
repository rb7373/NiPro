#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    iniciarParametros();
    crearObjetos();
    crearBlques();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::iniciarParametros()
{
    resize(Constantes::tamXVentana, Constantes::tamYVentana);
    setMinimumSize(Constantes::tamXVentana, Constantes::tamYVentana);
    setMaximumSize(Constantes::tamXVentana, Constantes::tamYVentana);
}

void MainWindow::crearObjetos()
{
    frame = new QFrame(this);
    frameLayout = new QHBoxLayout(frame);

    //label = new QLabel(frame);
    //label->setObjectName(QString::fromUtf8("label"));
    //label->setGeometry(QRect(0, 0, 900, 700));

    //label->setPixmap(QPixmap(QString::fromUtf8(":/recursos/fondoGeneral.png")));

    frame->setStyleSheet("background-color:black;");

    obstaclesList = new ObstaclesList;
    mapWidget = new MapWidget();

    frameLayout->addWidget(obstaclesList);
    frameLayout->addWidget(mapWidget);

    QPushButton *boton = new QPushButton(this);

    connect(boton,SIGNAL(clicked()),this,SLOT(mostrarPiezas()));
    boton->setText("Hola");

    frameLayout->addWidget(boton);

    setCentralWidget(frame);

}

void MainWindow::crearBlques()
{
    obstaclesList->clear();

    for (int i = 0; i < 28; i++)
    {
        cargarBloque(":/recursos/pieza" + QString::number(i)+ ".png", i);
    }

    mapWidget->clear();
}

void  MainWindow::cargarBloque(const QString &pRuta, int pId)
{
    QPixmap pieceImage(pRuta);
    pieceImage = pieceImage.scaled(QSize(Constantes::intIconSize*Constantes::factorCrecimiento,
                                         Constantes::intIconSize*Constantes::factorCrecimiento),
                                   Qt::KeepAspectRatio, Qt::SmoothTransformation);

    obstaclesList->addPiece(pieceImage, QPoint(0, 0), pId);

}

void MainWindow::mostrarPiezas()
{
    int size = mapWidget->pieceIDs.count();
    for (int i = 0; i < size; i++)
    {

        qDebug() << "ID: " << mapWidget->pieceIDs.at(i);
        int pX;
        int pY;
        pX = mapWidget->pieceRects.at(i).x();
        pY = mapWidget->pieceRects.at(i).y();
        pX = pX/Constantes::sizeSquare;;
        pY = pY/Constantes::sizeSquare;
        qDebug() << "X: " << pX << " Y: " << pY;
    }
}



