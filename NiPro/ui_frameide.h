/********************************************************************************
** Form generated from reading UI file 'frameide.ui'
**
** Created: Sun Oct 14 22:08:02 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRAMEIDE_H
#define UI_FRAMEIDE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_FrameIDE
{
public:
    QPushButton *pushButtonStop;
    QPushButton *pushButtonPlay;
    QPushButton *pushButtonCerrar;
    QPushButton *pushButtonPause;
    QPushButton *pushButtonPlayAbrir;
    QPushButton *pushButtonPlayGuardar;
    QPushButton *pushButtonTrash;

    void setupUi(QFrame *FrameIDE)
    {
        if (FrameIDE->objectName().isEmpty())
            FrameIDE->setObjectName(QString::fromUtf8("FrameIDE"));
        FrameIDE->resize(1000, 700);
        FrameIDE->setStyleSheet(QString::fromUtf8("background-color:black;"));
        FrameIDE->setFrameShape(QFrame::StyledPanel);
        FrameIDE->setFrameShadow(QFrame::Raised);
        pushButtonStop = new QPushButton(FrameIDE);
        pushButtonStop->setObjectName(QString::fromUtf8("pushButtonStop"));
        pushButtonStop->setEnabled(false);
        pushButtonStop->setGeometry(QRect(280, 610, 64, 64));
        pushButtonStop->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonStop->setFocusPolicy(Qt::NoFocus);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icons/set_0/stop_1_128x128.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonStop->setIcon(icon);
        pushButtonStop->setIconSize(QSize(64, 64));
        pushButtonStop->setFlat(true);
        pushButtonPlay = new QPushButton(FrameIDE);
        pushButtonPlay->setObjectName(QString::fromUtf8("pushButtonPlay"));
        pushButtonPlay->setGeometry(QRect(120, 610, 64, 64));
        pushButtonPlay->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonPlay->setFocusPolicy(Qt::NoFocus);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/icons/set_0/play_1_128x128.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonPlay->setIcon(icon1);
        pushButtonPlay->setIconSize(QSize(64, 64));
        pushButtonPlay->setFlat(true);
        pushButtonCerrar = new QPushButton(FrameIDE);
        pushButtonCerrar->setObjectName(QString::fromUtf8("pushButtonCerrar"));
        pushButtonCerrar->setGeometry(QRect(30, 610, 64, 64));
        pushButtonCerrar->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonCerrar->setFocusPolicy(Qt::NoFocus);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/icons/set_0/uncheck_1_64x64.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonCerrar->setIcon(icon2);
        pushButtonCerrar->setIconSize(QSize(64, 64));
        pushButtonCerrar->setFlat(true);
        pushButtonPause = new QPushButton(FrameIDE);
        pushButtonPause->setObjectName(QString::fromUtf8("pushButtonPause"));
        pushButtonPause->setEnabled(false);
        pushButtonPause->setGeometry(QRect(200, 610, 64, 64));
        pushButtonPause->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonPause->setFocusPolicy(Qt::NoFocus);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/icons/set_0/pause_1_128x128.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonPause->setIcon(icon3);
        pushButtonPause->setIconSize(QSize(64, 64));
        pushButtonPause->setFlat(true);
        pushButtonPlayAbrir = new QPushButton(FrameIDE);
        pushButtonPlayAbrir->setObjectName(QString::fromUtf8("pushButtonPlayAbrir"));
        pushButtonPlayAbrir->setGeometry(QRect(360, 610, 64, 64));
        pushButtonPlayAbrir->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonPlayAbrir->setFocusPolicy(Qt::NoFocus);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/icons/set_0/load_1_128x128.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonPlayAbrir->setIcon(icon4);
        pushButtonPlayAbrir->setIconSize(QSize(64, 64));
        pushButtonPlayAbrir->setFlat(true);
        pushButtonPlayGuardar = new QPushButton(FrameIDE);
        pushButtonPlayGuardar->setObjectName(QString::fromUtf8("pushButtonPlayGuardar"));
        pushButtonPlayGuardar->setGeometry(QRect(440, 610, 64, 64));
        pushButtonPlayGuardar->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonPlayGuardar->setFocusPolicy(Qt::NoFocus);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/icons/set_0/save_1_128x128.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonPlayGuardar->setIcon(icon5);
        pushButtonPlayGuardar->setIconSize(QSize(64, 64));
        pushButtonPlayGuardar->setFlat(true);
        pushButtonTrash = new QPushButton(FrameIDE);
        pushButtonTrash->setObjectName(QString::fromUtf8("pushButtonTrash"));
        pushButtonTrash->setGeometry(QRect(520, 610, 64, 64));
        pushButtonTrash->setCursor(QCursor(Qt::PointingHandCursor));
        pushButtonTrash->setFocusPolicy(Qt::NoFocus);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/icons/set_0/trash_1_256x256.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButtonTrash->setIcon(icon6);
        pushButtonTrash->setIconSize(QSize(64, 64));
        pushButtonTrash->setFlat(true);

        retranslateUi(FrameIDE);

        QMetaObject::connectSlotsByName(FrameIDE);
    } // setupUi

    void retranslateUi(QFrame *FrameIDE)
    {
        FrameIDE->setWindowTitle(QApplication::translate("FrameIDE", "Frame", 0, QApplication::UnicodeUTF8));
        pushButtonStop->setText(QString());
        pushButtonPlay->setText(QString());
        pushButtonCerrar->setText(QString());
        pushButtonPause->setText(QString());
        pushButtonPlayAbrir->setText(QString());
        pushButtonPlayGuardar->setText(QString());
        pushButtonTrash->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FrameIDE: public Ui_FrameIDE {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRAMEIDE_H
