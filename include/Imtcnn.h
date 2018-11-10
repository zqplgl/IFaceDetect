#ifndef IOBJZONEDETECTFASTER_H
#define IOBJZONEDETECTFASTER_H

#include <opencv2/highgui/highgui.hpp>
#include <string>
#include <vector>

using namespace std;

struct BoundingBox
{
    //rect two points
    int x1, y1;
    int x2, y2;
    //regression
    float dx1, dy1;
    float dx2, dy2;
    //cls
    float score;
    //inner points
    float points_x[5];
    float points_y[5];
};
    
class IObjZoneDetect
{
    public:
        virtual void detection(const cv::Mat& img, std::vector<float>& confidence, std::vector<BoundingBox>& faceinfos)=0;
        virtual ~IObjZoneDetect(){}
};


IObjZoneDetect *CreateObjZoneMTcnnDetector(const string &model_dir);
#endif
