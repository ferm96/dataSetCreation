#include <QCoreApplication>
#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/core/utility.hpp>

using namespace cv;
using namespace std;

const int fps = 20;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Mat frame;
    VideoCapture inputVideo("http://192.168.1.111:8080/stream?topic=/HiVision_Box_0_camera/image_raw");
            int waitTime;
            waitTime = 100;

            if (!inputVideo.isOpened())
            {
                cout << "Could not open the input video: " << endl; return -1;
            }
            while(inputVideo.grab())
            {
                inputVideo >> frame;
                imshow("stream",frame);


                if(waitKey(1000/fps) >= 0)
                    break;


                //Mat image, imageCopy; inputVideo >> image;
            }


    return a.exec();
}
