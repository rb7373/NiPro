#ifndef PUSHBUTTONPIEZASIMPLE_H
#define PUSHBUTTONPIEZASIMPLE_H

#include <QPushButton>
#include <QDebug>

class PushButtonPiezaSimple : public QPushButton
{
    Q_OBJECT
public:
    explicit PushButtonPiezaSimple(QWidget *parent = 0);
    void setID(int pID);


    
signals:
    void actualizar(int pID);
    
public slots:
    void click();

private:
    int _ID;
};

#endif // PUSHBUTTONPIEZASIMPLE_H
