/********************************************************************************
** Form generated from reading UI file 'frametablero.ui'
**
** Created: Sun Oct 14 22:08:02 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRAMETABLERO_H
#define UI_FRAMETABLERO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_FrameTablero
{
public:
    QPushButton *pushButtonCerrar;
    QPushButton *pushButtonPlay;
    QPushButton *pushButtonPause;
    QPushButton *pushButtonStop;
    QPushButton *pushButtonUpdate;

    void setupUi(QFrame *FrameTablero)
    {
        if (FrameTablero->objectName().isEmpty())
            FrameTablero->setObjectName(QString::fromUtf8("FrameTablero"));
        FrameTablero->resize(1000, 700);
        FrameTablero->setStyleSheet(QString::fromUtf8("background-color:black;"));
        FrameTablero->setFrameShape(QFrame::StyledPanel);
        FrameTablero->setFrameShadow(QFrame::Raised);
        pushButtonCerrar = new QPushButton(FrameTablero);
        pushButtonCerrar->setObjectName(QString::fromUtf8("pushButtonCerrar"));
        pushButtonCerrar->setGeometry(QRect(30, 610, 64, 64));
        pushButtonCerrar->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonCerrar->setFocusPolicy(Qt::NoFocus);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icons/set_0/uncheck_1_64x64.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonCerrar->setIcon(icon);
        pushButtonCerrar->setIconSize(QSize(64, 64));
        pushButtonCerrar->setFlat(true);
        pushButtonPlay = new QPushButton(FrameTablero);
        pushButtonPlay->setObjectName(QString::fromUtf8("pushButtonPlay"));
        pushButtonPlay->setGeometry(QRect(120, 610, 64, 64));
        pushButtonPlay->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonPlay->setFocusPolicy(Qt::NoFocus);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/icons/set_0/play_1_128x128.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonPlay->setIcon(icon1);
        pushButtonPlay->setIconSize(QSize(64, 64));
        pushButtonPlay->setFlat(true);
        pushButtonPause = new QPushButton(FrameTablero);
        pushButtonPause->setObjectName(QString::fromUtf8("pushButtonPause"));
        pushButtonPause->setEnabled(false);
        pushButtonPause->setGeometry(QRect(200, 610, 64, 64));
        pushButtonPause->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonPause->setFocusPolicy(Qt::NoFocus);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/icons/set_0/pause_1_128x128.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonPause->setIcon(icon2);
        pushButtonPause->setIconSize(QSize(64, 64));
        pushButtonPause->setFlat(true);
        pushButtonStop = new QPushButton(FrameTablero);
        pushButtonStop->setObjectName(QString::fromUtf8("pushButtonStop"));
        pushButtonStop->setEnabled(false);
        pushButtonStop->setGeometry(QRect(280, 610, 64, 64));
        pushButtonStop->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonStop->setFocusPolicy(Qt::NoFocus);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/icons/set_0/stop_1_128x128.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonStop->setIcon(icon3);
        pushButtonStop->setIconSize(QSize(64, 64));
        pushButtonStop->setFlat(true);
        pushButtonUpdate = new QPushButton(FrameTablero);
        pushButtonUpdate->setObjectName(QString::fromUtf8("pushButtonUpdate"));
        pushButtonUpdate->setGeometry(QRect(360, 610, 64, 64));
        pushButtonUpdate->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonUpdate->setFocusPolicy(Qt::NoFocus);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/icons/set_0/update_1_128x128.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonUpdate->setIcon(icon4);
        pushButtonUpdate->setIconSize(QSize(64, 64));
        pushButtonUpdate->setFlat(true);

        retranslateUi(FrameTablero);

        QMetaObject::connectSlotsByName(FrameTablero);
    } // setupUi

    void retranslateUi(QFrame *FrameTablero)
    {
        FrameTablero->setWindowTitle(QApplication::translate("FrameTablero", "Frame", 0, QApplication::UnicodeUTF8));
        pushButtonCerrar->setText(QString());
        pushButtonPlay->setText(QString());
        pushButtonPause->setText(QString());
        pushButtonStop->setText(QString());
        pushButtonUpdate->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FrameTablero: public Ui_FrameTablero {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRAMETABLERO_H
