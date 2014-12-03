/********************************************************************************
** Form generated from reading UI file 'pruebasfichas.ui'
**
** Created: Sun Oct 14 22:08:02 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRUEBASFICHAS_H
#define UI_PRUEBASFICHAS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSlider>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PruebasFichas
{
public:
    QLabel *labelWebcamIcon;
    QPushButton *pushButtonCerrar;
    QLabel *labelFondo;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QSlider *horizontalSliderDistanceThreshold;
    QSlider *horizontalSliderErodeNumber;
    QPushButton *pushButtonDistanceThreshold;
    QPushButton *pushButtonErodeNumber;
    QPushButton *pushButtonPiezaActual;

    void setupUi(QFrame *PruebasFichas)
    {
        if (PruebasFichas->objectName().isEmpty())
            PruebasFichas->setObjectName(QString::fromUtf8("PruebasFichas"));
        PruebasFichas->resize(1000, 700);
        PruebasFichas->setStyleSheet(QString::fromUtf8("background-color:black;"));
        PruebasFichas->setFrameShape(QFrame::StyledPanel);
        PruebasFichas->setFrameShadow(QFrame::Raised);
        labelWebcamIcon = new QLabel(PruebasFichas);
        labelWebcamIcon->setObjectName(QString::fromUtf8("labelWebcamIcon"));
        labelWebcamIcon->setGeometry(QRect(90, 80, 128, 128));
        labelWebcamIcon->setMinimumSize(QSize(128, 0));
        labelWebcamIcon->setStyleSheet(QString::fromUtf8("background-color: rgba( 255, 255, 255, 0% );"));
        labelWebcamIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/icons/set_0/webcam_1_128x128.png")));
        labelWebcamIcon->setScaledContents(false);
        pushButtonCerrar = new QPushButton(PruebasFichas);
        pushButtonCerrar->setObjectName(QString::fromUtf8("pushButtonCerrar"));
        pushButtonCerrar->setGeometry(QRect(50, 580, 64, 64));
        pushButtonCerrar->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonCerrar->setFocusPolicy(Qt::NoFocus);
        pushButtonCerrar->setStyleSheet(QString::fromUtf8("background-color: rgba( 255, 255, 255, 0% );"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icons/set_0/uncheck_1_64x64.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonCerrar->setIcon(icon);
        pushButtonCerrar->setIconSize(QSize(64, 64));
        pushButtonCerrar->setFlat(true);
        labelFondo = new QLabel(PruebasFichas);
        labelFondo->setObjectName(QString::fromUtf8("labelFondo"));
        labelFondo->setGeometry(QRect(15, 24, 970, 632));
        labelFondo->setPixmap(QPixmap(QString::fromUtf8(":/images/marcos/marco_gris_1.png")));
        labelFondo->setScaledContents(false);
        scrollArea = new QScrollArea(PruebasFichas);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(75, 280, 170, 150));
        scrollArea->setStyleSheet(QString::fromUtf8("color:rgb(0,95,114,255);\n"
"border-radius: 10px;\n"
"border-style: outset;\n"
"border-width: 1px;\n"
"border-color:rgb(0,95,114,255);\n"
""));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 168, 148));
        scrollArea->setWidget(scrollAreaWidgetContents_2);
        horizontalSliderDistanceThreshold = new QSlider(PruebasFichas);
        horizontalSliderDistanceThreshold->setObjectName(QString::fromUtf8("horizontalSliderDistanceThreshold"));
        horizontalSliderDistanceThreshold->setGeometry(QRect(300, 602, 160, 20));
        horizontalSliderDistanceThreshold->setValue(38);
        horizontalSliderDistanceThreshold->setOrientation(Qt::Horizontal);
        horizontalSliderErodeNumber = new QSlider(PruebasFichas);
        horizontalSliderErodeNumber->setObjectName(QString::fromUtf8("horizontalSliderErodeNumber"));
        horizontalSliderErodeNumber->setGeometry(QRect(650, 602, 160, 20));
        horizontalSliderErodeNumber->setValue(1);
        horizontalSliderErodeNumber->setOrientation(Qt::Horizontal);
        pushButtonDistanceThreshold = new QPushButton(PruebasFichas);
        pushButtonDistanceThreshold->setObjectName(QString::fromUtf8("pushButtonDistanceThreshold"));
        pushButtonDistanceThreshold->setGeometry(QRect(190, 570, 98, 94));
        pushButtonDistanceThreshold->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonDistanceThreshold->setFocusPolicy(Qt::NoFocus);
        pushButtonDistanceThreshold->setStyleSheet(QString::fromUtf8("background-color: rgba( 255, 255, 255, 0% );"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/icons/set_0/configurar_color_3_128x128.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonDistanceThreshold->setIcon(icon1);
        pushButtonDistanceThreshold->setIconSize(QSize(83, 83));
        pushButtonDistanceThreshold->setFlat(true);
        pushButtonErodeNumber = new QPushButton(PruebasFichas);
        pushButtonErodeNumber->setObjectName(QString::fromUtf8("pushButtonErodeNumber"));
        pushButtonErodeNumber->setGeometry(QRect(550, 570, 85, 81));
        pushButtonErodeNumber->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonErodeNumber->setFocusPolicy(Qt::NoFocus);
        pushButtonErodeNumber->setStyleSheet(QString::fromUtf8("background-color: rgba( 255, 255, 255, 0% );"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/icons/set_0/configurar_color_2.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonErodeNumber->setIcon(icon2);
        pushButtonErodeNumber->setIconSize(QSize(70, 70));
        pushButtonErodeNumber->setFlat(true);
        pushButtonPiezaActual = new QPushButton(PruebasFichas);
        pushButtonPiezaActual->setObjectName(QString::fromUtf8("pushButtonPiezaActual"));
        pushButtonPiezaActual->setGeometry(QRect(850, 580, 98, 94));
        pushButtonPiezaActual->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonPiezaActual->setFocusPolicy(Qt::NoFocus);
        pushButtonPiezaActual->setStyleSheet(QString::fromUtf8("background-color: rgba( 255, 255, 255, 0% );"));
        pushButtonPiezaActual->setIcon(icon1);
        pushButtonPiezaActual->setIconSize(QSize(83, 83));
        pushButtonPiezaActual->setFlat(true);
        labelFondo->raise();
        labelWebcamIcon->raise();
        pushButtonCerrar->raise();
        scrollArea->raise();
        horizontalSliderDistanceThreshold->raise();
        horizontalSliderErodeNumber->raise();
        pushButtonDistanceThreshold->raise();
        pushButtonErodeNumber->raise();
        pushButtonPiezaActual->raise();

        retranslateUi(PruebasFichas);

        QMetaObject::connectSlotsByName(PruebasFichas);
    } // setupUi

    void retranslateUi(QFrame *PruebasFichas)
    {
        PruebasFichas->setWindowTitle(QApplication::translate("PruebasFichas", "Frame", 0, QApplication::UnicodeUTF8));
        labelWebcamIcon->setText(QString());
        pushButtonCerrar->setText(QString());
        labelFondo->setText(QString());
        pushButtonDistanceThreshold->setText(QString());
        pushButtonErodeNumber->setText(QString());
        pushButtonPiezaActual->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PruebasFichas: public Ui_PruebasFichas {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRUEBASFICHAS_H
