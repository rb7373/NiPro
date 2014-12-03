#ifndef FRAMEIDE_H
#define FRAMEIDE_H

#include <QFrame>
#include <QPushButton>
#include <QDebug>
#include <QFileDialog>

#include "constantes.h"
#include "mapwidget.h"
#include "obstacleslist.h"
#include "constants.h"

namespace Ui {
class FrameIDE;
}

class FrameIDE : public QFrame
{
    Q_OBJECT
    
public:
    explicit FrameIDE(QWidget *parent = 0);

    void preEstablecerConfiguracionPiezas(QList <int> pLista);
    void abrir();
    void guardar();
    void proyectoToMatriz(QString pProyecto);
    QString matrizToProyecto();

    ~FrameIDE();
    
private:
    Ui::FrameIDE *ui;
    ObstaclesList *obstaclesList;
    MapWidget *mapWidget;

    //QList <int> listaConfiguracionPiezas;

    int matrizConfiguacionPiezas [FILAS_PIEZAS][COLUMNAS_PIEZAS];
    QString path;

private:
    void crearObjetos();
    void crearBlques();
    void cargarBloque(QString pRuta, int pId);
    void iniciarConfiguracionPiezas();
    void limpiarPantalla();


private slots:
    void mostrarPiezas();
    void iniciarDebugger();
    void on_pushButtonPlayAbrir_clicked();
    void on_pushButtonPlayGuardar_released();
    void on_pushButtonTrash_released();
};

#endif // FRAMEIDE_H
