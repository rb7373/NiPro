#ifndef CONSTANTS_H
#define CONSTANTS_H

#define FILAS_PIEZAS 8
#define COLUMNAS_PIEZAS 12

#include <QString>
#include <QThread>

#include <QDir>

class Constants
{
public:
    Constants();

    const static int CANTIDAD_PIEZAS_TABLERO_X;
    const static int CANTIDAD_PIEZAS_TABLERO_Y;

    const static int TAM_X_SCROll_AREA;
    const static int TAM_Y_SCROll_AREA;
    const static int RESOLUCION_W;
    const static int RESOLUCION_H;

    const static int DEFAULT_IMAGE_BUFFER_SIZE;
    const static int DEFAULT_CAMERA_DEV_NO;
    const static bool DEFAULT_DROP_FRAMES;

    // Thread priorities
    const static int DEFAULT_CAP_THREAD_PRIO;
    const static int DEFAULT_PROC_THREAD_PRIO;

    // FPS statistics queue lengths
    const static int DEFAULT_PROCESSING_FPS_STAT_QUEUE_LENGTH;
    const static int DEFAULT_CAPTURE_FPS_STAT_QUEUE_LENGTH;

    //GUI display
    static const QString TRANSPARENT_BACKGROUND;

    //Paths
    static const QString PATH_ICON_CHECK_CAMERA;
    static const QString PATH_ICON_UNCHECK_CAMERA;
    static const QString PATH_ICON_CAMERA;
    static const QString PATH_ICON_SEARCH;
    static const QString PATH_ICON_PIECES;
    static const QString PATH_ICON_SETTINGS;
    static const QString PATH_ICON_PROGRAMMING;
    static const QString PATH_ICON_PROGRAMMING_IDE;

    //Titles
    static const QString TITLE_BUTTON_CHECK_CAMERA;
    static const QString TITLE_BUTTON_CAMERA;
    static const QString TITLE_BUTTON_SEARCH;
    static const QString TITLE_BUTTON_PIECES;
    static const QString TITLE_BUTTON_PRUEBAS;
    static const QString TITLE_BUTTON_PROGRAMACION;
    static const QString TITLE_BUTTON_IDE;

    //Button styles
    static const QString TITLE_BUTTON_COMIC;



    const static int DURACION_ANIMACION_BOTON;
    const static int DURACION_ANIMACION_LABEL_CAMARA;
    const static int DURACION_ANIMACION_MOSTRAR_VENTANA_SETTINGS;

    const static int CHANGE_SIZE_BUTTON_X;
    const static int CHANGE_SIZE_BUTTON_Y;
    const static int SIZE_ICON_X;
    const static int SIZE_ICON_Y;
    const static int CHANGE_POS_BUTTON;

    const static int CANTIDAD_PIEZAS;

    const static int POS_BUTTON_CAMERA_CHECK_X;
    const static int POS_BUTTON_CAMERA_CHECK_Y;

    const static int POS_BUTTON_PIECES_X;
    const static int POS_BUTTON_PIECES_Y;


    const static int INCREASE_SIZE_20;
    const static int INCREASE_SIZE_40;


    // IMAGE PROCESSING
    // Smooth
    const static int DEFAULT_SMOOTH_TYPE;
    const static int DEFAULT_SMOOTH_PARAM_1;
    const static int DEFAULT_SMOOTH_PARAM_2;
    const static int DEFAULT_SMOOTH_PARAM_3;
    const static int DEFAULT_SMOOTH_PARAM_4;
    // Dilate
    const static int DEFAULT_DILATE_ITERATIONS;
    // Erode
    const static int DEFAULT_ERODE_ITERATIONS;
    // Flip
    const static int DEFAULT_FLIP_CODE;
    // Canny
    const static int DEFAULT_CANNY_THRESHOLD_1;
    const static int DEFAULT_CANNY_THRESHOLD_2;
    const static int DEFAULT_CANNY_APERTURE_SIZE;
    const static bool DEFAULT_CANNY_L2GRADIENT;
    const static bool DEFAULT_IMAGE_FIND;
    const static int DEFAULT_COLOR_DISTANCE_THRESHOLD;


    const static bool DEFAULT_GRAYSCALE;
    const static bool DEFAULT_SMOOTH;
    const static bool DEFAULT_DILATE;
    const static bool DEFAULT_ERODE;
    const static bool DEFAULT_FLIP;
    const static bool DEFAULT_CANNY;
    const static bool DEFAULT_FIND_PIECES;
    const static bool DEFAULT_FIND_PIECE;
};

#endif // CONSTANTS_H
