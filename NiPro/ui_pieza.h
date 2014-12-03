/********************************************************************************
** Form generated from reading UI file 'pieza.ui'
**
** Created: Sun Oct 14 22:08:02 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PIEZA_H
#define UI_PIEZA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pieza
{
public:
    QLabel *labelDescripcion;

    void setupUi(QWidget *pieza)
    {
        if (pieza->objectName().isEmpty())
            pieza->setObjectName(QString::fromUtf8("pieza"));
        pieza->resize(850, 256);
        pieza->setStyleSheet(QString::fromUtf8("background-color:black;"));
        labelDescripcion = new QLabel(pieza);
        labelDescripcion->setObjectName(QString::fromUtf8("labelDescripcion"));
        labelDescripcion->setGeometry(QRect(502, 20, 328, 216));
        labelDescripcion->setStyleSheet(QString::fromUtf8("background-color:rgb(89,41,93,193);\n"
"border-style: ridge;\n"
"border-width: 4px;\n"
"border-radius: 10px;\n"
"border-color: rgb(89,41,93,193);\n"
"font: 75 14pt \"Comic Sans MS\";\n"
"color: white;\n"
"padding: 6px; \n"
""));

        retranslateUi(pieza);

        QMetaObject::connectSlotsByName(pieza);
    } // setupUi

    void retranslateUi(QWidget *pieza)
    {
        pieza->setWindowTitle(QApplication::translate("pieza", "Form", 0, QApplication::UnicodeUTF8));
        labelDescripcion->setText(QApplication::translate("pieza", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Comic Sans MS'; font-size:14pt; font-weight:72; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class pieza: public Ui_pieza {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PIEZA_H
