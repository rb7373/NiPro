#include "processingthread.h"

ProcessingThread::ProcessingThread(ImageBuffer *imageBuffer,
                                   int inputSourceWidth,
                                   int inputSourceHeight)
    : QThread(),
      imageBuffer(imageBuffer),
      inputSourceWidth(inputSourceWidth),
      inputSourceHeight(inputSourceHeight)
{
    // Initialize variables
    stopped=false;
    sampleNo=0;
    fpsSum=0;
    avgFPS=0;
    fps.clear();
    currentROI=Rect(0,0,inputSourceWidth,inputSourceHeight);
    // Store original ROI
    originalROI=currentROI;



    _ColorDetector = new ColorDetector();

    detector = new cv::FastFeatureDetector();

    //-- Step 1: Detect the keypoints using SURF Detector
    //int minHessian = 400;

    //detector = new SurfFeatureDetector( minHessian );
    extractor = new cv::SurfDescriptorExtractor();


    QDir::setCurrent(QCoreApplication::applicationDirPath());
    path = QDir::currentPath()+"/fichas/pieza";

    //_ColorDetector->setTargetColor(181,83,95);

} // ProcessingThread constructor

ProcessingThread::~ProcessingThread()
{

    delete _ColorDetector;

    ////////////////////////////
    //Cleanup
    ////////////////////////////
    delete detector;
    delete extractor;

} // ProcessingThread destructor

void ProcessingThread::run()
{

    while(true)
    {
        //qDebug() << "Procesando captura";

        /////////////////////////////////
        // Stop thread if stopped=TRUE //
        /////////////////////////////////
        stoppedMutex.lock();
        if (stopped)
        {
            stopped=false;
            stoppedMutex.unlock();
            break;
        }
        stoppedMutex.unlock();
        /////////////////////////////////
        /////////////////////////////////

        //        // Get frame from queue, store in currentFrame, set ROI
        //        currentFrame=Mat(imageBuffer->getFrame(),currentROI);

        //namedWindow("RGB", CV_WINDOW_AUTOSIZE );
        //imshow("RGB", currentFrame );

        updateMembersMutex.lock();




        ///////////////////
        // PERFORM TASKS //
        ///////////////////
        // Note: ROI changes will take effect on next frame
        if(resetROIFlag)
        {
            resetROI();
        }
        else if(setROIFlag)
        {
            setROI();
        }
        ////////////////////////////////////
        // PERFORM IMAGE PROCESSING BELOW //
        ////////////////////////////////////

        if (findPiece)
        {
            QTime timeGeneral;
            timeGeneral.start();


            emit iniciaProcesamientoEspecial(true);
            for (int IDPieza = 0; IDPieza < _AdministradorPiezas->sizeLista(); IDPieza++)
            {

                // Get frame from queue, store in currentFrame, set ROI

                if (imageBuffer->getSizeOfImageBuffer() == 0)
                {
                    sleep(2);
                }

                currentFrame=Mat(imageBuffer->getFrame(),currentROI);


                QTime timeEspecifico;
                timeEspecifico.start();

                _TempPieza = _AdministradorPiezas->at(IDPieza);

                qDebug() << "Reconociendo fichas: "  << _TempPieza->_ID;
                emit piezaActual(_TempPieza->_ID);

                //qDebug() << "Imagen: " << rutaPieza;

                if(erodeOn)
                {

                    erode(currentFrame,currentFrame,Mat(),Point(-1,-1),erodeNumberOfIterations);
                }

                if(flipOn)
                {

                    flip(currentFrame,currentFrame,flipCode);

                }

                //Mat sceneImg = currentFrame.clone();

                if(currentFrame.data)
                {
                    std::vector<cv::KeyPoint> objectKeypoints = _TempPieza->objectKeypoints;
                    std::vector<cv::KeyPoint> sceneKeypoints;
                    cv::Mat sceneDescriptors;
                    cv::Mat objectData = _TempPieza->objectData;
                    cv::Mat sceneData;
                    float nndrRatio = 0.6;
                    std::vector<cv::Point2f> mpts_1_Obj, mpts_2_scene; // Used for homography
                    std::vector<int> indexes_1, indexes_2; // Used for homography
                    std::vector<uchar> outlier_mask;  // Used for homography
                    cv::Mat homography;
                    // FIND HOMOGRAPHY
                    unsigned int minInliers = 20;
                    std::vector<Point2f> obj_corners(4);
                    std::vector<Point2f> scene_corners(4);
                    Rect rectTemp;

                    ////////////////////////////
                    // EXTRACT KEYPOINTS
                    ////////////////////////////

                    int veces = 0;
                    while (veces < 20)
                    {

                        //sceneImg = currentFrame.clone();
                        detector->detect(currentFrame, sceneKeypoints);

                        ////////////////////////////
                        // EXTRACT DESCRIPTORS
                        ////////////////////////////

                        //printf("Object: %d descriptors extracted in %d ms\n", objectDescriptors.rows, time.restart());
                        extractor->compute(currentFrame, sceneKeypoints, sceneDescriptors);
                        //printf("Scene: %d descriptors extracted in %d ms\n", sceneDescriptors.rows, time.restart());

                        ////////////////////////////
                        // NEAREST NEIGHBOR MATCHING USING FLANN LIBRARY (included in OpenCV)
                        ////////////////////////////
                        // Format descriptors for Flann

                        if(sceneDescriptors.type()!=CV_32F) {
                            sceneDescriptors.convertTo(sceneData, CV_32F); // make sure it's CV_32F
                        }
                        else {
                            sceneData = sceneDescriptors;
                        }

                        // Create Flann index
                        cv::flann::Index treeFlannIndex(sceneData, cv::flann::KDTreeIndexParams());
                        //printf("Time creating FLANN index = %d ms\n", time.restart());

                        // search (nearest neighbor)
                        int k=2; // find the 2 nearest neighbors
                        cv::Mat results(objectData.rows, k, CV_32SC1); // Results index
                        cv::Mat dists(objectData.rows, k, CV_32FC1); // Distance results are CV_32FC1
                        treeFlannIndex.knnSearch(objectData, results, dists, k, cv::flann::SearchParams() ); // maximum number of leafs checked
                        //printf("Time nearest neighbor search = %d ms\n", time.restart());

                        ////////////////////////////
                        // PROCESS NEAREST NEIGHBOR RESULTS
                        ////////////////////////////

                        // Find correspondences by NNDR (Nearest Neighbor Distance Ratio)
                        nndrRatio = 0.6;

                        for(int i=0; i<objectData.rows; ++i)
                        {
                            // Check if this descriptor matches with those of the objects
                            // Apply NNDR
                            if(dists.at<float>(i,0) <= nndrRatio * dists.at<float>(i,1))
                            {
                                mpts_1_Obj.push_back(objectKeypoints.at(i).pt);
                                indexes_1.push_back(i);

                                mpts_2_scene.push_back(sceneKeypoints.at(results.at<int>(i,0)).pt);
                                indexes_2.push_back(results.at<int>(i,0));
                            }
                        }


                        if(mpts_1_Obj.size() >= minInliers)
                        {
                            timeEspecifico.start();
                            homography = findHomography(mpts_1_Obj,
                                                        mpts_2_scene,
                                                        cv::RANSAC,
                                                        1.0,
                                                        outlier_mask);

                            obj_corners[0] = cvPoint(0,0);
                            obj_corners[1] = cvPoint( _TempPieza->_Cols, 0 );
                            obj_corners[2] = cvPoint( _TempPieza->_Cols, _TempPieza->_Rows );
                            obj_corners[3] = cvPoint( 0, _TempPieza->_Rows );

                            scene_corners[0].x = -1;
                            scene_corners[1].x = -1;
                            scene_corners[2].x = -1;
                            scene_corners[3].x = -1;

                            perspectiveTransform( obj_corners, scene_corners, homography);


                            rectTemp = Rect_<float>(scene_corners[0].x,
                                                    scene_corners[0].y,
                                                    scene_corners[1].x - scene_corners[0].x,
                                                    scene_corners[2].x - scene_corners[0].x);



                            rectangle(currentFrame, rectTemp,
                                      Scalar(qrand() % 256,
                                             qrand() % 256,
                                             qrand() % 256)
                                      , CV_FILLED );

                            sceneKeypoints.clear();
                            mpts_1_Obj.clear();
                            mpts_2_scene.clear();
                            indexes_1.clear();
                            indexes_2.clear();
                            outlier_mask.clear();

                            float width = rectTemp.width;
                            float height = rectTemp.height;


                            if (width > 10 &&  width < 100 && height > 10 && height < 100)
                            {
                                emit nuevaPieza(rectTemp.x, rectTemp.y, width, height, _TempPieza->_ID);
                            }

                            frame=MatToQImage(currentFrame);

                            emit newFrame(frame);

                            veces++;
                        }
                        else
                        {
                            //                            frame=MatToQImage(currentFrame);

                            //                            emit newFrame(frame);

                            qDebug() << "Not enough matches";
                            break;
                        }




                    }

                    qDebug() << "Pieza: "  << _TempPieza->_ID << "Reconocida: " << veces << " veces";
                    qDebug() << "Milisegundos transcurridos: " << timeEspecifico.elapsed();
                    qDebug() << "Segundos transcurridos: " << timeEspecifico.elapsed()/(1000+0.0);
                }
                else
                {
                    qDebug() << "No se logro cargar imagen";
                }

            }

            qDebug() << "Milisegundos transcurridos: " << timeGeneral.elapsed();
            qDebug() << "Segundos transcurridos: " << timeGeneral.elapsed()/(1000+0.0);
            emit iniciaProcesamientoEspecial(false);
        }
        else
        {
            if (imageBuffer->getSizeOfImageBuffer() == 0)
            {
                sleep(2);
            }

            // Get frame from queue, store in currentFrame, set ROI
            currentFrame=Mat(imageBuffer->getFrame(),currentROI);

            if(erodeOn)
            {

                erode(currentFrame,currentFrame,Mat(),Point(-1,-1),erodeNumberOfIterations);
            }

            if(flipOn)
            {

                flip(currentFrame,currentFrame,flipCode);

            }

            frame=MatToQImage(currentFrame);
            emit newFrame(frame);

        }

        ////////////////////////////////////
        // PERFORM IMAGE PROCESSING ABOVE //
        ////////////////////////////////////



        updateMembersMutex.unlock();

        // Update statistics
        updateFPS(processingTime);
        currentSizeOfBuffer=imageBuffer->getSizeOfImageBuffer();

    }

    //qDebug() << "---";
    //qDebug() << "Deteniendo hilo de procesamiento...";
    //qDebug() << "---";
}

void ProcessingThread::updateFPS(int timeElapsed)
{
    // Add instantaneous FPS value to queue
    if(timeElapsed>0)
    {
        fps.enqueue((int)(1000/timeElapsed));
        // Increment sample number
        sampleNo++;
    }
    // Maximum size of queue is DEFAULT_PROCESSING_FPS_STAT_QUEUE_LENGTH
    if(fps.size()>Constants::DEFAULT_PROCESSING_FPS_STAT_QUEUE_LENGTH)
        fps.dequeue();
    // Update FPS value every DEFAULT_PROCESSING_FPS_STAT_QUEUE_LENGTH samples
    if((fps.size()==Constants::DEFAULT_PROCESSING_FPS_STAT_QUEUE_LENGTH)
            &&(sampleNo==Constants::DEFAULT_PROCESSING_FPS_STAT_QUEUE_LENGTH))
    {
        // Empty queue and store sum
        while(!fps.empty())
            fpsSum+=fps.dequeue();
        // Calculate average FPS
        avgFPS=fpsSum/Constants::DEFAULT_PROCESSING_FPS_STAT_QUEUE_LENGTH;
        // Reset sum
        fpsSum=0;
        // Reset sample number
        sampleNo=0;
    }
} // updateFPS()

void ProcessingThread::stopProcessingThread()
{
    stoppedMutex.lock();
    stopped=true;
    stoppedMutex.unlock();
} // stopProcessingThread()

void ProcessingThread::setROI()
{
    // Save selection as new (current) ROI
    currentROI=selectionBox;
    //qDebug() <<"###";
    //qDebug() << "Zona de procesamiento asignada";
    //qDebug() <<"###";

    // Reset flag to FALSE
    setROIFlag=false;
} // setROI()

void ProcessingThread::resetROI()
{
    // Reset ROI to original if not already
    if((currentROI.x!=originalROI.x)&&(currentROI.y!=originalROI.y)&&(currentROI.width!=originalROI.width)&&(currentROI.height!=originalROI.height))
    {
        currentROI=originalROI;

        //qDebug() <<"###";
        //qDebug() << "Zona de procesamiento reiniciada";
        //qDebug() <<"###";
    }
    // Reset flag to FALSE
    resetROIFlag=false;
} // resetROI()

void ProcessingThread::updateImageProcessingFlags(struct ImageProcessingFlags imageProcessingFlags)
{
    QMutexLocker locker(&updateMembersMutex);
    this->grayscaleOn=imageProcessingFlags.grayscaleOn;
    this->smoothOn=imageProcessingFlags.smoothOn;
    this->dilateOn=imageProcessingFlags.dilateOn;
    this->erodeOn=imageProcessingFlags.erodeOn;
    this->flipOn=imageProcessingFlags.flipOn;
    this->cannyOn=imageProcessingFlags.cannyOn;
    this->findPieces = imageProcessingFlags.encontrarPiezas;
    this->findPiece = imageProcessingFlags.encontrarPieza;

} // updateImageProcessingFlags()

void ProcessingThread::updateImageProcessingSettings(struct ImageProcessingSettings imageProcessingSettings)
{
    QMutexLocker locker(&updateMembersMutex);
    this->smoothType=imageProcessingSettings.smoothType;
    this->smoothParam1=imageProcessingSettings.smoothParam1;
    this->smoothParam2=imageProcessingSettings.smoothParam2;
    this->smoothParam3=imageProcessingSettings.smoothParam3;
    this->smoothParam4=imageProcessingSettings.smoothParam4;
    this->dilateNumberOfIterations=imageProcessingSettings.dilateNumberOfIterations;
    this->erodeNumberOfIterations=imageProcessingSettings.erodeNumberOfIterations;
    this->flipCode=imageProcessingSettings.flipCode;
    this->cannyThreshold1=imageProcessingSettings.cannyThreshold1;
    this->cannyThreshold2=imageProcessingSettings.cannyThreshold2;
    this->cannyApertureSize=imageProcessingSettings.cannyApertureSize;
    this->cannyL2gradient=imageProcessingSettings.cannyL2gradient;
    this->encontrarPieza=imageProcessingSettings.encontrarPieza;
    this->colorDistanceThreshold = imageProcessingSettings.colorDistanceThreshold;
} // updateImageProcessingSettings()

void ProcessingThread::updateTaskData(struct TaskData taskData)
{
    QMutexLocker locker(&updateMembersMutex);
    this->setROIFlag=taskData.setROIFlag;
    this->resetROIFlag=taskData.resetROIFlag;
    this->selectionBox.x=taskData.selectionBox.left();
    this->selectionBox.y=taskData.selectionBox.top();
    this->selectionBox.width=taskData.selectionBox.width();
    this->selectionBox.height=taskData.selectionBox.height();
} // updateTaskData()

int ProcessingThread::getAvgFPS()
{
    return avgFPS;
} // getAvgFPS()

int ProcessingThread::getCurrentSizeOfBuffer()
{
    return currentSizeOfBuffer;
} // getCurrentSizeOfBuffer()

Rect ProcessingThread::getCurrentROI()
{
    return currentROI;
} // getCurrentROI();

//tests

void ProcessingThread::processA(cv::Mat &image, Rect pRect)
{

    qDebug() << pRect.height <<"  " << pRect.width;
    for( int i = pRect.y; i < pRect.y + pRect.height; i++ )
    {
        for( int j = pRect.x; j < pRect.x + pRect.width; j++ )
        {
            image.at<cv::Vec3b>(i,j)[0]= 255;
            image.at<cv::Vec3b>(i,j)[1]= 0;
            image.at<cv::Vec3b>(i,j)[2]= 0;                                          // Cast and access by index
        }
    }
    //    for (int i = pRect.x ; i <pRect.x + pRect.width; i++) {
    //        for (int j = pRect.y ;pRect.y <pRect.y + pRect.height; j++)
    //        {
    //            if (image.channels() == 1) { // gray-level image
    //                image.at<uchar>(i,j)= 0;
    //            } else if (image.channels() == 3) { // color image
    //                image.at<cv::Vec3b>(i,j)[0]= 0;
    //                image.at<cv::Vec3b>(i,j)[1]= 0;
    //                image.at<cv::Vec3b>(i,j)[2]= 0;
    //            }
    //        }
    //    }
}

//////////////////////////
////////Temp
//////////////////////////

// Grayscale conversion
//if(grayscaleOn)
//    cvtColor(currentFrame,currentFrameGrayscale,CV_BGR2GRAY);
//// Smooth (in-place operations)
//if(smoothOn)
//{
//    if(grayscaleOn)
//    {
//        switch(smoothType)
//        {
//        // BLUR
//        case 0:
//            blur(currentFrameGrayscale,currentFrameGrayscale,Size(smoothParam1,smoothParam2));
//            break;
//            // GAUSSIAN
//        case 1:
//            GaussianBlur(currentFrameGrayscale,currentFrameGrayscale,Size(smoothParam1,smoothParam2),smoothParam3,smoothParam4);
//            break;
//            // MEDIAN
//        case 2:
//            medianBlur(currentFrameGrayscale,currentFrameGrayscale,smoothParam1);
//            break;
//        }
//    }
//    else
//    {
//        switch(smoothType)
//        {
//        // BLUR
//        case 0:
//            blur(currentFrame,currentFrame,Size(smoothParam1,smoothParam2));
//            break;
//            // GAUSSIAN
//        case 1:
//            GaussianBlur(currentFrame,currentFrame,Size(smoothParam1,smoothParam2),smoothParam3,smoothParam4);
//            break;
//            // MEDIAN
//        case 2:
//            medianBlur(currentFrame,currentFrame,smoothParam1);
//            break;
//        }
//    }
//}
//// Dilate
//if(dilateOn)
//{
//    if(grayscaleOn)
//        dilate(currentFrameGrayscale,currentFrameGrayscale,Mat(),Point(-1,-1),dilateNumberOfIterations);
//    else
//        dilate(currentFrame,currentFrame,Mat(),Point(-1,-1),dilateNumberOfIterations);
//}
//// Erode
//if(erodeOn)
//{
//    if(grayscaleOn)
//        erode(currentFrameGrayscale,currentFrameGrayscale,Mat(),Point(-1,-1),erodeNumberOfIterations);
//    else
//        erode(currentFrame,currentFrame,Mat(),Point(-1,-1),erodeNumberOfIterations);
//}

//// Canny edge detection
//if(cannyOn)
//{
//    // Frame must be converted to grayscale first if grayscale conversion is OFF
//    if(!grayscaleOn)
//        cvtColor(currentFrame,currentFrameGrayscale,CV_BGR2GRAY);

//    Canny(currentFrameGrayscale,currentFrameGrayscale,
//          cannyThreshold1,cannyThreshold2,
//          cannyApertureSize,cannyL2gradient);
//}


//tests
/*
if (findPiece)
{

    //                piezaTemp = _AdministradorPiezas->at(encontrarPieza);

    //                _ColorDetector->setTargetColor(piezaTemp->_R,
    //                                               piezaTemp->_G,
    //                                               piezaTemp->_B);

    //                _ColorDetector->setColorDistanceThreshold(piezaTemp->_ColorDistanceThreshold);

    //                currentFrame = _ColorDetector->procesar(currentFrame);

    //                // vector of keypoints
    //                std::vector<cv::KeyPoint> keypoints;
    //                // Construction of the Fast feature detector object
    //                cv::FastFeatureDetector fast(
    //                            20); // threshold for detection
    //                // feature point detection
    //                fast.detect(currentFrame,keypoints);

    //                cv::drawKeypoints(currentFrame, // original image
    //                                  keypoints, // vector of keypoints
    //                                  currentFrame, // the output image
    //                                  cv::Scalar(255,255,255), // keypoint color
    //                                  cv::DrawMatchesFlags::DRAW_OVER_OUTIMG); //drawing flag



    qDebug() << "Procesando cargar imagen";

    QTime time;
    time.start();

    //Load as grayscale


    QString rutaPieza = path +
            QString::number(0)+
            ".png";

    qDebug() << "Imagen: " << rutaPieza;

    Mat objectImg = imread(rutaPieza.toAscii().data());
    Mat sceneImg = currentFrame.clone();

    if( objectImg.data && sceneImg.data )
    {
        std::vector<cv::KeyPoint> objectKeypoints;
        std::vector<cv::KeyPoint> sceneKeypoints;
        cv::Mat objectDescriptors;
        cv::Mat sceneDescriptors;
        cv::FeatureDetector * detector;
        cv::DescriptorExtractor * extractor;
        cv::Mat objectData;
        cv::Mat sceneData;
        float nndrRatio = 0.6;
        std::vector<cv::Point2f> mpts_1_Obj, mpts_2_scene; // Used for homography
        std::vector<int> indexes_1, indexes_2; // Used for homography
        std::vector<uchar> outlier_mask;  // Used for homography
        cv::Mat homography;
        // FIND HOMOGRAPHY
        unsigned int minInliers = 8;
        std::vector<Point2f> obj_corners(4);
        std::vector<Point2f> scene_corners(4);
        Rect rectTemp;


        ////////////////////////////
        // EXTRACT KEYPOINTS
        ////////////////////////////

        detector = new cv::FastFeatureDetector();

        detector->detect(objectImg, objectKeypoints);
        //printf("Object: %d keypoints detected in %d ms\n", (int)objectKeypoints.size(), time.restart());
        detector->detect(sceneImg, sceneKeypoints);
        //printf("Scene: %d keypoints detected in %d ms\n", (int)sceneKeypoints.size(), time.restart());

        cv::drawKeypoints(currentFrame, // original image
                          sceneKeypoints, // vector of keypoints
                          currentFrame, // the output image
                          cv::Scalar(255,255,255), // keypoint color
                          cv::DrawMatchesFlags::DRAW_OVER_OUTIMG); //drawing flag


        ////////////////////////////
        // EXTRACT DESCRIPTORS
        ////////////////////////////

        extractor = new cv::SurfDescriptorExtractor();
        extractor->compute(objectImg, objectKeypoints, objectDescriptors);
        //printf("Object: %d descriptors extracted in %d ms\n", objectDescriptors.rows, time.restart());
        extractor->compute(sceneImg, sceneKeypoints, sceneDescriptors);
        //printf("Scene: %d descriptors extracted in %d ms\n", sceneDescriptors.rows, time.restart());

        ////////////////////////////
        // NEAREST NEIGHBOR MATCHING USING FLANN LIBRARY (included in OpenCV)
        ////////////////////////////
        // Format descriptors for Flann
        if(objectDescriptors.type()!=CV_32F) {
            objectDescriptors.convertTo(objectData, CV_32F); // make sure it's CV_32F
        }
        else {
            objectData = objectDescriptors;
        }
        if(sceneDescriptors.type()!=CV_32F) {
            sceneDescriptors.convertTo(sceneData, CV_32F); // make sure it's CV_32F
        }
        else {
            sceneData = sceneDescriptors;
        }

        // Create Flann index
        cv::flann::Index treeFlannIndex(sceneData, cv::flann::KDTreeIndexParams());
        //printf("Time creating FLANN index = %d ms\n", time.restart());

        // search (nearest neighbor)
        int k=2; // find the 2 nearest neighbors
        cv::Mat results(objectData.rows, k, CV_32SC1); // Results index
        cv::Mat dists(objectData.rows, k, CV_32FC1); // Distance results are CV_32FC1
        treeFlannIndex.knnSearch(objectData, results, dists, k, cv::flann::SearchParams() ); // maximum number of leafs checked
        //printf("Time nearest neighbor search = %d ms\n", time.restart());

        ////////////////////////////
        // PROCESS NEAREST NEIGHBOR RESULTS
        ////////////////////////////

        // Find correspondences by NNDR (Nearest Neighbor Distance Ratio)
        nndrRatio = 0.6;

        for(int i=0; i<objectData.rows; ++i)
        {
            // Check if this descriptor matches with those of the objects
            // Apply NNDR
            if(dists.at<float>(i,0) <= nndrRatio * dists.at<float>(i,1))
            {
                mpts_1_Obj.push_back(objectKeypoints.at(i).pt);
                indexes_1.push_back(i);

                mpts_2_scene.push_back(sceneKeypoints.at(results.at<int>(i,0)).pt);
                indexes_2.push_back(results.at<int>(i,0));
            }
        }


        if(mpts_1_Obj.size() >= minInliers)
        {
            time.start();
            homography = findHomography(mpts_1_Obj,
                                        mpts_2_scene,
                                        cv::RANSAC,
                                        1.0,
                                        outlier_mask);

            //printf("Time finding homography = %d ms\n", time.restart());

            obj_corners[0] = cvPoint(0,0);
            obj_corners[1] = cvPoint( objectImg.cols, 0 );
            obj_corners[2] = cvPoint( objectImg.cols, objectImg.rows );
            obj_corners[3] = cvPoint( 0, objectImg.rows );

            scene_corners[0].x = -1;
            scene_corners[1].x = -1;
            scene_corners[2].x = -1;
            scene_corners[3].x = -1;

            perspectiveTransform( obj_corners, scene_corners, homography);

            qDebug() << "---Rectangul---";

            qDebug() << "X = " << scene_corners[0].x << " Y = " << scene_corners[0].y;
            qDebug() << "X = " << scene_corners[1].x << " Y = " << scene_corners[1].y;
            qDebug() << "X = " << scene_corners[2].x << " Y = " << scene_corners[2].y;
            qDebug() << "X = " << scene_corners[3].x << " Y = " << scene_corners[3].y;




            rectTemp = Rect_<float>(scene_corners[0].x,
                                         scene_corners[0].y,
                                         scene_corners[1].x - scene_corners[0].x,
                                         scene_corners[2].x - scene_corners[0].x);


            //-- Draw lines between the corners (the mapped object in the scene - image_2 )
            rectangle(currentFrame, rectTemp, Scalar(0, 0, 0), CV_FILLED );


            ////printf("Inliers=%d Outliers=%d\n", inliers, outliers);
        }
        else
        {
            //printf("Not enough matches (%d) for homography...\n", (int)mpts_1_Obj.size());
        }


    }
    else
    {
        qDebug() << "No se logro cargar imagen";
    }




}

*/

void ProcessingThread::inicializarFichas()
{
    //QList<std::vector>;
}
