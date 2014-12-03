/********************************************************************************
** Form generated from reading UI file 'piezas.ui'
**
** Created: Sun Oct 14 22:08:02 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PIEZAS_H
#define UI_PIEZAS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Piezas
{
public:
    QLabel *labelFondo;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPushButton *pushButtonCerrar;
    QPushButton *pushButtonAnterior;
    QLabel *labelCoordenadas;

    void setupUi(QFrame *Piezas)
    {
        if (Piezas->objectName().isEmpty())
            Piezas->setObjectName(QString::fromUtf8("Piezas"));
        Piezas->resize(1000, 700);
        Piezas->setStyleSheet(QString::fromUtf8("background-color:black;"));
        Piezas->setFrameShape(QFrame::StyledPanel);
        Piezas->setFrameShadow(QFrame::Raised);
        labelFondo = new QLabel(Piezas);
        labelFondo->setObjectName(QString::fromUtf8("labelFondo"));
        labelFondo->setGeometry(QRect(15, 24, 970, 632));
        labelFondo->setPixmap(QPixmap(QString::fromUtf8(":/images/marcos/marco_gris_1.png")));
        labelFondo->setScaledContents(false);
        scrollArea = new QScrollArea(Piezas);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(60, 60, 880, 512));
        scrollArea->setStyleSheet(QString::fromUtf8("color:rgb(0,95,114,255);\n"
"border-radius: 10px;\n"
"border-style: outset;\n"
"border-width: 1px;\n"
"border-color:rgb(0,95,114,255);"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 878, 510));
        scrollArea->setWidget(scrollAreaWidgetContents);
        pushButtonCerrar = new QPushButton(Piezas);
        pushButtonCerrar->setObjectName(QString::fromUtf8("pushButtonCerrar"));
        pushButtonCerrar->setGeometry(QRect(50, 580, 64, 64));
        pushButtonCerrar->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonCerrar->setFocusPolicy(Qt::NoFocus);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icons/set_0/uncheck_1_64x64.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonCerrar->setIcon(icon);
        pushButtonCerrar->setIconSize(QSize(64, 64));
        pushButtonCerrar->setFlat(true);
        pushButtonAnterior = new QPushButton(Piezas);
        pushButtonAnterior->setObjectName(QString::fromUtf8("pushButtonAnterior"));
        pushButtonAnterior->setGeometry(QRect(120, 580, 64, 64));
        pushButtonAnterior->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonAnterior->setFocusPolicy(Qt::NoFocus);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/icons/set_0/Arrow-turn-left-icon_2_128x128.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonAnterior->setIcon(icon1);
        pushButtonAnterior->setIconSize(QSize(64, 64));
        pushButtonAnterior->setFlat(true);
        labelCoordenadas = new QLabel(Piezas);
        labelCoordenadas->setObjectName(QString::fromUtf8("labelCoordenadas"));
        labelCoordenadas->setGeometry(QRect(820, 590, 131, 51));
        labelCoordenadas->setStyleSheet(QString::fromUtf8("background-color: rgba( 255, 255, 255, 0% );\n"
"color:white;\n"
"font: 75 12pt \"Comic Sans MS\";"));
        labelCoordenadas->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        retranslateUi(Piezas);

        QMetaObject::connectSlotsByName(Piezas);
    } // setupUi

    void retranslateUi(QFrame *Piezas)
    {
        Piezas->setWindowTitle(QApplication::translate("Piezas", "Frame", 0, QApplication::UnicodeUTF8));
        labelFondo->setText(QString());
        pushButtonCerrar->setText(QString());
        pushButtonAnterior->setText(QString());
        labelCoordenadas->setText(QApplication::translate("Piezas", "Coor", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Piezas: public Ui_Piezas {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PIEZAS_H
