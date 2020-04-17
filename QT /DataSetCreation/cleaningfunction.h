#ifndef CLEANINGFUNCTION_H
#define CLEANINGFUNCTION_H

#include <iostream>


class Cleaning
{
public:
    static void GenerateData(); //Cleaning function
    static void NewFolder(); //New folder with the date and time as name
    static bool CheckifMp4(); //True if the input file is a type .mp4
    static void GetFileName(); //Getting the name of our input file

    static std::string SourceUrl; //Path of video file
    static std::string DestUrl; //Parent path for output images
    static std::string VideoName; //Getting this from GetFileName
    static int FrameCtrl; //Controlling how many images to save per second of video, default 1 img/sec
    static int xRes; //Pixel resolution, default 720
    static int yRes; //Pixel resolution, default 480
    static int FPS; //fps of input video .mp4
    static bool endofVideo; //True if the file has ended
    static bool checkValid; //True if the file is valid
};

#endif // CLEANINGFUNCTION_H
