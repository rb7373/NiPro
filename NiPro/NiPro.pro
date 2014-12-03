#-------------------------------------------------
#
# Project created by QtCreator 2012-04-20T23:05:55
#
#-------------------------------------------------

QT       += core gui
QT       += xml

QT += widgets

TARGET = NiPro
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    constantes.cpp \
    botonanimadoabooldosestados.cpp \
    botonanimadoa.cpp \
    constants.cpp \
    mainwindowtests.cpp \
    piezas.cpp \
    pieza.cpp \
    processingthread.cpp \
    mattoqimage.cpp \
    framelabel.cpp \
    controller.cpp \
    colorhistogram.cpp \
    colordetector.cpp \
    capturethread.cpp \
    imagebuffer.cpp \
    pruebasfichas.cpp \
    subprocesadorimagenes.cpp \
    administradorxml.cpp \
    administradorpiezas.cpp \
    piezalogica.cpp \
    administradorprincipal.cpp \
    mainmanager.cpp \
    pushbuttonpiezasimple.cpp \
    piezathreadprocesamiento.cpp \
    frametablero.cpp \
    frameide.cpp \
    obstacleslist.cpp \
    mapwidget.cpp

HEADERS  += mainwindow.h \
    constantes.h \
    botonanimadoabooldosestados.h \
    botonanimadoa.h \
    constants.h \
    mainwindowtests.h \
    piezas.h \
    pieza.h \
    processingthread.h \
    mattoqimage.h \
    framelabel.h \
    controller.h \
    colorhistogram.h \
    colordetector.h \
    capturethread.h \
    Structures.h \
    imagebuffer.h \
    pruebasfichas.h \
    subprocesadorimagenes.h \
    objectFinder.h \
    administradorxml.h \
    administradorpiezas.h \
    piezalogica.h \
    administradorprincipal.h \
    mainmanager.h \
    pushbuttonpiezasimple.h \
    piezathreadprocesamiento.h \
    frametablero.h \
    frameide.h \
    obstacleslist.h \
    mapwidget.h

FORMS    += mainwindow.ui \
    mainwindowtests.ui \
    piezas.ui \
    pieza.ui \
    pruebasfichas.ui \
    frametablero.ui \
    frameide.ui



#Para el icono
RC_FILE = myapp.rc

#imporatacion de bibliotecas para windows
win32 {

INCLUDEPATH += C:\\opencv2.3.1\\install\\include

LIBS += -LC:\\opencv2.3.1\\install\lib \
    -lopencv_calib3d231.dll \
    -lopencv_features2d231.dll \
    -lopencv_flann231.dll \
    -lopencv_imgproc231.dll \
    -lopencv_core231.dll \
    -lopencv_highgui231.dll \


}

unix {

#pkg-config --cflags opencv
INCLUDEPATH += /usr/local/include/opencv -I/usr/local/include
#pkg-config --libs opencv
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann

}

RESOURCES += \
    recursos.qrc
