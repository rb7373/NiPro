#include "pushbuttonpiezasimple.h"

PushButtonPiezaSimple::PushButtonPiezaSimple(QWidget *parent) :
    QPushButton(parent)
{
    connect(this,SIGNAL(clicked()),this,SLOT(click()));
}

void PushButtonPiezaSimple::setID(int pID)
{
    _ID = pID;

}

void PushButtonPiezaSimple::click()
{
    emit actualizar(_ID);
    //qDebug("CLICK");
}
