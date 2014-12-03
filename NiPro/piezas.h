#ifndef PIEZAS_H
#define PIEZAS_H

#include <QFrame>
#include <QPushButton>
#include <QVBoxLayout>

#include <QStackedWidget>
#include <QStackedLayout>
#include <QFormLayout>

#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>

#include "pieza.h"
#include "framelabel.h"

//OPENCV
#include "Structures.h"
#include "controller.h"
#include "administradorpiezas.h"



namespace Ui {
class Piezas;
}

class Piezas : public QFrame
{
    Q_OBJECT
    
public:
    explicit Piezas(AdministradorPiezas *pAdministradorPiezas, QWidget *parent = 0);

    ~Piezas();

    //****************

private:
    //Crea los objetos necesarios en la ventana
    void crearObjetos();
    void cargarPiezas();
    void reducirScrollArea();
    void actualizarImagen(int pID, QString pRutaImagenPersonalizada);
    void ocultarFrameLabel();

public slots:
    void actualizarDescripcionFuncion(int pID,
                                 QString pFuncion,
                                 QString pDescripcion);



private slots:

    void iniciarAnimacionMostrarVentana();
    void iniciarAnimacionOcultarVentana();

private slots:
    void cambiarPieza(int pID);
    void mostrarLabelCamara();
    void iniciarCamara();
    void aumentarScrollArea();
    void mostrarPiezas();

private:
    Ui::Piezas *ui;
    QList <Pieza *> _ListaPiezas;
    QFrame *_FramePiezas;
    int _IDPiezaActual;
    QList <QWidget *> _ListaLabels;
    bool isTransparenciaActiva;

    ////////////////////////////////////////
    //INICIA: Seccción genérica para la cámara
    ////////////////////////////////////////

private:

    AdministradorPiezas *_AdministradorPiezas;

    //INICIA: Variables de la cámara

    FrameLabel *_LabelCamara;
    QPixmap _PixmapFrameLabel;
    QPixmap _PixmapSave;
    BotonAnimadoA *_BottunTakePhoto;
    BotonAnimadoA *_BottunSave;
    QWidget *_MarcoLabelFoto;
    QLabel *_LabelPhoto;
    QLabel *_LabelCoordenadas;

    //Image processing controller
    Controller *_Controller;

    //TaskData structure
    TaskData taskData;

    //Parametros camara
    int sourceWidth;
    int sourceHeight;
    int deviceNumber;
    int imageBufferSize;
    bool isCameraConnected;
    bool isNewImagenReady;
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

    //Inicializa la estructura de lectura del ratón
    void initializeTaskDataStructure();

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


    //FINALIZA: Métodos privados para la cámara

public slots:
    void connectToCamera();
    void connectToCameraAux();
    void takeAPhoto();
    void disconnectCamera();
    void about();
    void clearImageBuffer();
    void setGrayscale(bool);
    void setSmooth(bool);
    void setDilate(bool);
    void setErode(bool);
    void setFlip(bool);
    void setCanny(bool);
    void setImageProcessingSettings();
    void updateMouseCursorPosLabel();
    void newMouseData(struct MouseData);



    //Inicializa los componentes gráficos de la ventana
    void camDisconnected();
    void initializeFrameLabel();

    void guardarImagen();

private slots:
    void updateFrame(const QImage &frame);
    void reestablecerFondoLabelCamara();

signals:
    void newImageProcessingFlags(struct ImageProcessingFlags imageProcessingFlags);
    void newTaskData(struct TaskData taskData);
    void newImageProcessingSettings(struct ImageProcessingSettings pSettings);

    void piezaPersonalizada(int pID);

    //FINALIZA: Sección genérica para la cámara

};

#endif // PIEZAS_H
