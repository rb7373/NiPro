#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopWidget>

#include "constantes.h"
#include "botonanimadoa.h"
#include "piezas.h"
#include "pruebasfichas.h"
#include "administradorprincipal.h"
#include "mainmanager.h"
#include "frametablero.h"
#include "frameide.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /*Se sobreescribe el evento que se ejecuta cuando se cambia el tamano
      de la ventana.
      Llama a la funcion: centrarAreaPrincipal
      */
    void resizeEvent(QResizeEvent *);

    /*Coloca la ventana en el centro de la pantalla
      */
    void centrarVentana();

    /*Coloca el widget pricinpal (el Ã¡rea de trabajo)
      en el centro de la ventana
      */
    void centrarAreaPrincipal();

    /*Crea todos los objetos necesarios
      */
    void crearObjetos();

    /*Realiza las modificaciones necesaria a los objetos creados
      */
    void modificarObjetos();

    void iniciarAnimaciones();

private slots:
    //Muestra la configuracion de las piezas
    void mostrarPiezas();

    //Muestra la pantalla de pruebas
    void mostrarPruebas();

    //Mustra la pantalla de programacion
    void mostrarPantallaProgramacion();

    void mostrarIDE();

private:
    AdministradorPrincipal *_Administrador;
    AdministradorPiezas *_AdministradorPiezas;

    
private:
    Ui::MainWindow *ui;

    /*Comprende toda el area
    en la cual se muestran
    los demas elementos */
    QWidget *_AreaPrincipal;

    //botones
    BotonAnimadoA *_BottunPieces;
    BotonAnimadoA *_BottunSettings;
    BotonAnimadoA *_BottunPantallaProgramacion;
    BotonAnimadoA *_BottunIDEProgramacion;

    //Establece variables para el cambio de tamaño de los
    //botones con respecto al tamaño básico
    int _FactorEscala;
    int _FactorCambio;

};

#endif // MAINWINDOW_H
