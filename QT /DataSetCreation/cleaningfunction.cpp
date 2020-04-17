#include "cleaningfunction.h"
#include "cleaningapp.h"
#include "ui_cleaningapp.h"

#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/core/utility.hpp>

#include <QDateTime>
#include <QFileDialog>
#include <QDate>
#include <QTime>
#include <iostream>
#include <sstream>
#include <ctype.h>
#include <string>
//#include <direct.h>

#define ARRAY_COUNT(arr) (sizeof(arr) / sizeof((arr)[0]))

std::string Cleaning::SourceUrl = "http://192.168.1.111:8080/stream?topic=/HiVision_Box_1_camera/image_raw";
        //"http://192.168.1.111:8080/stream?topic=/HiVision_Box_1_camera/image_raw";
std::string Cleaning::DestUrl = "";
std::string Cleaning::VideoName = "";
int Cleaning::FrameCtrl = 1; //default
int Cleaning::xRes = 720; //default
int Cleaning::yRes = 480; //default
int Cleaning::FPS = 0;
bool Cleaning::endofVideo = false;
bool Cleaning::checkValid = false;

void Cleaning::GenerateData()
{

    char buf[4096] = {};
    int FrameCounter = 1;

    cv::VideoCapture cap(Cleaning::SourceUrl);

    int fps = cap.get(cv::CAP_PROP_FPS);

    Cleaning::FPS = fps;

    if (cap.isOpened())
    {
        Cleaning::checkValid = true;

        cv::Mat frame;

        Cleaning::NewFolder();

        char* OutputPath = new char[Cleaning::DestUrl.size() + 1];
            Cleaning::DestUrl.copy(OutputPath, (Cleaning::DestUrl.size() + 1));
            OutputPath[Cleaning::DestUrl.size()] = '\0';

        char* VidName = new char[Cleaning::VideoName.size() + 1];
            Cleaning::VideoName.copy(VidName, (Cleaning::VideoName.size() + 1));
            VidName[Cleaning::VideoName.size()] = '\0';
        int count = 0;
        while(count < 250 && cap.grab()) //remember to delete the count recording video
        {
            cap >> frame;
            if (frame.empty())
            {
                Cleaning::endofVideo = true;
                break;
            }

            cv::Mat imgNew, imgNewRotate;

            resize(frame, imgNew, cv::Size(Cleaning::xRes, Cleaning::yRes));
            //flip(imgNew, imgNewRotate, 0);

            int ctrl = fps/(Cleaning::FrameCtrl);

            if (FrameCounter % ctrl == 1)
            {
                snprintf(buf, ARRAY_COUNT(buf), "%s%s%04d.jpg", OutputPath, VidName, (Cleaning::FrameCtrl)*FrameCounter / fps);
                imwrite(buf, imgNew);
                count ++;
            }
            FrameCounter++;
        }
    }
}

void Cleaning::NewFolder()
{
     std::string parent_path = Cleaning::DestUrl;
     QString Qparent_path = QString::fromStdString(parent_path);

     QString Qfolder_path, Qfolder_name;
     std::string folder_path, folder_name;

     QDateTime DATE(QDateTime::currentDateTimeUtc());
     QDateTime local(DATE.toLocalTime());
     QTime tid = DATE.time();
     QDate date = DATE.date();

     std::string hour = std::to_string(tid.hour()+2), //Swedish timezone (+2h)
                 min = std::to_string(tid.minute()),
                 day = std::to_string(date.day()),
                 month = std::to_string(date.month()),
                 year = std::to_string(date.year());

     QString qhour = QString::fromStdString(hour),
             qmin = QString::fromStdString(min),
             qday = QString::fromStdString(day),
             qmonth = QString::fromStdString(month),
             qyear = QString::fromStdString(year);


     folder_name = hour + min + " " +year + "-" + month + "-" + day;
     folder_path = parent_path + folder_name + "/";

     Qfolder_name = qhour + qmin + " " +qyear + "-" + qmonth + "-" + qday;
     Qfolder_path = Qparent_path + Qfolder_name;

     QDir().mkdir(Qfolder_path);

     Cleaning::DestUrl = folder_path;
}

bool Cleaning::CheckifMp4()
{
    std::string filename = Cleaning::SourceUrl;
    // Remove directory if present.
    // Do this before extension removal incase directory has a period character.
    const size_t last_slash_idx = filename.find_last_of(".");
    if (std::string::npos != last_slash_idx)
    {
        filename.erase(0, last_slash_idx + 1);
    }

   if(filename == "mp4"){
    return true;
   }
}

void Cleaning::GetFileName()
{
    std::string filename = Cleaning::SourceUrl;

    // Remove directory if present.
    // Do this before extension removal incase directory has a period character.
    const size_t last_slash_idx = filename.find_last_of("\\/");
    if (std::string::npos != last_slash_idx)
    {
        filename.erase(0, last_slash_idx + 1);
    }

    // Remove extension if present.
    const size_t period_idx = filename.rfind('.');
    if (std::string::npos != period_idx)
    {
        filename.erase(period_idx);
    }
    Cleaning::VideoName = filename;

}
