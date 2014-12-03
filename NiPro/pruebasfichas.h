#ifndef PRUEBASFICHAS_H
#define PRUEBASFICHAS_H

#include <QFrame>
#include <QDebug>

#include "botonanimadoabooldosestados.h"

//OPENCV
#include "Structures.h"
#include "controller.h"
#include "framelabel.h"
#include "pushbuttonpiezasimple.h"
#include "frametablero.h"


namespace Ui {
class PruebasFichas;
}

class PruebasFichas : public QFrame
{
    Q_OBJECT
    
public:
    explicit PruebasFichas(AdministradorPiezas *pAdministradorPiezas, QWidget *parent = 0);
    ~PruebasFichas();

    AdministradorPiezas *_AdministradorPiezas;


    FrameTablero *_Tablero;




private slots:

    void iniciarAnimacionMostrarVentana();
    void iniciarAnimacionOcultarVentana();

    void actualizarPiezaADetectar(int pIDPieza);

    void mostrarNuevaPieza(float pX, float pY, float pWidth, float pHeight, int pID);

    void actualizarPiezaEnProcesamiento(int pID);

private:
    //Crea los objetos necesarios en la ventana
    void crearObjetos();
    void cargarFichas();
    
private:
    Ui::PruebasFichas *ui;

    QList <QPushButton *> _ListaPiezas;
    QFrame *_FramePiezas;
    QPushButton *pushButtonPiezaActual;
    int _IDPiezaActual;

    QString path;

    //GUI Display
    BotonAnimadoABoolDosEstados *_BottunCameraCheck;

    ////////////////////////////////////////
    //INICIA: Seccción genérica para la cámara
    ////////////////////////////////////////

    //INICIA: Variables de la cámara

    FrameLabel *_LabelCamara;

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

    //OpenCV
    cv::Mat imageTemp;

    //FINALIZA: Variables de la cámara

    //INICIA: Métodos privados para la cámara

    //Establece los parametros adecuados para iniciar la
    //camara
    void iniciarParametrosCamara();

    //Inicializa las señales
    void iniciarConexionesCamara();

    //Inicializa las banderas la estructura de procesamiento
    void initializeImageProcessingFlagsStructure();

    //Get settings
    int getDeviceNumber();
    int getImageBufferSize();
    bool getDropFrameCheckBoxState();
    int getCaptureThreadPrio();
    int getProcessingThreadPrio();

    //Actualiza los parámetros
    void updateStoredSettings();

    //Asigna los paramñetros a los valores por defecto
    void resetAllToDefaults();

    void loadImage(QString pPath);

private slots:
    void connectToCamera(bool pToggled);

    //FINALIZA: Métodos privados para la cámara

public slots:
    void connectToCameraAux();
    void disconnectCamera();
    void clearImageBuffer();
    void setGrayscale(bool);
    void setSmooth(bool);
    void setDilate(bool);
    void setErode(bool);
    void setFlip(bool);
    void setCanny(bool);
    void setImageProcessingSettings();

    //Inicializa los componentes gráficos de la ventana
    void camDisconnected();


private slots:
    void updateFrame(const QImage &frame);
    void reestablecerFondoLabelCamara();

    void on_pushButtonDistanceThreshold_released();

    void on_horizontalSliderDistanceThreshold_valueChanged(int value);

    void on_pushButtonErodeNumber_released();

    void on_horizontalSliderErodeNumber_valueChanged(int value);

signals:
    void newImageProcessingFlags(struct ImageProcessingFlags imageProcessingFlags);
    void newImageProcessingSettings(struct ImageProcessingSettings pSettings);

    //FINALIZA: Sección genérica para la cámara
};

#endif // PRUEBASFICHAS_H
