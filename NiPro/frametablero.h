#ifndef FRAMETABLERO_H
#define FRAMETABLERO_H

#define PIEZAS_X
#define PIEZAS_Y

#include <QFrame>
#include <QLabel>
#include <QDebug>

#include "constants.h"
#include "constantes.h"
#include "administradorpiezas.h"
#include "controller.h"
#include "frameide.h"


#include <cmath>

namespace Ui {
class FrameTablero;
}

class FrameTablero : public QFrame
{
    Q_OBJECT
    
public:
    explicit FrameTablero(AdministradorPiezas *pAdministradorPiezas,
                          QWidget *parent);



    ~FrameTablero();


    
private:
    Ui::FrameTablero *ui;
    double escalaX;
    double escalaY;

    int widthTablero;
    int heightTablero;
    int widthPieza;
    int heightPieza;
    int separacionX;
    int separacionY;

    int widthPiezaTotal;
    int heightPiezaTotal;


    QList<QLabel *> _Piezas;
    QList<int > _ListaPiezasID;
    AdministradorPiezas *_AdministradorPiezas;

    bool matrizEstadoAnterior [FILAS_PIEZAS][COLUMNAS_PIEZAS];
    bool matrizEstadoActual [FILAS_PIEZAS][COLUMNAS_PIEZAS];

    //Image processing controller
    Controller *_Controller;

    //Parametros camara
    int sourceWidth;
    int sourceHeight;
    int deviceNumber;
    int imageBufferSize;
    bool isCameraConnected;
    ImageProcessingFlags imageProcessingFlags;
    ImageProcessingSettings imageProcessingSettings;

    bool isPaused;

private slots:
    void connectToCamera();
    void actulizarPlay();
    void actualizarStop();
    void actualizarPause();
    void actualizarPiezas(float pX,
                          float pY,
                          float pWidth,
                          float pHeight,
                          int pID);

    void reActulizarPantalla(bool inicia);

    void on_pushButtonUpdate_clicked();

private:
    //Get settings
    int getDeviceNumber();
    int getImageBufferSize();
    bool getDropFrameCheckBoxState();
    int getCaptureThreadPrio();
    int getProcessingThreadPrio();
    void initializeImageProcessingFlagsStructure();
    void updateStoredSettings();
    void resetAllToDefaults();

    //camara
    void connectToCameraAux();
    void disconnectCamera();

    //GUI
    void crearObjetos();

    void comprobarCambios();

signals:
    void newImageProcessingFlags(struct ImageProcessingFlags imageProcessingFlags);
    void newImageProcessingSettings(struct ImageProcessingSettings pSettings);

};

#endif // FRAMETABLERO_H
