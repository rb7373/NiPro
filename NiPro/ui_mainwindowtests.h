/********************************************************************************
** Form generated from reading UI file 'mainwindowtests.ui'
**
** Created: Sun Oct 14 22:08:02 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWTESTS_H
#define UI_MAINWINDOWTESTS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowTESTS
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindowTESTS)
    {
        if (MainWindowTESTS->objectName().isEmpty())
            MainWindowTESTS->setObjectName(QString::fromUtf8("MainWindowTESTS"));
        MainWindowTESTS->resize(800, 600);
        centralwidget = new QWidget(MainWindowTESTS);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(170, 120, 126, 36));
        MainWindowTESTS->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindowTESTS);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindowTESTS->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindowTESTS);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindowTESTS->setStatusBar(statusbar);

        retranslateUi(MainWindowTESTS);

        QMetaObject::connectSlotsByName(MainWindowTESTS);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowTESTS)
    {
        MainWindowTESTS->setWindowTitle(QApplication::translate("MainWindowTESTS", "MainWindow", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindowTESTS", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; color:#ff0000;\">TextLabel</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowTESTS: public Ui_MainWindowTESTS {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWTESTS_H
