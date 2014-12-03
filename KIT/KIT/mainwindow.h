#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

#include "constantes.h"
#include "mapwidget.h"
#include "obstacleslist.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void iniciarParametros();
    void crearObjetos();
    void crearBlques();
    void cargarBloque(const QString &pRuta, int pId);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

    //widgets

    QFrame *frame;
    QHBoxLayout *frameLayout;
    ObstaclesList *obstaclesList;
    MapWidget *mapWidget;
    QLabel *label;


private slots:
    void mostrarPiezas();


};

#endif // MAINWINDOW_H
