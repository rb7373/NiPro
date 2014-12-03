
#include <QGuiApplication>

#include "mainwindow.h"

#include "mainwindowtests.h"
#include "piezas.h"
#include "pieza.h"
#include "pruebasfichas.h"

#include "subprocesadorimagenes.h"

#include "frametablero.h"
#include "frameide.h"

#include <QtGlobal>


int main(int argc, char *argv[])
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    QApplication a(argc, argv);


    MainWindow w;
    w.showMaximized();
    //w.showFullScreen();

//    FrameIDE IDE;
//    IDE.show();

    //    FrameTablero tablero;
    //    tablero.show();



    //       Piezas piezas;
    //       piezas.show();


    //    Pieza pieza(":/images/icons/set_0/tubo-celeste-vertical-1.png",
    //                ":/images/icons/set_0/tubo-celeste-vertical-1.png");
    //    pieza.show();
    //    PruebasFichas pruebas;
    //    pruebas.show();

    //        SubProcesadorImagenes A;
    //        A.obtenerColoresPrincipales();

    
    return a.exec();
}
