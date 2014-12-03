#include "constants.h"




Constants::Constants()
{
}

const int Constants::CANTIDAD_PIEZAS_TABLERO_X = COLUMNAS_PIEZAS;
const int Constants::CANTIDAD_PIEZAS_TABLERO_Y = FILAS_PIEZAS;

const int Constants::TAM_X_SCROll_AREA = 880;
const int Constants::TAM_Y_SCROll_AREA = 512;
const int Constants::RESOLUCION_W = 640;
const int Constants::RESOLUCION_H = 480;

const int Constants::DEFAULT_IMAGE_BUFFER_SIZE = 5;
const int Constants::DEFAULT_CAMERA_DEV_NO = -1;
const bool Constants::DEFAULT_DROP_FRAMES = false;

// Thread priorities
const int Constants::DEFAULT_CAP_THREAD_PRIO = QThread::HighPriority;
const int Constants::DEFAULT_PROC_THREAD_PRIO = QThread::TimeCriticalPriority;

// FPS statistics queue lengths
const int Constants::DEFAULT_PROCESSING_FPS_STAT_QUEUE_LENGTH = 32;
const int Constants::DEFAULT_CAPTURE_FPS_STAT_QUEUE_LENGTH = 32;



const QString Constants::TRANSPARENT_BACKGROUND = "background-color: rgba( 255, 255, 255, 0% );";


const QString Constants::PATH_ICON_CHECK_CAMERA = ":/images/icons/set_0/check_1_64x64.png";
const QString Constants::PATH_ICON_UNCHECK_CAMERA = ":/images/icons/set_0/uncheck_2_64x64.png";
const QString Constants::PATH_ICON_CAMERA = ":/images/icons/set_0/camera_1_96x96.png";
const QString Constants::PATH_ICON_SEARCH = ":/icon/buttons/images/search_1_128_128.png";
const QString Constants::PATH_ICON_PIECES = ":/images/icons/set_0/puzzle_Pieces_1.png";
const QString Constants::PATH_ICON_SETTINGS = ":/images/icons/set_0/plumber_1.png";
const QString Constants::PATH_ICON_PROGRAMMING = ":/images/icons/set_0/computer_1_256x256.png";
const QString Constants::PATH_ICON_PROGRAMMING_IDE = ":/images/icons/set_0/computer_2_256x256.png";



const QString Constants::TITLE_BUTTON_CHECK_CAMERA = "<font color='white'>Inicio</font>";
const QString Constants::TITLE_BUTTON_CAMERA = "<font color='white'>Tomar Foto</font>";
const QString Constants::TITLE_BUTTON_SEARCH = "<font color='white'>Buscar</font>";
const QString Constants::TITLE_BUTTON_PIECES = "<font color='white'>Piezas</font>";
const QString Constants::TITLE_BUTTON_PRUEBAS = "<font color='white'>Pruebas</font>";
const QString Constants::TITLE_BUTTON_PROGRAMACION = "<font color='white'>Programar</font>";
const QString Constants::TITLE_BUTTON_IDE = "<font color='white'>Depurar</font>";

const QString Constants::TITLE_BUTTON_COMIC = "font: 75 12pt 'Comic Sans MS';";


const int Constants::CANTIDAD_PIEZAS = 27; //

const int Constants::DURACION_ANIMACION_BOTON = 1000;
const int Constants::DURACION_ANIMACION_LABEL_CAMARA = 1000;
const int Constants::DURACION_ANIMACION_MOSTRAR_VENTANA_SETTINGS = 2000;

const int Constants::CHANGE_SIZE_BUTTON_X = 30;
const int Constants::CHANGE_SIZE_BUTTON_Y = 30;
const int Constants::SIZE_ICON_X = 64;
const int Constants::SIZE_ICON_Y = 64;
const int Constants::CHANGE_POS_BUTTON = 20;

const int Constants::POS_BUTTON_CAMERA_CHECK_X = 30;
const int Constants::POS_BUTTON_CAMERA_CHECK_Y = 100;

const int Constants::POS_BUTTON_PIECES_X = 100;
const int Constants::POS_BUTTON_PIECES_Y = 100;

const int Constants::INCREASE_SIZE_20 = 20;

const int Constants::INCREASE_SIZE_40 = 40;

// IMAGE PROCESSING
// Smooth
const int Constants::DEFAULT_SMOOTH_TYPE = 0; // Options: [BLUR=0,GAUSSIAN=1,MEDIAN=2]
const int Constants::DEFAULT_SMOOTH_PARAM_1 = 3;
const int Constants::DEFAULT_SMOOTH_PARAM_2 = 3;
const int Constants::DEFAULT_SMOOTH_PARAM_3 = 0;
const int Constants::DEFAULT_SMOOTH_PARAM_4 = 0;
// Dilate
const int Constants::DEFAULT_DILATE_ITERATIONS = 1;
// Erode
const int Constants::DEFAULT_ERODE_ITERATIONS = 0;
// Flip
const int Constants::DEFAULT_FLIP_CODE = 1; // Options: [x-axis=0,y-axis=1,both axes=-1]
// Canny
const int Constants::DEFAULT_CANNY_THRESHOLD_1 = 10;
const int Constants::DEFAULT_CANNY_THRESHOLD_2 = 100;
const int Constants::DEFAULT_CANNY_APERTURE_SIZE = 3;
const bool Constants::DEFAULT_CANNY_L2GRADIENT = false;
const bool Constants::DEFAULT_IMAGE_FIND = -1;
const int Constants::DEFAULT_COLOR_DISTANCE_THRESHOLD = 30;

const bool Constants::DEFAULT_GRAYSCALE = false;
const bool Constants::DEFAULT_SMOOTH = false;
const bool Constants::DEFAULT_DILATE = false;
const bool Constants::DEFAULT_ERODE = false;
const bool Constants::DEFAULT_FLIP = false;
const bool Constants::DEFAULT_CANNY = false;
const bool Constants::DEFAULT_FIND_PIECES = false;
const bool Constants::DEFAULT_FIND_PIECE = false;

